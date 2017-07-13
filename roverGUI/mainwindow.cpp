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
#include <QTimer>

//  Status of sending command
#define COMMANDS_ACK    1
#define COMMANDS_NACK   2
#define COMMANDS_RESET  3
uint8_t sendStatus = COMMANDS_RESET;

///-----------------------------------------------------------------------------
///        GUI constructor & destructor                                    [GUI]
///-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    blank(200, 400, cv::Scalar(0x45, 0x45, 0x45)),
    latencyGraph(50, 100, cv::Scalar(0x45, 0x45, 0x45)),
    rollGraph(189, 400, cv::Scalar(0x45, 0x45, 0x45)),
    pitchGraph(189, 400, cv::Scalar(0x45, 0x45, 0x45)),
    yawGraph(189, 400, cv::Scalar(0x45, 0x45, 0x45)),
    _sentReq(0), _ackReq(0)
{
    ui->setupUi(this);

    qApp->setStyleSheet("@import url(\"/styles/default.css\");");

    //  Allows execution of custom routine when new client connects to 'telemetry' socket
    connect(&tcpStelemetry, SIGNAL(newConnection()),
            this, SLOT(acceptCliTelemetry()));
    tcpStelemetry.listen(QHostAddress::Any, P_TELEMETRY);
    LogLine("Listening on telemetry socket " + QString::number(P_TELEMETRY));
    tcpCliTelemetry = NULL;

    //  Allows execution of custom routine when new clients client connects to 'command' socket
    connect(&tcpScommands, SIGNAL(newConnection()),
            this, SLOT(acceptCliCommands()));
    tcpScommands.listen(QHostAddress::Any, P_COMMANDS);
    LogLine("Listening on commands socket " + QString::number(P_COMMANDS));
    tcpCliCommands = NULL;

    //  Add basic lines to the radar plot -> construct background
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

    //  Put all labels from 'Overview' tab to a single list, indexed by kernel module ID
    labOverview[ESP_UID] = ui->comm_L;
    labOverview[RADAR_UID] = ui->radar_L;
    labOverview[ENGINES_UID] = ui->engines_L;
    labOverview[MPU_UID] = ui->inertial_L;
    labOverview[DATAS_UID] = NULL;
    labOverview[PLAT_UID] = ui->platform_L;
    labOverview[EVLOG_UID] = NULL;
    labOverview[TASKSCHED_UID] = NULL;

    //  Put all labels from 'Instruments' tab to a single list, indexed by kernel module ID
    labInstruments[ESP_UID] = ui->comm_L_2;
    labInstruments[RADAR_UID] = ui->radar_L_2;
    labInstruments[ENGINES_UID] = ui->engines_L_2;
    labInstruments[MPU_UID] = ui->inertial_L_2;
    labInstruments[DATAS_UID] = NULL;
    labInstruments[PLAT_UID] = ui->platform_L_2;
    labInstruments[EVLOG_UID] = ui->evlog_L_2;
    labInstruments[TASKSCHED_UID] = ui->ts_L_2;

    //  Put all warning images into a single list
    pinv[ESP_UID] = ui->commPinv_GV;
    pinv[RADAR_UID] = ui->radPinv_GV;
    pinv[ENGINES_UID] = ui->engPinv_GV;
    pinv[MPU_UID] = ui->inerPinv_GV;
    pinv[DATAS_UID] = NULL;
    pinv[PLAT_UID] = ui->platPinv_GV;
    pinv[EVLOG_UID] = ui->evlogPinv_GV;
    pinv[TASKSCHED_UID] = ui->tsPinv_GV;

    //  Hide warning images for priority inversion
    for (int i = 0; i < 8; i++)
        if (pinv[i] != NULL)
            pinv[i]->setVisible(false);

    //  Configure scroll area for mission planning so that overflow after adding
    //  new tasks results in creatin on scroll bar and not cutoff
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout(ui->scrollAreaWidgetContents));
    ui->missionScroll_SA->setWidget(ui->scrollAreaWidgetContents);

    //  Initialize timer used to send batch of commands through 'commands' stream
    sendTimer = new QTimer(this);
    connect(sendTimer, SIGNAL(timeout()), this, SLOT(sendNext()));

    ui->missPer_LE->setVisible(ui->missPer_CB->isChecked());
    ui->missRep_LE->setVisible(ui->missPer_CB->isChecked());

    ui->missionT_GB->setEnabled((ui->mStart_LE->text().length() > 0));
    ui->missionT_GB->setVisible((ui->mStart_LE->text().length() > 0));

    ui->warn_GV->setVisible(false);
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

///-----------------------------------------------------------------------------
///        Miscellaneous functions                                        [MISC]
///-----------------------------------------------------------------------------
/**
 * @brief Send a command from GUI through 'commands' socket (if opened)
 * @param command
 * @param commandLen
 * @return true if command was sent, false if not
 */
bool MainWindow::SendCommand(const char *command, uint16_t commandLen)
{
    //  Check if there ary any client connected
    if (tcpCliCommands == NULL)
        return false;

    tcpCliCommands->write(command,commandLen);
    LogLine("Sent command:> " + QString(command));
    _sentReq++;

    //    Update quality of service
    ui->qos_PrB->setValue(_ackReq*100/_sentReq);

    return true;
}

/**
 * @brief sendTimer timout() event handler
 * On each timout event this function sends one entry from mission planner. Once
 * all mission tasks have been sent timer is stopped in here.
 */
void MainWindow::sendNext(void)
{
    static uint16_t counter = 0;
    //  Count number of attempts at sending, if a command receives NACK 3 times
    //  it's skipped
    static int8_t attempts = 0;

    //  Move to next entry if last sending resulted in ACK or we've reached max
    //  number of sending attempts. Reset status.
    if ((sendStatus == COMMANDS_ACK) || (attempts == 3))
    {
        counter++;
        sendStatus == COMMANDS_RESET;
        attempts = 0;
    }

    //  Check if there are any entries not sent
    if (counter < mEntries.size())
    {
        uint16_t commandLen = 0;
        char     command[50] = {0};

        //  Adjust parameters in case mission is scheduled to be periodic and
        //  construct request from current mission entry
        if (ui->missPer_CB->isChecked())
            mEntries[counter]->ToReq(command, commandLen,
                                     ui->missRep_LE->text().toLong(),
                                     ui->missPer_LE->text().toLongLong()*1000);
        else
            mEntries[counter]->ToReq(command, commandLen, 0, 0);

        //  Send command over 'commands' stream
        SendCommand(command, commandLen);
        attempts++;
    }
    else
    {
        counter = 0;
        sendTimer->stop();
    }
}

///-----------------------------------------------------------------------------
///        Functions for refreshing GUI elements                           [GUI]
///-----------------------------------------------------------------------------
/**
 * @brief Update certain GUI labels with new status and color based on the event
 * which occurred in specified module
 * @param event
 * @param libUID
 */
void MainWindow::EventUpdateGUI(Events event, uint8_t libUID)
{
    QString lable = QString(events[event]);
    QString styleSheet;

    //  Select color based on event
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
            styleSheet = "background-color:rgb(120, 120, 120);";
            if (pinv[libUID] != 0)
                pinv[libUID]->setVisible(true);
        }
        break;
    }
    styleSheet += "\ncolor:#454545;\nborder-radius:3px;";

    //  Update labels with new text and color
    if (labOverview[libUID] != 0)
        labOverview[libUID]->setStyleSheet(styleSheet);
    if (labInstruments[libUID] != 0)
    {
        labInstruments[libUID]->setStyleSheet(styleSheet);
        labInstruments[libUID]->setText(lable);
    }
}
/**
 * @brief Append new measurement to one of realtime-graphs in GUI
 * @param graph Reference to the realtime-graph
 * @param old Last value plotted in graph
 * @param val New value being appended to graph
 * @param renderer Pointer to OpenGL graph holder
 */
void MainWindow::AppendToGraph(OCVGraph &graph, double old, double val, CQtOpenCVViewerGl *renderer)
{
    //  Update plot with delta value
    cv::Point2d endP(0, val);
    graph.LineCartesian(endP, cv::Point2d(0, old), COLOR_WHITE);

    //  Shift data in latency plot one column to the left
    cv::Mat &shiftPlot = graph.GetMatImg();
    cv::Mat out(shiftPlot.size(), shiftPlot.type(), cv::Scalar::all(255));
    shiftPlot(cv::Rect(1,0, shiftPlot.cols-1,shiftPlot.rows)).copyTo(out(cv::Rect(0,0,shiftPlot.cols-1,shiftPlot.rows)));
    out.copyTo(shiftPlot);
    //  Match color of background in shifted line with that of GUI background
    for (uint16_t i = 0; i < shiftPlot.rows; i++)
    {
        cv::Vec3b &pix = shiftPlot.at<cv::Vec3b>(i, shiftPlot.cols-1);

        if (pix.val[0] != 0xFF)
            break;
        pix.val[0] = 0x45;
        pix.val[1] = 0x45;
        pix.val[2] = 0x45;
    }

    //  Copy graph into new holder to be able to apply axes
    OCVGraph temp(graph);

    //  Draw axes and horizontal lines for every 10ms
    temp.AddAxes(20, 10, 2, 2);

    renderer->showImage( temp.GetMatImg() );
}
/**
 * @brief Add line of text to one of log text fields in GUI
 * @param arg Line of text to add
 * @param holder Pointer to text field element in which to add line
 */
void MainWindow::LogLine(QString arg, QPlainTextEdit *holder)
{
    //  Add text to 'GUI log' if holder is NULL pointer
    //  Else add to the specified text field
    if (holder == NULL)
        holder = ui->log;

    //  To prevent stack smashing, reset logs once they reach 6000 characters
    if ((holder->toPlainText().length()+arg.length()) >= 6000)
        holder->setPlainText("");
    //  Add new line to the log
    holder->setPlainText(holder->toPlainText() + arg + '\n');
}

/**
 * @brief Called every time a task has been deleted from mission, handles
 * renumbering the tasks in case the task in the middle has been deleted
 * (Mission planner->Mission tasks)
 */
void MainWindow::UpdateIDs()
{
    //  House keeping: Check all 'dead' (deleted) entries from mEntries vector
    //  and remove them
    for (uint8_t i = 0; i < mEntries.size(); i++)
        if (mEntries[i]->dead)
        {
            //  Delete object from heap
            //delete mEntries[i];
            //  Delete entry from vector
            mEntries.erase(mEntries.begin()+i);
        }
    //std::cout<<"Deleted, updating labels\n";
    //  After deleting do one more pass through entries to update their number
    for (uint8_t i = 0; i < mEntries.size(); i++)
        mEntries[i]->ChangeIndex(i);
}

///-----------------------------------------------------------------------------
///         Miscelaneous event functions(clicked, checked...) for GUI elements
///-----------------------------------------------------------------------------
/**
 * @brief Toggle sampling of IMU data (Instruments->MPU9250)
 * @param checked If true turns on sampling of IMU on vehicle,
 *                if false sampling inhibited
 */
void MainWindow::on_imuSamp_CB_toggled(bool checked)
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {(char)checked, 0};

    MakeRequest((uint8_t*)command, MPU_UID, MPU_LISTEN, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Changes time-period for sending telemetry data, default 1.5s
 */
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

///-----------------------------------------------------------------------------
///         Stream data parsers                           [TELEMETRY & COMMANDS]
///-----------------------------------------------------------------------------
/**
 * @brief Parse response on a give command (such as radar scan)
 * @param respStr Response from vehicle to a sent command
 */
bool MainWindow::ParseCommandResp(QString respStr)
{
    //  Setup graph background
    OCVGraph image(blank);

    uint16_t it = 0;

    if(respStr.length() < 100)
        return false;
    for (uint16_t i = 10; i <170; i++)
        image.LinePolar((double)i, (double)((int)respStr.at(i-10+it).toAscii()), cv::Point2d(0,0), COLOR_WHITE);

    // Show the image
    ui->radarPlot->showImage( image.GetMatImg() );

    return true;
}

/**
 *  @brief Parse incoming telemetry frame. Format is:
 *  [uptimeMS]:Roll|Pitch|Yaw\n
 *  @param teleStr
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
    ui->mUtime_LE_2->setText(QString::number(tmpStr.toDouble()/1000));
    uint32_t dd, hh, mm;
    double ss = tmpStr.toDouble()/1000;
    mm = (ss/60);
    ss -= ((double)mm)*60;
    hh = mm / 60;
    mm -= hh * 60;
    dd = hh / 24;
    hh -= dd * 24;
    //  Updatime time on top of window
    ui->mUtime_LE->setText(QString::number(dd)+"d, "+QString::number(hh)+":"+QString::number(mm)+":"+QString::number(ss));
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
    //  Match color of background in shifted line with that of GUI background
    for (uint16_t i = 0; i < lastPlot.rows; i++)
    {
        cv::Vec3b &pix = lastPlot.at<cv::Vec3b>(i, lastPlot.cols-1);

        if (pix.val[0] != 0xFF)
            break;
        pix.val[0] = 0x45;
        pix.val[1] = 0x45;
        pix.val[2] = 0x45;
    }

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
 * @brief Parse a telemetry line containing event log data
 * @param teleStr String containing event log entri(es)
 */
void MainWindow::ParseEventLog(QString teleStr)
{
    //  Find '2*' sequence, start of EventLog telemetry frame
    QStringList entries = teleStr.split("2*");

    //  Loop through all events in this list
    for (QString X : entries)
    {
        QStringList parts = X.split(":", QString::SkipEmptyParts);
        //  Skip broken/short frames
        if (parts.length() < 5)
            continue;

        QString msg;
        msg = parts[1] + ": " + QString(events[parts[4].toInt()]) + " in "
              + QString(libName[parts[2].toInt()]) + " on task " +
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

/**
 * @brief Parse a telemetry line containing task scheduler entries
 * @param teleStr String containing event log entri(es)
 */
void MainWindow::ParseTaskEntry(QString teleStr)
{
    //  Find '3*' sequence, start of EventLog telemetry frame
    QStringList entries = teleStr.split("3*");

    //  Loop through all events in this list
    for (QString X : entries)
    {
        QStringList parts = X.split(":", QString::SkipEmptyParts);
        //  Skip broken/short frames
        if (parts.length() < 4)
            continue;

        QString msg;
        msg = parts[0] + ": " + QString(allTasks[parts[1].toInt()][parts[2].toInt()])
              + ", period " + parts[3] +" ms";
        LogLine(msg, ui->tsLog_TE);
    }
}


///-----------------------------------------------------------------------------
///         TCP telemetry stream                                     [TELEMETRY]
///-----------------------------------------------------------------------------
/**
 * @brief Accept new connection on 'telemetry' socket
 */
void MainWindow::acceptCliTelemetry(void)
{
    tcpCliTelemetry = tcpStelemetry.nextPendingConnection();
    LogLine("Have client on telemetry: " + tcpCliTelemetry->peerAddress().toString());
    ui->telemetry_L->setStyleSheet("background-color:rgb(0, 255, 29);\ncolor:#454545;\nborder-radius:3px;");
    connect(tcpCliTelemetry, SIGNAL(readyRead()),
            this, SLOT(readDataTelemetry()));
    connect(tcpCliTelemetry, SIGNAL(aboutToClose()), this, SLOT(sockTelClose()));
}
/**
 * @brief Read incoming data from TCP 'telemetry' socket
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
  else if ((buffer[0] == '3') && (buffer[1] == '*'))
    ParseTaskEntry(QString(buffer));
}
/**
 * @brief Triggered when TCP socket is closed
 */
void MainWindow::sockTelClose()
{
    ui->telemetry_L->setStyleSheet("background-color:rgb(255, 0, 4);\ncolor:#454545;\nborder-radius:3px;");
}

///-----------------------------------------------------------------------------
///         TCP command stream                                        [COMMANDS]
///-----------------------------------------------------------------------------
/**
 * @brief Accept new connection on 'commands' socket
 */
void MainWindow::acceptCliCommands(void)
{
    tcpCliCommands = tcpScommands.nextPendingConnection();
    LogLine("Have client on commands: " + tcpCliCommands->peerAddress().toString());
    ui->commands_L->setStyleSheet("background-color:rgb(0, 255, 29);\ncolor:#454545;\nborder-radius:3px;");
    connect(tcpCliCommands, SIGNAL(readyRead()),
            this, SLOT(readDataCommands()));
    connect(tcpCliCommands, SIGNAL(aboutToClose()), this, SLOT(sockCommClose()));
    connect(tcpCliCommands, SIGNAL(aboutToClose()), this, SLOT(sockCommClose()));
}

/**
 * @brief Read incoming data from TCP 'commands' socket
 */
void MainWindow::readDataCommands(void)
{
  char buffer[1024] = {0};
  tcpCliCommands->read(buffer, tcpCliCommands->bytesAvailable());
  LogLine("COMMANDS: " + QString(buffer));

  //    If there's no radar data embedded, it's only ACK/NACK response
  if (!ParseCommandResp(QString(buffer)))
  {
      QString qsBuffer(buffer);
      //    If string doesn't contain NACK, it's been acknowledged by vehicle
      if (!qsBuffer.contains("NACK"))
          _ackReq++, sendStatus = COMMANDS_ACK;
      else
          sendStatus = COMMANDS_NACK;
      //    Update quality of service
      ui->qos_PrB->setValue(_ackReq*100/_sentReq);
  }

}

/**
 * @brief Triggered when TCP socket is closed
 */
void MainWindow::sockCommClose()
{
    LogLine("Comm closing");
    ui->commands_L->setStyleSheet("background-color:rgb(255, 0, 4);\ncolor:#454545;\nborder-radius:3px;");
}

///-----------------------------------------------------------------------------
///         Push-button events                                         [CLICKED]
///-----------------------------------------------------------------------------
/**
 * @brief Reset communication module (Instruments->Platform)
 */
void MainWindow::on_commReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, ESP_UID, ESP_T_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Clear GUI log (Overview->GUI log)
 */
void MainWindow::on_clrLog_clicked()
{
    ui->log->setPlainText("");
}

/**
 * @brief Clear vehicle's event log (Overview->Vehicle event log)
 */
void MainWindow::on_clrVel_PB_clicked()
{
    ui->vel_TE->setPlainText("");
}

/**
 * @brief Reboot whole platform (Overview)
 */
void MainWindow::on_reboot_BT_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, PLAT_UID, PLAT_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Reboot inertial unit (Instruments->MPU9250)
 */
void MainWindow::on_inReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, MPU_UID, MPU_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Initiate radar scan (Overview->Scan)
 */
void MainWindow::on_scan_bt_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x00"};

    MakeRequest((uint8_t*)command, RADAR_UID, RADAR_SCAN, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Only case of writing into a telemetry socket, when clicked attempts to
 * reopen 'commands' stream from the vehcile's side
 */
void MainWindow::on_commands_L_2_clicked()
{
    //  Check if there ary any client connected
    if (tcpCliTelemetry == NULL)
        return;

    tcpCliTelemetry->write("REOP\r\n",6);
    LogLine("Sent command:> " + QString("REOP"));
}
/**
 * @brief Adds another entry to the mission task list
 * (Mission planner->Mission tasks)
 */
void MainWindow::on_addTask_PB_clicked()
{
    //  Create new entry
    MissionEntry *tmp = new MissionEntry(mEntries.size(), ui->scrollAreaWidgetContents, ui->mStart_LE);
    mEntries.push_back(tmp);
    //  Connect 'Deleted' signal to 'UpdateIDs' slot so that we automatically
    //  change IDs of all entries when signal is deleted
    connect(mEntries.back(), SIGNAL(Deleted()), this, SLOT(UpdateIDs()));
    //  Add mission entry to scrollable area
    ui->scrollAreaWidgetContents->layout()->addWidget(mEntries.back()->Container());
}

/**
 * @brief Sends command to clear and reset event logger
 * (Instruments->Platform->Event log)
 */
void MainWindow::on_evlogReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x17"};

    MakeRequest((uint8_t*)command, EVLOG_UID, EVLOG_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Request status update for all modules from the vehicle
 * (Instruments->Platform->Event log)
 */
void MainWindow::on_evlogUpd_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x00"};

    MakeRequest((uint8_t*)command, PLAT_UID, PLAT_EVLOG_DUMP, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Request print of all tasks currently in task scheduler
 * (Instruments->Platform->Task scheduler)
 */
void MainWindow::on_tsUpd_PB_clicked()
{
    ui->tsLog_TE->setPlainText("");

    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x00"};

    MakeRequest((uint8_t*)command, PLAT_UID, PLAT_TS_DUMP, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief MainWindow::on_schedMiss_PB_clicked
 */
void MainWindow::on_schedMiss_PB_clicked()
{
    //  Reset status
    sendStatus = COMMANDS_RESET;
    //  Start sending through timeout event
    sendTimer->start(200);  //  send max 5 commands per second
}

/**
 * @brief Field evaluation triggered by changing content of mission time
 * Function evaluates content of mission starting time text box in order to
 * ensure that content of it always evaluates to a number
 * @param arg1
 */
void MainWindow::on_mStart_LE_textChanged(const QString &arg1)
{
    //  Allow user to type in only digits and decimal comma
    if (arg1.length() > 0)
        if (!(arg1[arg1.length()-1].isDigit() || (arg1[arg1.length()-1] == '.')))
        {
            if (arg1.length() == 1)
                ui->mStart_LE->setText("");
            else
                ui->mStart_LE->setText(arg1.left(arg1.length()-1));
        }

    ui->missionT_GB->setEnabled((arg1.length() > 0));
    ui->missionT_GB->setVisible((arg1.length() > 0));

    //  Display warning if mission is scheduled in past
    if (ui->mStart_LE->text().toDouble() < ui->mUtime_LE_2->text().toDouble())
        ui->warn_GV->setVisible(true);
    else
        ui->warn_GV->setVisible(false);
}

void MainWindow::on_engReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x17"};

    MakeRequest((uint8_t*)command, ENGINES_UID, ENG_T_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

void MainWindow::on_missPer_CB_clicked(bool checked)
{
    ui->missPer_LE->setVisible(checked);
    ui->missRep_LE->setVisible(checked);
}
