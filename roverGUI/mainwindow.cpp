#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <iostream>

#include <QChar>
#include <QDebug>
#include <QTimer>
#include <QTextStream>


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
    rpDef(200, 200, cv::Scalar(0x45, 0x45, 0x45)),
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

    //  Make default rp plot
    rpDef.SetRange(-100, 100, -100, 100);
    rpDef.LineCartesian(cv::Point2d(-70, 0), cv::Point2d(-20, 0), COLOR_WHITE);
    rpDef.LineCartesian(cv::Point2d( 70, 0), cv::Point2d( 20, 0), COLOR_WHITE);
    rpDef.LineCartesian(cv::Point2d(-20, -20), cv::Point2d(-40, 0), COLOR_WHITE);
    rpDef.LineCartesian(cv::Point2d( 20, -20), cv::Point2d( 40, 0), COLOR_WHITE);
    rpDef.LineCartesian(cv::Point2d(-20, -20), cv::Point2d(-10, -20), COLOR_WHITE);
    rpDef.LineCartesian(cv::Point2d( 20, -20), cv::Point2d(10, -20), COLOR_WHITE);
    rpDef.Circle(5, cv::Point2d(0,0), COLOR_WHITE);

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

    this->installEventFilter(this);
    ui->tabWidget->installEventFilter(this);

    sendStatus = COMMANDS_RESET;
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
        sendStatus = COMMANDS_RESET;
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
                                     ui->missPer_LE->text().toLongLong());
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
///        Block auto-repeat functionality while holding a key
///-----------------------------------------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //  While holding key QT emits multiple events, use this to filter them out
    if (event->isAutoRepeat())
        return;

    if (event->key() == Qt::Key_W)
        on_fwd_PB_pressed();
    if (event->key() == Qt::Key_A)
        on_left_PB_pressed();
    if (event->key() == Qt::Key_S)
        on_bck_PB_pressed();
    if (event->key() == Qt::Key_D)
        on_right_PB_pressed();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    //  While holding key QT emits multiple events, use this to filter them out
    if (event->isAutoRepeat())
        return;

    if (event->key() == Qt::Key_W)
        on_fwd_PB_released();
    if (event->key() == Qt::Key_A)
        on_left_PB_released();
    if (event->key() == Qt::Key_S)
        on_bck_PB_released();
    if (event->key() == Qt::Key_D)
        on_right_PB_released();

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

    //  Allow using filter on vehicle log
    if (holder == ui->vel_TE)
    {
        //  To prevent stack smashing, reset logs once they reach 6000 characters
        if ((vhLog.length()+arg.length()) >= 6000)
            vhLog = "";

        vhLog += arg + '\n';

        //  Check filtering setting
        if (ui->filter_CB->currentText() == "All")
            holder->setPlainText(vhLog);
        else
        {
            QStringList source = vhLog.split("\n");
            holder->setPlainText("");

            for (QString line : source)
            {
                if (line.contains(ui->filter_CB->currentText(), Qt::CaseSensitive))
                    holder->setPlainText(holder->toPlainText()+line+'\n');
            }
        }
    }
    else
    //  Add new line to the log
    holder->setPlainText(holder->toPlainText() + arg + '\n');
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


