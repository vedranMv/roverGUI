#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QChar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    blank(200, 400),
    latencyGraph(50, 100),
    rollGraph(189, 400),
    pitchGraph(189, 400),
    yawGraph(189, 400)
{
    ui->setupUi(this);

    //  Allows to execute custom routine when new client connects to telemetry socket
    connect(&tcpStelemetry, SIGNAL(newConnection()),
            this, SLOT(acceptCliTelemetry()));
    tcpStelemetry.listen(QHostAddress::Any, P_TELEMETRY);
    LogLine("Listening on telemetry socket " + QString::number(P_TELEMETRY));
    tcpCliTelemetry = NULL;

    //  Allows to execute custom routine when new clients client connects to command socket
    connect(&tcpScommands, SIGNAL(newConnection()),
            this, SLOT(acceptCliCommands()));
    tcpScommands.listen(QHostAddress::Any, P_COMMANDS);
    LogLine("Listening on commands socket " + QString::number(P_COMMANDS));
    tcpCliCommands = NULL;

    //  Add basic lines to the plot -> construct background
    blank.SetCenter(200, 200);
    blank.SetXRangeKeepAspectR(-80, 80);
    blank.Circle(30);   //  30cm range
    blank.Circle(60);   //  60cm range
    blank.Circle(80);   //  80cm range
    //  Plot data axes with divisions every 10cm, every 2nd division labeled
    blank.AddAxes(10, 10, 2, 2);

    // Show the image
    ui->radarPlot->showImage( blank.GetMatImg() );

    //  Adjust graph settings for latency graph
    latencyGraph.SetCenter(1, 45);
    latencyGraph.SetXRangeKeepAspectR(-1, 99);

    //  Adjust setting for RPY graphs
    rollGraph.SetXRangeKeepAspectR(-359, 40, true);
    pitchGraph.SetXRangeKeepAspectR(-359, 40, true);
    yawGraph.SetXRangeKeepAspectR(-359, 40, true);

    //  Hide warning images for priority inversion
    pinv[ESP_UID] = NULL;
    pinv[RADAR_UID] = ui->radPinv_GV;
    pinv[ENGINES_UID] = ui->engPinv_GV;
    pinv[MPU_UID] = ui->inerPinv_GV;
    pinv[DATAS_UID] = NULL;
    pinv[PLAT_UID] = ui->platPinv_GV;
    pinv[EVLOG_UID] = NULL;
    pinv[TASKSCHED_UID] = NULL;

    for (int i = 0; i < 6; i++)
        if (pinv[i] != NULL)
            pinv[i]->setVisible(false);
}


MainWindow::~MainWindow()
{

    if (tcpCliCommands != 0)
        tcpCliCommands->close();
    if (tcpCliTelemetry != 0)
        tcpCliTelemetry->close();
    tcpStelemetry.close();
    tcpScommands.close();

    delete ui;
}

/**
 *  Parse incoming telemetry frame. Format is:
 *  [uptimeMS]:Roll|Pitch|Yaw\n
 * @brief ParseTelemetry
 * @param teleStr
 */
void MainWindow::ParseTelemetry(QString teleStr)
{
    //  Saved variables from previous call to this function
    static double oldTime = 0,
                  oldRoll = 0,
                  oldPitch = 0,
                  oldYaw = 0;

    uint16_t i = 0;
    QString tmpStr;
    //  Find beginning
    while(teleStr[i++] != '[');
    //  Save local time(in ms) on MCU into a string
    while(teleStr[i] != ']')
        tmpStr += teleStr[i++];
    //  Convert time in string to number (ms -> s)
    ui->utime_LE->setText(QString::number(tmpStr.toDouble()/1000));
    ui->mUtime_LE->setText(ui->utime_LE->text());
    //  Calculate time since last received frame to estimate latency
    ui->deltams_LE->setText(QString::number(tmpStr.toDouble()/1000-oldTime));
    oldTime = tmpStr.toDouble()/1000;

    tmpStr = "";
    i+=2;   //  Point to first char of 'Roll'
    //  Get roll
    while(teleStr[i] != '|')
        tmpStr += teleStr[i++];
    ui->roll_LE->setText(tmpStr);
    AppendToGraph(rollGraph, oldRoll, tmpStr.toDouble(), ui->rollPlot);
    oldRoll = tmpStr.toDouble();
    tmpStr = "";
    i++;    //  Point to first char of 'Pitch'

    //  Get pitch
    while(teleStr[i] != '|')
        tmpStr += teleStr[i++];
    ui->pitch_LE->setText(tmpStr);
    AppendToGraph(pitchGraph, oldPitch, tmpStr.toDouble(), ui->pitchPlot);
    oldPitch = tmpStr.toDouble();
    tmpStr = "";
    i++;    //  Point to first char of 'Yaw'

    //  Get yaw
    while(teleStr[i] != '|')
        tmpStr += teleStr[i++];
    ui->yaw_LE->setText(tmpStr);
    AppendToGraph(yawGraph, oldYaw, tmpStr.toDouble(), ui->yawPlot);
    oldYaw = tmpStr.toDouble();
    tmpStr = "";

    //  Update latency plot with delta value
    cv::Point2d endP(98, (ui->deltams_LE->text().toDouble()-1.5)*1000.0);
    latencyGraph.LineCartesian(endP, cv::Point2d(98, 0));

    //  Shift data in latency plot one column to the left
    cv::Mat &lastPlot = latencyGraph.GetMatImg();
    cv::Mat out(lastPlot.size(), lastPlot.type(), cv::Scalar::all(255));
    lastPlot(cv::Rect(1,0, lastPlot.cols-1,lastPlot.rows)).copyTo(out(cv::Rect(0,0,lastPlot.cols-1,lastPlot.rows)));
    out.copyTo(lastPlot);

    //  Copy graph into new holder to be able to apply axes
    OCVGraph temp(latencyGraph);

    //  Draw axes and horizontal lines for every 10ms
    temp.AddAxes(15, 10, 15, 1);
    temp.LineCartesian(cv::Point2d(-1, 10), cv::Point2d(99, 10), COLOR_25GREY);
    temp.LineCartesian(cv::Point2d(-1, 20), cv::Point2d(99, 20), COLOR_25GREY);
    temp.LineCartesian(cv::Point2d(-1, 30), cv::Point2d(99, 30), COLOR_25GREY);
    temp.LineCartesian(cv::Point2d(-1, 40), cv::Point2d(99, 40), COLOR_25GREY);

    ui->latencyPlot->showImage( temp.GetMatImg() );
}
/**
 * @brief MainWindow::ParseEventLog
 * @param teleStr
 */
void MainWindow::ParseEventLog(QString teleStr)
{
    //Find '2*' sequence, start of EventLog telemetry frame
    QStringList entries = teleStr.split("2*");

    //  Loop through all events in this list
    for (QString X : entries)
    {
        QStringList parts = X.split(":", QString::SkipEmptyParts);
        //  Skip broken/short frames
        if (parts.length() < 5)
            continue;

        QString msg;
        msg = parts[1] + ": " + QString(events[parts[4].toInt()]) + " in module "
              + QString(libName[parts[2].toInt()]) + " during task " +
               QString(parts[3]);
        LogLine(msg, ui->vel_TE);

        //  Update GUI elements with data from event log
        EventUpdateGUI((Events)parts[4].toInt(), parts[2].toInt());

        //  If this is the last line from event log (one indexed 0)
        if ((parts[0].toInt() == 0))
        {
            uint16_t commandLen = 0,
                     i = 1; //  Start at 1 to skip '[' on first position
            char command[50] = {0},
                 args[5] = {0};
            QString tmpStr;
            uint32_t timeStamp;

            //  Extract timestamp in ms from this frame and save it to args
            //  for constructing the request
            while(parts[1][i] != ']')
                tmpStr += parts[1][i++];
            //  Convert string to int
            timeStamp = tmpStr.toLong();
            //  Copy int value to arguments list
            memcpy(args, &timeStamp, sizeof(uint32_t));

            //  Send request to drop internal event log on the MCU
            MakeRequest((uint8_t*)command, EVLOG_UID, EVLOG_DROP, 0, 0);
            AppendArgs((uint8_t*)command, &commandLen, (void*)args, sizeof(uint32_t));
            //  Send command to TCP client
            SendCommand(command, commandLen);
        }
    }
}

void MainWindow::EventUpdateGUI(Events event, uint8_t libUID)
{
    QString lable = QString(events[event]);
    QString styleSheet;

    switch(event)
    {
    case EVENT_ERROR:
        {
            styleSheet = "background-color:rgb(255, 0, 4);";
        }
        break;
    case EVENT_UNINITIALIZED:
        {
            styleSheet = "background-color:rgb(126, 189, 189);";
        }
        break;
    case EVENT_STARTUP:
        {
            styleSheet = "background-color:rgb(177, 255, 134);";
            if (pinv[libUID] != 0)
                pinv[libUID]->setVisible(false);
        }
        break;
    case EVENT_INITIALIZED:
        {
            styleSheet = "background-color:rgb(170, 255, 0);";
        }
        break;
    case EVENT_OK:
        {
            styleSheet = "background-color:rgb(0, 255, 29);";
        }
        break;
    case EVENT_HANG:
        {
            styleSheet = "background-color:rgb(255, 167, 14);";
        }
        break;
    case EVENT_PRIOINV:
        {
            if (pinv[libUID] != 0)
                pinv[libUID]->setVisible(true);
        }
        break;
    }

    switch(libUID)
    {
    case ESP_UID:
        {
            ui->comm_L->setStyleSheet(styleSheet);

        }
        break;
    case RADAR_UID:
        {
            ui->radar_L->setStyleSheet(styleSheet);
            ui->radar_L_2->setStyleSheet(styleSheet);
            ui->radar_L_2->setText(lable);
        }
        break;
    case ENGINES_UID:
        {
            ui->engines_L->setStyleSheet(styleSheet);
            ui->engines_L_2->setStyleSheet(styleSheet);
            ui->engines_L_2->setText(lable);
        }
        break;
    case MPU_UID:
        {
            ui->inertial_L->setStyleSheet(styleSheet);
            ui->inertial_L_2->setStyleSheet(styleSheet);
            ui->inertial_L_2->setText(lable);
        }
        break;
    case PLAT_UID:
        {
            ui->platform_L->setStyleSheet(styleSheet);
            ui->platform_L_2->setStyleSheet(styleSheet);
            ui->platform_L_2->setText(lable);
        }
        break;
    case EVLOG_UID:
        {

        }
        break;
    }
}

/**
 * @brief Parse response on a give command (such as radar scan)
 * @param respStr
 */
void MainWindow::ParseCommandResp(QString respStr)
{
    //  Setup graph background
    OCVGraph image(blank);

    uint16_t it = 0;

    if(respStr.length() < 100)
        return;
    for (uint16_t i = 10; i <170; i++)
        image.LinePolar((double)i, (double)((int)respStr.at(i-10+it).toAscii()));

    // Show the image
    ui->radarPlot->showImage( image.GetMatImg() );
}


void MainWindow::AppendToGraph(OCVGraph &graph, double old, double val, CQtOpenCVViewerGl *renderer)
{
    //  Update latency plot with delta value
    cv::Point2d endP(0, val);
    graph.LineCartesian(endP, cv::Point2d(0, old));

    //  Shift data in latency plot one column to the left
    cv::Mat &shiftPlot = graph.GetMatImg();
    cv::Mat out(shiftPlot.size(), shiftPlot.type(), cv::Scalar::all(255));
    shiftPlot(cv::Rect(1,0, shiftPlot.cols-1,shiftPlot.rows)).copyTo(out(cv::Rect(0,0,shiftPlot.cols-1,shiftPlot.rows)));
    out.copyTo(shiftPlot);

    //  Copy graph into new holder to be able to apply axes
    OCVGraph temp(graph);

    //  Draw axes and horizontal lines for every 10ms
    temp.AddAxes(20, 10, 2, 2);

    renderer->showImage( temp.GetMatImg() );
}

void MainWindow::LogLine(QString arg, QPlainTextEdit *holder)
{
    if (holder == 0)
        ui->log->setPlainText(ui->log->toPlainText() + arg + '\n');
    else
        holder->setPlainText(holder->toPlainText() + arg + '\n');
}

/**
 * @brief Handles "clicked" event for "Scan" button
 * Sends 'radar scan' command to the "command stream"; if opened
 */
void MainWindow::on_scan_bt_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x00"};

    MakeRequest((uint8_t*)command, RADAR_UID, RADAR_SCAN, -3000, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Accept new connection on 'telemery' socket
 */
void MainWindow::acceptCliTelemetry(void)
{
    tcpCliTelemetry = tcpStelemetry.nextPendingConnection();
    LogLine("Have client on telemetry: " + tcpCliTelemetry->peerAddress().toString());
    ui->telemetry_L->setStyleSheet("background-color:rgb(0, 255, 29);");
    connect(tcpCliTelemetry, SIGNAL(readyRead()),
            this, SLOT(readDataTelemetry()));
    connect(tcpCliTelemetry, SIGNAL(aboutToClose()), this, SLOT(sockTelClose()));
}

/**
 * @brief Accept new connection on 'commands' socket
 */
void MainWindow::acceptCliCommands(void)
{
    tcpCliCommands = tcpScommands.nextPendingConnection();
    LogLine("Have client on commands: " + tcpCliCommands->peerAddress().toString());
    ui->commands_L->setStyleSheet("background-color:rgb(0, 255, 29);");
    connect(tcpCliCommands, SIGNAL(readyRead()),
            this, SLOT(readDataCommands()));
    connect(tcpCliCommands, SIGNAL(aboutToClose()), this, SLOT(sockCommClose()));
    connect(tcpCliCommands, SIGNAL(aboutToClose()), this, SLOT(sockCommClose()));
}

void MainWindow::sockCommClose()
{
    LogLine("Comm closing");
    ui->commands_L->setStyleSheet("background-color:rgb(255, 0, 4);");
}

void MainWindow::sockTelClose()
{
    ui->telemetry_L->setStyleSheet("background-color:rgb(255, 0, 4);");
}

/**
 * @brief Called every time new data comes on the 'telemetry' socket. Function
 * logs data and calls parser to update UI elements with new telemetry data.
 */
void MainWindow::readDataTelemetry(void)
{
  char buffer[1024] = {0};
  tcpCliTelemetry->read(buffer, tcpCliTelemetry->bytesAvailable());
  //LogLine("TELEMETRY: " + QString(buffer));

  //    First two bytes determine what kind of data is in telemetry packet
  if ((buffer[0] == '1') && (buffer[1] == '*'))
    ParseTelemetry(QString(buffer+3));
  else if ((buffer[0] == '2') && (buffer[1] == '*'))
    ParseEventLog(QString(buffer)); //Leave leading 11:
}

/**
 * @brief Called every time new data comes on the 'commands' socket. Functions
 * calls parser to interpret incoming data and update UI elements with it.
 */
void MainWindow::readDataCommands(void)
{
  char buffer[1024] = {0};
  tcpCliCommands->read(buffer, tcpCliCommands->bytesAvailable());
  LogLine("COMMANDS: " + QString(buffer));
  ParseCommandResp(QString(buffer));
}

/**
 * @brief Handles "clicked" event for "Clear" button
 * Clear log window
 */
void MainWindow::on_clrLog_clicked()
{
    ui->log->setPlainText("");
}

void MainWindow::on_reboot_BT_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, PLAT_UID, PLAT_REBOOT, -3000, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

void MainWindow::on_inReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, MPU_UID, MPU_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

void MainWindow::on_clrVel_PB_clicked()
{
    ui->vel_TE->setPlainText("");
}

void MainWindow::on_updateTime_SB_editingFinished()
{
    static double oldVal = 0;

    //  Refresh update interval for telemetry only if spinBox value has changed
    if (oldVal != ui->updateTime_SB->value())
    {
        LogLine("Changing update time to " + QString::number(ui->updateTime_SB->value()));
        oldVal = ui->updateTime_SB->value();
    }
}

void MainWindow::on_imuSamp_CB_toggled(bool checked)
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {(char)checked, 0};

    MakeRequest((uint8_t*)command, MPU_UID, MPU_LISTEN, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

bool MainWindow::SendCommand(char *command, uint16_t commandLen)
{
    //  Check if there ary any client connected
    if (tcpCliCommands == NULL)
        return false;

    tcpCliCommands->write(command,commandLen);
    LogLine("Sent command:> " + QString(command));

    return true;
}

