#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <iostream>

#include <QComboBox>
#include <QPushButton>
#include <QFrame>
#include <QWidget>

#include <vector>

#include "ocvgraph.h"
#include "cqtopencvviewergl.h"
#include "QPlainTextEdit"
#include "roverinterface.h"
#include "missionentry.h"

//  Status of sending command
#define COMMANDS_ACK    1
#define COMMANDS_NACK   2
#define COMMANDS_RESET  3


namespace Ui {
class MainWindow;
class MissionEntry;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void LogLine(QString arg, QPlainTextEdit *holder = 0);
    void ParseTelemetry(QString teleStr);
    void ParseEventLog(QString teleStr);
    void ParseTaskEntry(QString teleStr);
    bool ParseCommandResp(QString respStr);
    void UpdateRPPlot(double roll, double pitch);
    void EventUpdateGUI(Events events, uint8_t libUID);
    void AppendToGraph(OCVGraph &graph, double old, double val, CQtOpenCVViewerGl *renderer);
    bool SendCommand(const char *command, uint16_t commandLen);
protected:
    //bool eventFilter(QObject *watched, QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private slots:
    void on_scan_bt_clicked();
    void acceptCliTelemetry(void);
    void acceptCliCommands(void);
    void readDataTelemetry(void);
    void readDataCommands(void);
    void on_clrLog_clicked();
    void sendNext(void);
    void HaltEngines();

    void on_reboot_BT_clicked();

    void on_inReb_PB_clicked();

    void on_clrVel_PB_clicked();


    void on_updateTime_SB_editingFinished();

    void on_imuSamp_CB_toggled(bool checked);

    void sockCommClose();

    void sockTelClose();

    void on_commReb_PB_clicked();

    void on_commands_L_2_clicked();

    void on_addTask_PB_clicked();

    void on_evlogReb_PB_clicked();

    void on_evlogUpd_PB_clicked();

    void on_tsUpd_PB_clicked();

    void UpdateIDs();

    void on_schedMiss_PB_clicked();

    void on_mStart_LE_textChanged(const QString &arg1);

    void on_engReb_PB_clicked();

    void on_missPer_CB_clicked(bool checked);

    void on_fwd_PB_pressed();

    void on_fwd_PB_released();

    void on_left_PB_pressed();

    void on_right_PB_pressed();

    void on_right_PB_released();

    void on_left_PB_released();

    void on_bck_PB_pressed();

    void on_bck_PB_released();

    void on_platReb_PB_clicked();

    void on_clearStat_PB_clicked();

    void on_filter_CB_currentTextChanged(const QString &arg1);

    void on_inSofReb_PB_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *socketTimer;
    QTcpServer tcpStelemetry;
    QTcpServer tcpScommands;
    QTcpSocket* tcpCliTelemetry;
    QTcpSocket* tcpCliCommands;
    QTcpSocket *tcpServerConnection;
    QTimer *sendTimer;
    QString vhLog;

    //  Setting up graph plotting in openCV
    OCVGraph blank,
             latencyGraph,
             rollGraph,
             pitchGraph,
             yawGraph,
             rpDef;

    QGraphicsView   *pinv[10];
    QLabel          *labOverview[10];
    QLabel          *labInstruments[10];

    //  Quality of service (QoS)parameters
    uint32_t _sentReq;
    uint32_t _ackReq;
    uint8_t sendStatus;

    //  Dynamicall created GUI objects for mission planning
    std::vector<MissionEntry*> mEntries;
    uint8_t entries = 0;
};

#endif // MAINWINDOW_H
