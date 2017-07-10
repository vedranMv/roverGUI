/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>
#include "cqtopencvviewergl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *reboot_BT;
    QGroupBox *uptime_GB;
    QLabel *deltams_L;
    QLabel *ms_L;
    QLabel *ms_L_2;
    QLineEdit *utime_LE;
    QLineEdit *deltams_LE;
    QGroupBox *orientation_GB;
    QLineEdit *roll_LE;
    QLabel *roll_L;
    QLineEdit *pitch_LE;
    QLabel *pitch_L;
    QLabel *yaw_L;
    QLineEdit *yaw_LE;
    QGroupBox *status_GB;
    QLabel *platform_L;
    QLabel *engines_L;
    QLabel *comm_L;
    QLabel *radar_L;
    QLabel *inertial_L;
    QLabel *hardware_L;
    QPushButton *scan_bt;
    CQtOpenCVViewerGl *radarPlot;
    QGroupBox *steering;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QTabWidget *log_TW;
    QWidget *guilog_TAB;
    QPushButton *clrLog;
    QPlainTextEdit *log;
    QWidget *vel_TAB;
    QPlainTextEdit *vel_TE;
    QPushButton *clrVel_PB;
    QGroupBox *latency_GB;
    CQtOpenCVViewerGl *latencyPlot;
    QDoubleSpinBox *updateTime_SB;
    QLabel *updateTime_L;
    QWidget *tab_2;
    QToolBox *toolBox;
    QWidget *inertial_TB;
    QLabel *inertial_L_2;
    QPushButton *inReb_PB;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    CQtOpenCVViewerGl *rollPlot;
    QWidget *tab_5;
    CQtOpenCVViewerGl *pitchPlot;
    QWidget *tab_6;
    CQtOpenCVViewerGl *yawPlot;
    QCheckBox *imuSamp_CB;
    QGraphicsView *inerPinv_GV;
    QWidget *platform_TB;
    QLabel *platform_L_2;
    QGraphicsView *platPinv_GV;
    QGroupBox *commI_GB;
    QPushButton *commReb_PB;
    QGraphicsView *commPinv_GV;
    QLabel *comm_L_2;
    QGroupBox *tsI_GB;
    QPushButton *tsUpd_PB;
    QGraphicsView *tsPinv_GV;
    QLabel *ts_L_2;
    QPlainTextEdit *tsLog_TE;
    QGroupBox *evlog_GB;
    QPushButton *evlogReb_PB;
    QGraphicsView *evlogPinv_GV;
    QLabel *evlog_L_2;
    QPushButton *evlogUpd_PB;
    QPushButton *platReb_PB;
    QLabel *softReb_L;
    QWidget *radar_TB;
    QLabel *radar_L_2;
    QGraphicsView *radPinv_GV;
    QWidget *engines_TB;
    QLabel *engines_L_2;
    QGraphicsView *engPinv_GV;
    QWidget *tab_3;
    QLabel *mStart_L;
    QLineEdit *mStart_LE;
    QGroupBox *missionT_GB;
    QPushButton *addTask_PB;
    QScrollArea *missionScroll_SA;
    QWidget *scrollAreaWidgetContents;
    QPushButton *schedMiss_PB;
    QCheckBox *checkBox;
    QLabel *mUtime_L_2;
    QLineEdit *mUtime_LE_2;
    QLabel *telemetry_L;
    QLabel *commands_L;
    QPushButton *commands_L_2;
    QLabel *mUtime_L;
    QLineEdit *mUtime_LE;
    QLabel *qos_L;
    QProgressBar *qos_PrB;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(751, 428);
        MainWindow->setMouseTracking(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 40, 751, 391));
        tabWidget->setMouseTracking(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        reboot_BT = new QPushButton(tab);
        reboot_BT->setObjectName(QStringLiteral("reboot_BT"));
        reboot_BT->setGeometry(QRect(90, 0, 80, 22));
        uptime_GB = new QGroupBox(tab);
        uptime_GB->setObjectName(QStringLiteral("uptime_GB"));
        uptime_GB->setGeometry(QRect(140, 260, 131, 91));
        uptime_GB->setAlignment(Qt::AlignCenter);
        deltams_L = new QLabel(uptime_GB);
        deltams_L->setObjectName(QStringLiteral("deltams_L"));
        deltams_L->setGeometry(QRect(10, 60, 16, 21));
        ms_L = new QLabel(uptime_GB);
        ms_L->setObjectName(QStringLiteral("ms_L"));
        ms_L->setGeometry(QRect(110, 30, 21, 21));
        ms_L_2 = new QLabel(uptime_GB);
        ms_L_2->setObjectName(QStringLiteral("ms_L_2"));
        ms_L_2->setGeometry(QRect(110, 60, 21, 21));
        utime_LE = new QLineEdit(uptime_GB);
        utime_LE->setObjectName(QStringLiteral("utime_LE"));
        utime_LE->setEnabled(true);
        utime_LE->setGeometry(QRect(20, 30, 81, 22));
        deltams_LE = new QLineEdit(uptime_GB);
        deltams_LE->setObjectName(QStringLiteral("deltams_LE"));
        deltams_LE->setEnabled(true);
        deltams_LE->setGeometry(QRect(20, 60, 81, 22));
        orientation_GB = new QGroupBox(tab);
        orientation_GB->setObjectName(QStringLiteral("orientation_GB"));
        orientation_GB->setGeometry(QRect(0, 260, 131, 91));
        orientation_GB->setAlignment(Qt::AlignCenter);
        roll_LE = new QLineEdit(orientation_GB);
        roll_LE->setObjectName(QStringLiteral("roll_LE"));
        roll_LE->setEnabled(true);
        roll_LE->setGeometry(QRect(30, 20, 101, 22));
        roll_L = new QLabel(orientation_GB);
        roll_L->setObjectName(QStringLiteral("roll_L"));
        roll_L->setGeometry(QRect(10, 20, 59, 21));
        pitch_LE = new QLineEdit(orientation_GB);
        pitch_LE->setObjectName(QStringLiteral("pitch_LE"));
        pitch_LE->setEnabled(true);
        pitch_LE->setGeometry(QRect(30, 40, 101, 22));
        pitch_L = new QLabel(orientation_GB);
        pitch_L->setObjectName(QStringLiteral("pitch_L"));
        pitch_L->setGeometry(QRect(10, 40, 59, 21));
        yaw_L = new QLabel(orientation_GB);
        yaw_L->setObjectName(QStringLiteral("yaw_L"));
        yaw_L->setGeometry(QRect(10, 60, 59, 21));
        yaw_LE = new QLineEdit(orientation_GB);
        yaw_LE->setObjectName(QStringLiteral("yaw_LE"));
        yaw_LE->setEnabled(true);
        yaw_LE->setGeometry(QRect(30, 60, 101, 22));
        status_GB = new QGroupBox(tab);
        status_GB->setObjectName(QStringLiteral("status_GB"));
        status_GB->setGeometry(QRect(420, 0, 151, 91));
        status_GB->setAlignment(Qt::AlignCenter);
        platform_L = new QLabel(status_GB);
        platform_L->setObjectName(QStringLiteral("platform_L"));
        platform_L->setGeometry(QRect(10, 30, 59, 14));
        platform_L->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        platform_L->setAlignment(Qt::AlignCenter);
        engines_L = new QLabel(status_GB);
        engines_L->setObjectName(QStringLiteral("engines_L"));
        engines_L->setGeometry(QRect(10, 50, 59, 14));
        engines_L->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        engines_L->setAlignment(Qt::AlignCenter);
        comm_L = new QLabel(status_GB);
        comm_L->setObjectName(QStringLiteral("comm_L"));
        comm_L->setGeometry(QRect(10, 70, 59, 14));
        comm_L->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        comm_L->setAlignment(Qt::AlignCenter);
        radar_L = new QLabel(status_GB);
        radar_L->setObjectName(QStringLiteral("radar_L"));
        radar_L->setGeometry(QRect(80, 30, 59, 14));
        radar_L->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        radar_L->setAlignment(Qt::AlignCenter);
        inertial_L = new QLabel(status_GB);
        inertial_L->setObjectName(QStringLiteral("inertial_L"));
        inertial_L->setGeometry(QRect(80, 50, 59, 14));
        inertial_L->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        inertial_L->setAlignment(Qt::AlignCenter);
        hardware_L = new QLabel(status_GB);
        hardware_L->setObjectName(QStringLiteral("hardware_L"));
        hardware_L->setGeometry(QRect(80, 70, 59, 14));
        hardware_L->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        hardware_L->setAlignment(Qt::AlignCenter);
        scan_bt = new QPushButton(tab);
        scan_bt->setObjectName(QStringLiteral("scan_bt"));
        scan_bt->setGeometry(QRect(0, 0, 80, 22));
        radarPlot = new CQtOpenCVViewerGl(tab);
        radarPlot->setObjectName(QStringLiteral("radarPlot"));
        radarPlot->setGeometry(QRect(10, 30, 400, 200));
        steering = new QGroupBox(tab);
        steering->setObjectName(QStringLiteral("steering"));
        steering->setGeometry(QRect(580, 0, 141, 91));
        steering->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(steering);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 30, 31, 22));
        pushButton->setFlat(false);
        pushButton_2 = new QPushButton(steering);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 60, 31, 22));
        pushButton_2->setFlat(false);
        pushButton_3 = new QPushButton(steering);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(100, 60, 31, 22));
        pushButton_3->setFlat(false);
        log_TW = new QTabWidget(tab);
        log_TW->setObjectName(QStringLiteral("log_TW"));
        log_TW->setGeometry(QRect(410, 100, 331, 261));
        guilog_TAB = new QWidget();
        guilog_TAB->setObjectName(QStringLiteral("guilog_TAB"));
        clrLog = new QPushButton(guilog_TAB);
        clrLog->setObjectName(QStringLiteral("clrLog"));
        clrLog->setGeometry(QRect(250, 0, 80, 22));
        log = new QPlainTextEdit(guilog_TAB);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(0, 0, 331, 231));
        log->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        log->setReadOnly(true);
        log->setCenterOnScroll(false);
        log_TW->addTab(guilog_TAB, QString());
        log->raise();
        clrLog->raise();
        vel_TAB = new QWidget();
        vel_TAB->setObjectName(QStringLiteral("vel_TAB"));
        vel_TE = new QPlainTextEdit(vel_TAB);
        vel_TE->setObjectName(QStringLiteral("vel_TE"));
        vel_TE->setGeometry(QRect(0, 0, 331, 231));
        clrVel_PB = new QPushButton(vel_TAB);
        clrVel_PB->setObjectName(QStringLiteral("clrVel_PB"));
        clrVel_PB->setGeometry(QRect(250, 0, 80, 22));
        log_TW->addTab(vel_TAB, QString());
        latency_GB = new QGroupBox(tab);
        latency_GB->setObjectName(QStringLiteral("latency_GB"));
        latency_GB->setGeometry(QRect(290, 260, 101, 91));
        latency_GB->setAlignment(Qt::AlignCenter);
        latencyPlot = new CQtOpenCVViewerGl(latency_GB);
        latencyPlot->setObjectName(QStringLiteral("latencyPlot"));
        latencyPlot->setGeometry(QRect(0, 20, 100, 50));
        updateTime_SB = new QDoubleSpinBox(tab);
        updateTime_SB->setObjectName(QStringLiteral("updateTime_SB"));
        updateTime_SB->setGeometry(QRect(340, 0, 71, 23));
        updateTime_SB->setMinimum(0.5);
        updateTime_SB->setValue(1.5);
        updateTime_L = new QLabel(tab);
        updateTime_L->setObjectName(QStringLiteral("updateTime_L"));
        updateTime_L->setGeometry(QRect(248, 0, 91, 21));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        toolBox = new QToolBox(tab_2);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(0, 0, 751, 361));
        toolBox->setMouseTracking(true);
        inertial_TB = new QWidget();
        inertial_TB->setObjectName(QStringLiteral("inertial_TB"));
        inertial_TB->setGeometry(QRect(0, 0, 751, 249));
        inertial_L_2 = new QLabel(inertial_TB);
        inertial_L_2->setObjectName(QStringLiteral("inertial_L_2"));
        inertial_L_2->setGeometry(QRect(20, 2, 150, 14));
        inertial_L_2->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        inReb_PB = new QPushButton(inertial_TB);
        inReb_PB->setObjectName(QStringLiteral("inReb_PB"));
        inReb_PB->setGeometry(QRect(660, 0, 80, 22));
        tabWidget_2 = new QTabWidget(inertial_TB);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(0, 20, 401, 221));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        rollPlot = new CQtOpenCVViewerGl(tab_4);
        rollPlot->setObjectName(QStringLiteral("rollPlot"));
        rollPlot->setGeometry(QRect(0, 0, 400, 189));
        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        pitchPlot = new CQtOpenCVViewerGl(tab_5);
        pitchPlot->setObjectName(QStringLiteral("pitchPlot"));
        pitchPlot->setGeometry(QRect(0, 0, 400, 189));
        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        yawPlot = new CQtOpenCVViewerGl(tab_6);
        yawPlot->setObjectName(QStringLiteral("yawPlot"));
        yawPlot->setGeometry(QRect(0, 0, 400, 189));
        tabWidget_2->addTab(tab_6, QString());
        imuSamp_CB = new QCheckBox(inertial_TB);
        imuSamp_CB->setObjectName(QStringLiteral("imuSamp_CB"));
        imuSamp_CB->setGeometry(QRect(180, 2, 131, 16));
        imuSamp_CB->setChecked(true);
        inerPinv_GV = new QGraphicsView(inertial_TB);
        inerPinv_GV->setObjectName(QStringLiteral("inerPinv_GV"));
        inerPinv_GV->setGeometry(QRect(0, 0, 18, 18));
        inerPinv_GV->setMouseTracking(true);
        inerPinv_GV->setToolTipDuration(-1);
        inerPinv_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        inerPinv_GV->setFrameShape(QFrame::NoFrame);
        toolBox->addItem(inertial_TB, QStringLiteral("MPU9250"));
        platform_TB = new QWidget();
        platform_TB->setObjectName(QStringLiteral("platform_TB"));
        platform_TB->setGeometry(QRect(0, 0, 751, 249));
        platform_L_2 = new QLabel(platform_TB);
        platform_L_2->setObjectName(QStringLiteral("platform_L_2"));
        platform_L_2->setGeometry(QRect(20, 2, 150, 14));
        platform_L_2->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        platPinv_GV = new QGraphicsView(platform_TB);
        platPinv_GV->setObjectName(QStringLiteral("platPinv_GV"));
        platPinv_GV->setGeometry(QRect(0, 0, 18, 18));
        platPinv_GV->setMouseTracking(true);
        platPinv_GV->setToolTipDuration(-1);
        platPinv_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        platPinv_GV->setFrameShape(QFrame::NoFrame);
        commI_GB = new QGroupBox(platform_TB);
        commI_GB->setObjectName(QStringLiteral("commI_GB"));
        commI_GB->setGeometry(QRect(10, 30, 191, 181));
        commI_GB->setAlignment(Qt::AlignCenter);
        commReb_PB = new QPushButton(commI_GB);
        commReb_PB->setObjectName(QStringLiteral("commReb_PB"));
        commReb_PB->setGeometry(QRect(90, 40, 80, 22));
        commPinv_GV = new QGraphicsView(commI_GB);
        commPinv_GV->setObjectName(QStringLiteral("commPinv_GV"));
        commPinv_GV->setGeometry(QRect(10, 20, 18, 18));
        commPinv_GV->setMouseTracking(true);
        commPinv_GV->setToolTipDuration(-1);
        commPinv_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        commPinv_GV->setFrameShape(QFrame::NoFrame);
        comm_L_2 = new QLabel(commI_GB);
        comm_L_2->setObjectName(QStringLiteral("comm_L_2"));
        comm_L_2->setGeometry(QRect(30, 22, 150, 14));
        comm_L_2->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        tsI_GB = new QGroupBox(platform_TB);
        tsI_GB->setObjectName(QStringLiteral("tsI_GB"));
        tsI_GB->setGeometry(QRect(210, 30, 331, 211));
        tsI_GB->setAlignment(Qt::AlignCenter);
        tsUpd_PB = new QPushButton(tsI_GB);
        tsUpd_PB->setObjectName(QStringLiteral("tsUpd_PB"));
        tsUpd_PB->setGeometry(QRect(240, 20, 80, 22));
        tsPinv_GV = new QGraphicsView(tsI_GB);
        tsPinv_GV->setObjectName(QStringLiteral("tsPinv_GV"));
        tsPinv_GV->setGeometry(QRect(10, 20, 18, 18));
        tsPinv_GV->setMouseTracking(true);
        tsPinv_GV->setToolTipDuration(-1);
        tsPinv_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        tsPinv_GV->setFrameShape(QFrame::NoFrame);
        ts_L_2 = new QLabel(tsI_GB);
        ts_L_2->setObjectName(QStringLiteral("ts_L_2"));
        ts_L_2->setGeometry(QRect(30, 22, 150, 14));
        ts_L_2->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        tsLog_TE = new QPlainTextEdit(tsI_GB);
        tsLog_TE->setObjectName(QStringLiteral("tsLog_TE"));
        tsLog_TE->setGeometry(QRect(0, 50, 331, 161));
        tsLog_TE->setStyleSheet(QStringLiteral("background-color:transparent;"));
        evlog_GB = new QGroupBox(platform_TB);
        evlog_GB->setObjectName(QStringLiteral("evlog_GB"));
        evlog_GB->setGeometry(QRect(550, 30, 191, 181));
        evlog_GB->setAlignment(Qt::AlignCenter);
        evlogReb_PB = new QPushButton(evlog_GB);
        evlogReb_PB->setObjectName(QStringLiteral("evlogReb_PB"));
        evlogReb_PB->setGeometry(QRect(90, 40, 80, 22));
        evlogPinv_GV = new QGraphicsView(evlog_GB);
        evlogPinv_GV->setObjectName(QStringLiteral("evlogPinv_GV"));
        evlogPinv_GV->setGeometry(QRect(10, 20, 18, 18));
        evlogPinv_GV->setMouseTracking(true);
        evlogPinv_GV->setToolTipDuration(-1);
        evlogPinv_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        evlogPinv_GV->setFrameShape(QFrame::NoFrame);
        evlog_L_2 = new QLabel(evlog_GB);
        evlog_L_2->setObjectName(QStringLiteral("evlog_L_2"));
        evlog_L_2->setGeometry(QRect(30, 22, 150, 14));
        evlog_L_2->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        evlogUpd_PB = new QPushButton(evlog_GB);
        evlogUpd_PB->setObjectName(QStringLiteral("evlogUpd_PB"));
        evlogUpd_PB->setGeometry(QRect(90, 70, 80, 22));
        platReb_PB = new QPushButton(platform_TB);
        platReb_PB->setObjectName(QStringLiteral("platReb_PB"));
        platReb_PB->setGeometry(QRect(660, 0, 80, 22));
        softReb_L = new QLabel(platform_TB);
        softReb_L->setObjectName(QStringLiteral("softReb_L"));
        softReb_L->setGeometry(QRect(578, 0, 71, 21));
        toolBox->addItem(platform_TB, QStringLiteral("Platform"));
        radar_TB = new QWidget();
        radar_TB->setObjectName(QStringLiteral("radar_TB"));
        radar_TB->setGeometry(QRect(0, 0, 751, 249));
        radar_L_2 = new QLabel(radar_TB);
        radar_L_2->setObjectName(QStringLiteral("radar_L_2"));
        radar_L_2->setGeometry(QRect(20, 2, 150, 14));
        radar_L_2->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        radPinv_GV = new QGraphicsView(radar_TB);
        radPinv_GV->setObjectName(QStringLiteral("radPinv_GV"));
        radPinv_GV->setGeometry(QRect(0, 0, 18, 18));
        radPinv_GV->setMouseTracking(true);
        radPinv_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        radPinv_GV->setFrameShape(QFrame::NoFrame);
        toolBox->addItem(radar_TB, QStringLiteral("Radar"));
        engines_TB = new QWidget();
        engines_TB->setObjectName(QStringLiteral("engines_TB"));
        engines_TB->setGeometry(QRect(0, 0, 751, 249));
        engines_L_2 = new QLabel(engines_TB);
        engines_L_2->setObjectName(QStringLiteral("engines_L_2"));
        engines_L_2->setGeometry(QRect(20, 2, 150, 14));
        engines_L_2->setStyleSheet(QStringLiteral("background-color:rgb(126, 189, 189);"));
        engPinv_GV = new QGraphicsView(engines_TB);
        engPinv_GV->setObjectName(QStringLiteral("engPinv_GV"));
        engPinv_GV->setGeometry(QRect(0, 0, 18, 18));
        engPinv_GV->setMouseTracking(true);
        engPinv_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        engPinv_GV->setFrameShape(QFrame::NoFrame);
        toolBox->addItem(engines_TB, QStringLiteral("Engines"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        mStart_L = new QLabel(tab_3);
        mStart_L->setObjectName(QStringLiteral("mStart_L"));
        mStart_L->setGeometry(QRect(10, 10, 311, 21));
        mStart_L->setStyleSheet(QStringLiteral("color:#FF0000;"));
        mStart_LE = new QLineEdit(tab_3);
        mStart_LE->setObjectName(QStringLiteral("mStart_LE"));
        mStart_LE->setEnabled(true);
        mStart_LE->setGeometry(QRect(160, 10, 113, 22));
        missionT_GB = new QGroupBox(tab_3);
        missionT_GB->setObjectName(QStringLiteral("missionT_GB"));
        missionT_GB->setGeometry(QRect(0, 40, 741, 311));
        missionT_GB->setStyleSheet(QStringLiteral(""));
        addTask_PB = new QPushButton(missionT_GB);
        addTask_PB->setObjectName(QStringLiteral("addTask_PB"));
        addTask_PB->setGeometry(QRect(30, 270, 80, 22));
        missionScroll_SA = new QScrollArea(missionT_GB);
        missionScroll_SA->setObjectName(QStringLiteral("missionScroll_SA"));
        missionScroll_SA->setGeometry(QRect(0, 20, 741, 231));
        missionScroll_SA->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        missionScroll_SA->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 739, 229));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        missionScroll_SA->setWidget(scrollAreaWidgetContents);
        schedMiss_PB = new QPushButton(missionT_GB);
        schedMiss_PB->setObjectName(QStringLiteral("schedMiss_PB"));
        schedMiss_PB->setGeometry(QRect(620, 260, 111, 41));
        checkBox = new QCheckBox(missionT_GB);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(260, 270, 171, 20));
        mUtime_L_2 = new QLabel(tab_3);
        mUtime_L_2->setObjectName(QStringLiteral("mUtime_L_2"));
        mUtime_L_2->setGeometry(QRect(440, 10, 291, 21));
        mUtime_LE_2 = new QLineEdit(tab_3);
        mUtime_LE_2->setObjectName(QStringLiteral("mUtime_LE_2"));
        mUtime_LE_2->setEnabled(true);
        mUtime_LE_2->setGeometry(QRect(590, 10, 111, 22));
        tabWidget->addTab(tab_3, QString());
        telemetry_L = new QLabel(centralWidget);
        telemetry_L->setObjectName(QStringLiteral("telemetry_L"));
        telemetry_L->setGeometry(QRect(580, 10, 71, 20));
        telemetry_L->setStyleSheet(QStringLiteral("background-color:rgb(255, 0, 4);"));
        telemetry_L->setAlignment(Qt::AlignCenter);
        commands_L = new QLabel(centralWidget);
        commands_L->setObjectName(QStringLiteral("commands_L"));
        commands_L->setGeometry(QRect(660, 10, 71, 20));
        commands_L->setStyleSheet(QStringLiteral("background-color:rgb(255, 0, 4);"));
        commands_L->setAlignment(Qt::AlignCenter);
        commands_L_2 = new QPushButton(centralWidget);
        commands_L_2->setObjectName(QStringLiteral("commands_L_2"));
        commands_L_2->setGeometry(QRect(660, 10, 80, 22));
        commands_L_2->setStyleSheet(QStringLiteral("background-color:transparent"));
        commands_L_2->setFlat(true);
        mUtime_L = new QLabel(centralWidget);
        mUtime_L->setObjectName(QStringLiteral("mUtime_L"));
        mUtime_L->setGeometry(QRect(420, 10, 21, 21));
        mUtime_LE = new QLineEdit(centralWidget);
        mUtime_LE->setObjectName(QStringLiteral("mUtime_LE"));
        mUtime_LE->setEnabled(true);
        mUtime_LE->setGeometry(QRect(440, 10, 111, 22));
        qos_L = new QLabel(centralWidget);
        qos_L->setObjectName(QStringLiteral("qos_L"));
        qos_L->setGeometry(QRect(250, 10, 31, 21));
        qos_PrB = new QProgressBar(centralWidget);
        qos_PrB->setObjectName(QStringLiteral("qos_PrB"));
        qos_PrB->setGeometry(QRect(280, 10, 118, 23));
        qos_PrB->setValue(0);
        qos_PrB->setTextVisible(true);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);
        log_TW->setCurrentIndex(0);
        toolBox->setCurrentIndex(3);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rover control", 0));
        reboot_BT->setText(QApplication::translate("MainWindow", "Reboot", 0));
        uptime_GB->setTitle(QApplication::translate("MainWindow", "Up-time", 0));
        deltams_L->setText(QApplication::translate("MainWindow", "\316\224 ", 0));
        ms_L->setText(QApplication::translate("MainWindow", "s", 0));
        ms_L_2->setText(QApplication::translate("MainWindow", "s", 0));
        orientation_GB->setTitle(QApplication::translate("MainWindow", "Orienatation", 0));
        roll_L->setText(QApplication::translate("MainWindow", "R", 0));
        pitch_L->setText(QApplication::translate("MainWindow", "P", 0));
        yaw_L->setText(QApplication::translate("MainWindow", "Y", 0));
        status_GB->setTitle(QApplication::translate("MainWindow", "Status", 0));
        platform_L->setText(QApplication::translate("MainWindow", "Platform", 0));
        engines_L->setText(QApplication::translate("MainWindow", "Engines", 0));
        comm_L->setText(QApplication::translate("MainWindow", "Comm", 0));
        radar_L->setText(QApplication::translate("MainWindow", "Radar", 0));
        inertial_L->setText(QApplication::translate("MainWindow", "Inertial", 0));
        hardware_L->setText(QApplication::translate("MainWindow", "Hardware", 0));
        scan_bt->setText(QApplication::translate("MainWindow", "Scan", 0));
        steering->setTitle(QApplication::translate("MainWindow", "Steering", 0));
        pushButton->setText(QApplication::translate("MainWindow", "^", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "<", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", ">", 0));
        clrLog->setText(QApplication::translate("MainWindow", "Clear", 0));
        log_TW->setTabText(log_TW->indexOf(guilog_TAB), QApplication::translate("MainWindow", "GUI log", 0));
        clrVel_PB->setText(QApplication::translate("MainWindow", "Clear", 0));
        log_TW->setTabText(log_TW->indexOf(vel_TAB), QApplication::translate("MainWindow", "Vehicle event log", 0));
        latency_GB->setTitle(QApplication::translate("MainWindow", "Latency (ms)", 0));
        updateTime_L->setText(QApplication::translate("MainWindow", "Refresh rate(s)", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Overview", 0));
        inertial_L_2->setText(QApplication::translate("MainWindow", "Inertial", 0));
        inReb_PB->setText(QApplication::translate("MainWindow", "Reboot", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "Roll", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("MainWindow", "Pitch", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("MainWindow", "Yaw", 0));
        imuSamp_CB->setText(QApplication::translate("MainWindow", "Enable sampling", 0));
#ifndef QT_NO_TOOLTIP
        inerPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        toolBox->setItemText(toolBox->indexOf(inertial_TB), QApplication::translate("MainWindow", "MPU9250", 0));
        platform_L_2->setText(QApplication::translate("MainWindow", "Platform", 0));
#ifndef QT_NO_TOOLTIP
        platPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        commI_GB->setTitle(QApplication::translate("MainWindow", "Communication", 0));
        commReb_PB->setText(QApplication::translate("MainWindow", "Reboot", 0));
#ifndef QT_NO_TOOLTIP
        commPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        comm_L_2->setText(QApplication::translate("MainWindow", "Communication", 0));
        tsI_GB->setTitle(QApplication::translate("MainWindow", "Task scheduler", 0));
        tsUpd_PB->setText(QApplication::translate("MainWindow", "Update", 0));
#ifndef QT_NO_TOOLTIP
        tsPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        ts_L_2->setText(QApplication::translate("MainWindow", "Task scheduler", 0));
        evlog_GB->setTitle(QApplication::translate("MainWindow", "Event logger", 0));
        evlogReb_PB->setText(QApplication::translate("MainWindow", "Reboot", 0));
#ifndef QT_NO_TOOLTIP
        evlogPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        evlog_L_2->setText(QApplication::translate("MainWindow", "Event logger", 0));
        evlogUpd_PB->setText(QApplication::translate("MainWindow", "Update", 0));
        platReb_PB->setText(QApplication::translate("MainWindow", "Reboot", 0));
        softReb_L->setText(QApplication::translate("MainWindow", "Soft reboot", 0));
        toolBox->setItemText(toolBox->indexOf(platform_TB), QApplication::translate("MainWindow", "Platform", 0));
        radar_L_2->setText(QApplication::translate("MainWindow", "Radar", 0));
#ifndef QT_NO_TOOLTIP
        radPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        toolBox->setItemText(toolBox->indexOf(radar_TB), QApplication::translate("MainWindow", "Radar", 0));
        engines_L_2->setText(QApplication::translate("MainWindow", "Engines", 0));
#ifndef QT_NO_TOOLTIP
        engPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        toolBox->setItemText(toolBox->indexOf(engines_TB), QApplication::translate("MainWindow", "Engines", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Instruments", 0));
        mStart_L->setText(QApplication::translate("MainWindow", "Mission starting time T=                                ms", 0));
        missionT_GB->setTitle(QApplication::translate("MainWindow", "Mission tasks", 0));
        addTask_PB->setText(QApplication::translate("MainWindow", "Add task", 0));
        schedMiss_PB->setText(QApplication::translate("MainWindow", "Schedule\n"
"mission", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Create periodic mission", 0));
        mUtime_L_2->setText(QApplication::translate("MainWindow", "Current vehice time T=                                 ms", 0));
        mUtime_LE_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Mission planner", 0));
        telemetry_L->setText(QApplication::translate("MainWindow", "Telemetry", 0));
        commands_L->setText(QApplication::translate("MainWindow", "Commands", 0));
        commands_L_2->setText(QString());
        mUtime_L->setText(QApplication::translate("MainWindow", "T=", 0));
        mUtime_LE->setText(QString());
        qos_L->setText(QApplication::translate("MainWindow", "QoS", 0));
        qos_PrB->setFormat(QApplication::translate("MainWindow", "%p%", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
