#include "mainwindow.h"

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
    ParseTelemetry(QString(buffer));
  else if ((buffer[0] == '2') && (buffer[1] == '*'))
    ParseEventLog(QString(buffer)); //Leave leading 11:
  else if ((buffer[0] == '3') && (buffer[1] == '*'))
    ParseTaskEntry(QString(buffer));
}
/**
 * @brief Triggered when TCP 'telemtry' socket is closed
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
 * @brief Triggered when TCP 'commands' socket is closed
 */
void MainWindow::sockCommClose()
{
    LogLine("Comm closing");
    ui->commands_L->setStyleSheet("background-color:rgb(255, 0, 4);\ncolor:#454545;\nborder-radius:3px;");
}
