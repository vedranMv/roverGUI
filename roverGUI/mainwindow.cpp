#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "roverinterface.h"
#include "ui_mainwindow.h"
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QChar>
#include <QDebug>


/**
 *  Parse incoming telemetry frame. Format is:
 *  [uptimeMS]:Roll|Pitch|Yaw\n
 * @brief ParseTelemetry
 * @param teleStr
 */
void MainWindow::ParseTelemetry(QString teleStr)
{
    uint16_t i = 0;
    QString tmpStr;
    //  Find beginning
    while(teleStr[i++] != '[');
    //  Get time
    while(teleStr[i] != ']')
        tmpStr += teleStr[i++];

    ui->utime_LE->setText(QString::number(tmpStr.toDouble()/1000));
    tmpStr = "";
    i+=2;   //  Point to first char of 'Roll'
    //  Get roll
    while(teleStr[i] != '|')
        tmpStr += teleStr[i++];
    ui->roll_LE->setText(tmpStr);
    tmpStr = "";
    i++;

    //  Get pitch
    while(teleStr[i] != '|')
        tmpStr += teleStr[i++];
    ui->pitch_LE->setText(tmpStr);
    tmpStr = "";
    i++;

    //  Get yaw
    while(teleStr[i] != '\n')
        tmpStr += teleStr[i++];
    ui->yaw_LE->setText(tmpStr);
    tmpStr = "";

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
    //while (respStr[it++] != ':');
//it=7;
    for (uint16_t i = 10; i <170; i++)
        image.LinePolar((double)i, (double)((int)respStr.at(i-10+it).toAscii()) * scale);

    // Show the image
    ui->radarPlot->showImage( image.GetMatImg() );
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    blank(200, 400)
{
    ui->setupUi(this);

    //  Allows to execute custom routine when new client connects to telemetry socket
    connect(&tcpStelemetry, SIGNAL(newConnection()),
            this, SLOT(acceptCliTelemetry()));
    tcpStelemetry.listen(QHostAddress::Any, P_TELEMETRY);
    LogLine("Listening on telemetry socket " + QString::number(P_TELEMETRY) + "\n");
    tcpCliTelemetry = NULL;

    //  Allows to execute custom routine when new clients client connects to command socket
    connect(&tcpScommands, SIGNAL(newConnection()),
            this, SLOT(acceptCliCommands()));
    tcpScommands.listen(QHostAddress::Any, P_COMMANDS);
    LogLine("Listening on commands socket " + QString::number(P_COMMANDS) + "\n");
    tcpCliCommands = NULL;

    //  Add basic lines to the plot - constructs background
    blank.SetCenter(200, 200);
    blank.Circle(30*scale);
    blank.Text("30cm", cv::Point2i(30*scale-20,2));
    blank.Circle(60*scale);
    blank.Text("60cm", cv::Point2i(60*scale-20,2));
    blank.Circle(80*scale);
    blank.Text("80cm", cv::Point2i(80*scale-20,2));

    // Show the image
    ui->radarPlot->showImage( blank.GetMatImg() );
}

void MainWindow::LogLine(QString arg)
{
    ui->log->setPlainText(ui->log->toPlainText() + arg);
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
 * @brief Handles "clicked" event for "Scan" button
 * Sends 'radar scan' command to the "command stream"; if opened
 */
void MainWindow::on_scan_bt_clicked()
{
    //  Check if there ary any client connected
    if (tcpCliCommands != NULL)
    {
        char command[50] = {};
        //  length of arguments bytes are in little endian, MSB first
        snprintf(command, 50, "V125:0:%c%c::%c%c:%c\r\n", 1, 0, RADAR_UID, RADAR_SCAN, 0);
        tcpCliCommands->write(command,17);
        LogLine("Sent command:> " + QString(command));
    }
}

/**
 * @brief Accept new connection on 'telemery' socket
 */
void MainWindow::acceptCliTelemetry(void)
{
    tcpCliTelemetry = tcpStelemetry.nextPendingConnection();
    LogLine("Have client on telemetry: " + tcpCliTelemetry->peerAddress().toString() +"\n");

    connect(tcpCliTelemetry, SIGNAL(readyRead()),
            this, SLOT(readDataTelemetry()));
}

/**
 * @brief Accept new connection on 'commands' socket
 */
void MainWindow::acceptCliCommands(void)
{
    tcpCliCommands = tcpScommands.nextPendingConnection();
    LogLine("Have client on commands: " + tcpCliCommands->peerAddress().toString() +"\n");

    connect(tcpCliCommands, SIGNAL(readyRead()),
            this, SLOT(readDataCommands()));
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
  ParseTelemetry(QString(buffer));
}

/**
 * @brief Called every time new data comes on the 'commands' socket. Functions
 * calls parser to interpret incoming data and update UI elements with it.
 */
void MainWindow::readDataCommands(void)
{
  char buffer[1024] = {0};
  tcpCliCommands->read(buffer, tcpCliCommands->bytesAvailable());
  //LogLine("COMMANDS: " + QString(buffer));
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
