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
#include <QComboBox>
#include <QPushButton>
#include <QFrame>
#include <QWidget>

#include <vector>

#include "ocvgraph.h"
#include "cqtopencvviewergl.h"
#include "QPlainTextEdit"
#include "roverinterface.h"


namespace Ui {
class MainWindow;
class MissionEntry;
}

class MissionEntry : public QObject
{
    Q_OBJECT
public:
    MissionEntry(uint8_t arg, QWidget *parent): taskF(new QFrame(parent)), dead(false)
    {
        //  Create all elements
        taskL = new QLabel(taskF);
        taskLE = new QLineEdit(taskF);
        taskCB = new QComboBox(taskF);
        taskPB = new QPushButton(taskF);

        //  Configure container frame
        taskF->setMaximumWidth(540);
        taskF->setMaximumHeight(42);
        taskF->setMinimumWidth(540);
        taskF->setMinimumHeight(42);
        taskF->resize(540, 42);
        taskF->setLineWidth(1);
        taskF->setFrameShape(QFrame::Shape::StyledPanel);
        taskF->setFrameShadow(QFrame::Shadow::Sunken);
        taskF->show();

        //  Configure Label
        taskL->setText(QString::number(arg)+". T+                                ms");
        taskL->move(40,10);
        taskL->resize(181,22);
        taskL->show();

        //  Configure LineEdit
        taskLE->move(80,10);
        taskLE->resize(113,22);
        taskLE->show();

        //  Configure PushButton
        taskPB->move(10, 10);
        taskPB->resize(22, 22);
        taskPB->setText("-");
        //  Connect deleting event
        connect(taskPB, SIGNAL(clicked()), this, SLOT(Delete()));

        //  Configure ComboBox
        taskCB->move(230,10);
        taskCB->resize(120, 22);
        for (uint8_t i = 0; i < 8; i++)
        {
            taskCB->addItem(QString(libName[i]));
        }
        connect(taskCB, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateArguments(int)));

    }
    ~MissionEntry()
    {
        delete taskL;
        delete taskLE;
        delete taskCB;
        delete taskPB;
        delete taskF;
    }
    void ChangeIndex(uint8_t newI)
    {
        QStringList oldLabel = taskL->text().split(".");
        taskL->setText(QString::number(newI)+"."+oldLabel[1]);
    }

    QWidget *Container()
    {
        return taskF;
    }

    int LibUID()
    {
        return taskCB->currentIndex();
    }

    int TaskID()
    {
        return taskTCB->currentIndex();
    }

public slots:
    void Delete()
    {
        taskL->deleteLater();
        taskLE->deleteLater();
        taskCB->deleteLater();
        taskPB->deleteLater();
        taskF->deleteLater();
        dead = true;
        emit(Deleted());
    }

    void UpdateArguments(int index)
    {
        taskTCB = new QComboBox(taskF);
        taskTCB->move(360,10);
        taskTCB->resize(120, 22);
        taskTCB->show();
        for (uint8_t i = 0; allTasks[index][i][0] != 0; i++)
            taskTCB->addItem(QString(allTasks[index][i]));
    }

Q_SIGNALS:
    void Deleted();

public:
    QLabel      *taskL;
    QLineEdit   *taskLE;
    QComboBox   *taskCB;
    QComboBox   *taskTCB;
    QFrame      *taskF;
    QPushButton *taskPB;
    bool        dead;
};

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

    void on_commReb_PB_clicked();

    void on_commands_L_2_clicked();

    void on_addTask_PB_clicked();

    void on_evlogReb_PB_clicked();

    void on_evlogUpd_PB_clicked();

    void on_tsUpd_PB_clicked();

    void UpdateIDs();

    void on_schedMiss_PB_clicked();

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

    QGraphicsView   *pinv[10];
    QLabel          *labOverview[10];
    QLabel          *labInstruments[10];

    //  Quality of service (QoS)parameters
    uint32_t _sentReq;
    uint32_t _ackReq;

    //  Dynamicall created GUI objects for mission planning
    std::vector<MissionEntry*> mEntries;
    uint8_t entries = 0;
};

#endif // MAINWINDOW_H
