#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QGraphicsView>

#include "ocvgraph.h"
#include "cqtopencvviewergl.h"
#include "QPlainTextEdit"
#include "roverinterface.h"



namespace Ui {
class MainWindow;
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
    void ParseCommandResp(QString respStr);
    void EventUpdateGUI(Events events, uint8_t libUID);
    void AppendToGraph(OCVGraph &graph, double old, double val, CQtOpenCVViewerGl *renderer);
    bool SendCommand(char *command, uint16_t commandLen);

private slots:
    void on_scan_bt_clicked();
    void acceptCliTelemetry(void);
    void acceptCliCommands(void);
    void readDataTelemetry(void);
    void readDataCommands(void);
    void on_clrLog_clicked();

    void on_reboot_BT_clicked();

    void on_inReb_PB_clicked();

    void on_clrVel_PB_clicked();


    void on_updateTime_SB_editingFinished();

    void on_imuSamp_CB_toggled(bool checked);

    void sockCommClose();

    void sockTelClose();

private:
    Ui::MainWindow *ui;
    QTimer *socketTimer;
    QTcpServer tcpStelemetry;
    QTcpServer tcpScommands;
    QTcpSocket* tcpCliTelemetry;
    QTcpSocket* tcpCliCommands;
    QTcpSocket *tcpServerConnection;

    //  Setting up graph plotting in openCV
    OCVGraph blank,
             latencyGraph,
             rollGraph,
             pitchGraph,
             yawGraph;

    QGraphicsView *pinv[10];
};

#endif // MAINWINDOW_H
