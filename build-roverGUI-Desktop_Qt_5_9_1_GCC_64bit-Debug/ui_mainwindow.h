/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
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
#include <QtWidgets/QComboBox>
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
    QPushButton *clearStat_PB;
    QPushButton *scan_bt;
    CQtOpenCVViewerGl *radarPlot;
    QGroupBox *steering;
    QPushButton *fwd_PB;
    QPushButton *left_PB;
    QPushButton *right_PB;
    QPushButton *bck_PB;
    QTabWidget *log_TW;
    QWidget *guilog_TAB;
    QPushButton *clrLog;
    QPlainTextEdit *log;
    QWidget *vel_TAB;
    QPlainTextEdit *vel_TE;
    QPushButton *clrVel_PB;
    QComboBox *filter_CB;
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
    QPushButton *inSofReb_PB;
    CQtOpenCVViewerGl *rpPlot;
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
    QPushButton *engReb_PB;
    QWidget *tab_3;
    QLabel *mStart_L;
    QLineEdit *mStart_LE;
    QGroupBox *missionT_GB;
    QPushButton *addTask_PB;
    QScrollArea *missionScroll_SA;
    QWidget *scrollAreaWidgetContents;
    QPushButton *schedMiss_PB;
    QCheckBox *missPer_CB;
    QLineEdit *missPer_LE;
    QLineEdit *missRep_LE;
    QLabel *mUtime_L_2;
    QLineEdit *mUtime_LE_2;
    QGraphicsView *warn_GV;
    QLabel *mUtime_L;
    QLineEdit *mUtime_LE;
    QLabel *qos_L;
    QProgressBar *qos_PrB;
    QGroupBox *groupBox;
    QLabel *telemetry_L;
    QPushButton *commands_L_2;
    QLabel *commands_L;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(751, 428);
        MainWindow->setMouseTracking(true);
        MainWindow->setStyleSheet(QLatin1String("background-color:#454545;\n"
"color:#DDDDDD;"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 40, 751, 391));
        tabWidget->setMouseTracking(true);
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidget->setUsesScrollButtons(false);
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
        ms_L->setGeometry(QRect(110, 30, 16, 21));
        ms_L_2 = new QLabel(uptime_GB);
        ms_L_2->setObjectName(QStringLiteral("ms_L_2"));
        ms_L_2->setGeometry(QRect(110, 60, 16, 21));
        utime_LE = new QLineEdit(uptime_GB);
        utime_LE->setObjectName(QStringLiteral("utime_LE"));
        utime_LE->setEnabled(true);
        utime_LE->setGeometry(QRect(20, 30, 81, 22));
        utime_LE->setFocusPolicy(Qt::NoFocus);
        utime_LE->setReadOnly(true);
        deltams_LE = new QLineEdit(uptime_GB);
        deltams_LE->setObjectName(QStringLiteral("deltams_LE"));
        deltams_LE->setEnabled(true);
        deltams_LE->setGeometry(QRect(20, 60, 81, 22));
        deltams_LE->setFocusPolicy(Qt::NoFocus);
        deltams_LE->setReadOnly(true);
        orientation_GB = new QGroupBox(tab);
        orientation_GB->setObjectName(QStringLiteral("orientation_GB"));
        orientation_GB->setGeometry(QRect(0, 260, 135, 91));
        orientation_GB->setAlignment(Qt::AlignCenter);
        roll_LE = new QLineEdit(orientation_GB);
        roll_LE->setObjectName(QStringLiteral("roll_LE"));
        roll_LE->setEnabled(true);
        roll_LE->setGeometry(QRect(30, 23, 101, 22));
        roll_LE->setFocusPolicy(Qt::NoFocus);
        roll_LE->setReadOnly(true);
        roll_L = new QLabel(orientation_GB);
        roll_L->setObjectName(QStringLiteral("roll_L"));
        roll_L->setGeometry(QRect(10, 23, 15, 21));
        pitch_LE = new QLineEdit(orientation_GB);
        pitch_LE->setObjectName(QStringLiteral("pitch_LE"));
        pitch_LE->setEnabled(true);
        pitch_LE->setGeometry(QRect(30, 43, 101, 22));
        pitch_LE->setFocusPolicy(Qt::NoFocus);
        pitch_LE->setReadOnly(true);
        pitch_L = new QLabel(orientation_GB);
        pitch_L->setObjectName(QStringLiteral("pitch_L"));
        pitch_L->setGeometry(QRect(10, 43, 15, 21));
        yaw_L = new QLabel(orientation_GB);
        yaw_L->setObjectName(QStringLiteral("yaw_L"));
        yaw_L->setGeometry(QRect(10, 63, 15, 21));
        yaw_LE = new QLineEdit(orientation_GB);
        yaw_LE->setObjectName(QStringLiteral("yaw_LE"));
        yaw_LE->setEnabled(true);
        yaw_LE->setGeometry(QRect(30, 63, 101, 22));
        yaw_LE->setFocusPolicy(Qt::NoFocus);
        yaw_LE->setReadOnly(true);
        roll_L->raise();
        pitch_L->raise();
        yaw_L->raise();
        yaw_LE->raise();
        roll_LE->raise();
        pitch_LE->raise();
        status_GB = new QGroupBox(tab);
        status_GB->setObjectName(QStringLiteral("status_GB"));
        status_GB->setGeometry(QRect(420, 0, 151, 91));
        status_GB->setAlignment(Qt::AlignCenter);
        platform_L = new QLabel(status_GB);
        platform_L->setObjectName(QStringLiteral("platform_L"));
        platform_L->setGeometry(QRect(10, 30, 59, 14));
        platform_L->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        platform_L->setAlignment(Qt::AlignCenter);
        engines_L = new QLabel(status_GB);
        engines_L->setObjectName(QStringLiteral("engines_L"));
        engines_L->setGeometry(QRect(10, 50, 59, 14));
        engines_L->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        engines_L->setAlignment(Qt::AlignCenter);
        comm_L = new QLabel(status_GB);
        comm_L->setObjectName(QStringLiteral("comm_L"));
        comm_L->setGeometry(QRect(10, 70, 59, 14));
        comm_L->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        comm_L->setAlignment(Qt::AlignCenter);
        radar_L = new QLabel(status_GB);
        radar_L->setObjectName(QStringLiteral("radar_L"));
        radar_L->setGeometry(QRect(80, 30, 59, 14));
        radar_L->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        radar_L->setAlignment(Qt::AlignCenter);
        inertial_L = new QLabel(status_GB);
        inertial_L->setObjectName(QStringLiteral("inertial_L"));
        inertial_L->setGeometry(QRect(80, 50, 59, 14));
        inertial_L->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        inertial_L->setAlignment(Qt::AlignCenter);
        hardware_L = new QLabel(status_GB);
        hardware_L->setObjectName(QStringLiteral("hardware_L"));
        hardware_L->setGeometry(QRect(80, 70, 59, 14));
        hardware_L->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        hardware_L->setAlignment(Qt::AlignCenter);
        clearStat_PB = new QPushButton(status_GB);
        clearStat_PB->setObjectName(QStringLiteral("clearStat_PB"));
        clearStat_PB->setGeometry(QRect(80, 70, 61, 16));
        scan_bt = new QPushButton(tab);
        scan_bt->setObjectName(QStringLiteral("scan_bt"));
        scan_bt->setGeometry(QRect(0, 0, 80, 22));
        radarPlot = new CQtOpenCVViewerGl(tab);
        radarPlot->setObjectName(QStringLiteral("radarPlot"));
        radarPlot->setGeometry(QRect(10, 30, 400, 200));
        steering = new QGroupBox(tab);
        steering->setObjectName(QStringLiteral("steering"));
        steering->setGeometry(QRect(590, 0, 141, 91));
        steering->setAlignment(Qt::AlignCenter);
        fwd_PB = new QPushButton(steering);
        fwd_PB->setObjectName(QStringLiteral("fwd_PB"));
        fwd_PB->setGeometry(QRect(55, 30, 31, 22));
        fwd_PB->setFocusPolicy(Qt::NoFocus);
        fwd_PB->setFlat(false);
        left_PB = new QPushButton(steering);
        left_PB->setObjectName(QStringLiteral("left_PB"));
        left_PB->setGeometry(QRect(15, 60, 31, 22));
        left_PB->setFocusPolicy(Qt::NoFocus);
        left_PB->setFlat(false);
        right_PB = new QPushButton(steering);
        right_PB->setObjectName(QStringLiteral("right_PB"));
        right_PB->setGeometry(QRect(95, 60, 31, 22));
        right_PB->setFocusPolicy(Qt::NoFocus);
        right_PB->setFlat(false);
        bck_PB = new QPushButton(steering);
        bck_PB->setObjectName(QStringLiteral("bck_PB"));
        bck_PB->setGeometry(QRect(55, 60, 31, 22));
        bck_PB->setFocusPolicy(Qt::NoFocus);
        bck_PB->setFlat(false);
        log_TW = new QTabWidget(tab);
        log_TW->setObjectName(QStringLiteral("log_TW"));
        log_TW->setGeometry(QRect(410, 100, 331, 261));
        log_TW->setFocusPolicy(Qt::NoFocus);
        log_TW->setTabShape(QTabWidget::Rounded);
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
        vel_TE->setReadOnly(true);
        clrVel_PB = new QPushButton(vel_TAB);
        clrVel_PB->setObjectName(QStringLiteral("clrVel_PB"));
        clrVel_PB->setGeometry(QRect(250, 0, 80, 22));
        clrVel_PB->setFocusPolicy(Qt::NoFocus);
        filter_CB = new QComboBox(vel_TAB);
        filter_CB->setObjectName(QStringLiteral("filter_CB"));
        filter_CB->setGeometry(QRect(260, 210, 71, 22));
        log_TW->addTab(vel_TAB, QString());
        latency_GB = new QGroupBox(tab);
        latency_GB->setObjectName(QStringLiteral("latency_GB"));
        latency_GB->setGeometry(QRect(290, 260, 104, 91));
        latency_GB->setAlignment(Qt::AlignCenter);
        latencyPlot = new CQtOpenCVViewerGl(latency_GB);
        latencyPlot->setObjectName(QStringLiteral("latencyPlot"));
        latencyPlot->setGeometry(QRect(2, 30, 100, 50));
        updateTime_SB = new QDoubleSpinBox(tab);
        updateTime_SB->setObjectName(QStringLiteral("updateTime_SB"));
        updateTime_SB->setGeometry(QRect(340, 0, 71, 23));
        updateTime_SB->setFocusPolicy(Qt::NoFocus);
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
        inertial_TB->setGeometry(QRect(0, 0, 751, 253));
        inertial_L_2 = new QLabel(inertial_TB);
        inertial_L_2->setObjectName(QStringLiteral("inertial_L_2"));
        inertial_L_2->setGeometry(QRect(20, 2, 150, 14));
        inertial_L_2->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        inertial_L_2->setAlignment(Qt::AlignCenter);
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
        inSofReb_PB = new QPushButton(inertial_TB);
        inSofReb_PB->setObjectName(QStringLiteral("inSofReb_PB"));
        inSofReb_PB->setGeometry(QRect(660, 30, 80, 22));
        rpPlot = new CQtOpenCVViewerGl(inertial_TB);
        rpPlot->setObjectName(QStringLiteral("rpPlot"));
        rpPlot->setGeometry(QRect(420, 40, 200, 200));
        rpPlot->setStyleSheet(QStringLiteral("border: 2px solid #333333;"));
        toolBox->addItem(inertial_TB, QStringLiteral("MPU9250"));
        platform_TB = new QWidget();
        platform_TB->setObjectName(QStringLiteral("platform_TB"));
        platform_TB->setGeometry(QRect(0, 0, 100, 30));
        platform_L_2 = new QLabel(platform_TB);
        platform_L_2->setObjectName(QStringLiteral("platform_L_2"));
        platform_L_2->setGeometry(QRect(20, 2, 150, 14));
        platform_L_2->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        platform_L_2->setAlignment(Qt::AlignCenter);
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
        comm_L_2->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        comm_L_2->setAlignment(Qt::AlignCenter);
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
        ts_L_2->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        ts_L_2->setAlignment(Qt::AlignCenter);
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
        evlog_L_2->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        evlog_L_2->setAlignment(Qt::AlignCenter);
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
        radar_TB->setGeometry(QRect(0, 0, 100, 30));
        radar_L_2 = new QLabel(radar_TB);
        radar_L_2->setObjectName(QStringLiteral("radar_L_2"));
        radar_L_2->setGeometry(QRect(20, 2, 150, 14));
        radar_L_2->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        radar_L_2->setAlignment(Qt::AlignCenter);
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
        engines_TB->setGeometry(QRect(0, 0, 100, 30));
        engines_L_2 = new QLabel(engines_TB);
        engines_L_2->setObjectName(QStringLiteral("engines_L_2"));
        engines_L_2->setGeometry(QRect(20, 2, 150, 14));
        engines_L_2->setStyleSheet(QLatin1String("background-color:rgb(126, 189, 189);\n"
"color:#454545;\n"
"border-radius:3px;"));
        engines_L_2->setAlignment(Qt::AlignCenter);
        engPinv_GV = new QGraphicsView(engines_TB);
        engPinv_GV->setObjectName(QStringLiteral("engPinv_GV"));
        engPinv_GV->setGeometry(QRect(0, 0, 18, 18));
        engPinv_GV->setMouseTracking(true);
        engPinv_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        engPinv_GV->setFrameShape(QFrame::NoFrame);
        engReb_PB = new QPushButton(engines_TB);
        engReb_PB->setObjectName(QStringLiteral("engReb_PB"));
        engReb_PB->setGeometry(QRect(660, 0, 80, 22));
        toolBox->addItem(engines_TB, QStringLiteral("Engines"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        mStart_L = new QLabel(tab_3);
        mStart_L->setObjectName(QStringLiteral("mStart_L"));
        mStart_L->setGeometry(QRect(10, 10, 281, 21));
        mStart_L->setStyleSheet(QStringLiteral("color:#FF0000;"));
        mStart_LE = new QLineEdit(tab_3);
        mStart_LE->setObjectName(QStringLiteral("mStart_LE"));
        mStart_LE->setEnabled(true);
        mStart_LE->setGeometry(QRect(160, 10, 113, 22));
        missionT_GB = new QGroupBox(tab_3);
        missionT_GB->setObjectName(QStringLiteral("missionT_GB"));
        missionT_GB->setEnabled(false);
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
        missPer_CB = new QCheckBox(missionT_GB);
        missPer_CB->setObjectName(QStringLiteral("missPer_CB"));
        missPer_CB->setGeometry(QRect(250, 270, 171, 20));
        missPer_LE = new QLineEdit(missionT_GB);
        missPer_LE->setObjectName(QStringLiteral("missPer_LE"));
        missPer_LE->setGeometry(QRect(420, 270, 81, 22));
        missRep_LE = new QLineEdit(missionT_GB);
        missRep_LE->setObjectName(QStringLiteral("missRep_LE"));
        missRep_LE->setGeometry(QRect(510, 270, 81, 22));
        mUtime_L_2 = new QLabel(tab_3);
        mUtime_L_2->setObjectName(QStringLiteral("mUtime_L_2"));
        mUtime_L_2->setGeometry(QRect(440, 10, 291, 21));
        mUtime_LE_2 = new QLineEdit(tab_3);
        mUtime_LE_2->setObjectName(QStringLiteral("mUtime_LE_2"));
        mUtime_LE_2->setEnabled(true);
        mUtime_LE_2->setGeometry(QRect(590, 10, 111, 22));
        mUtime_LE_2->setFocusPolicy(Qt::NoFocus);
        warn_GV = new QGraphicsView(tab_3);
        warn_GV->setObjectName(QStringLiteral("warn_GV"));
        warn_GV->setGeometry(QRect(300, 10, 18, 18));
        warn_GV->setMouseTracking(true);
        warn_GV->setStyleSheet(QLatin1String("background-image:url(:/new/prefix1/imgs/danger.png);\n"
"background-repeat:no-repeat;"));
        warn_GV->setFrameShape(QFrame::NoFrame);
        tabWidget->addTab(tab_3, QString());
        mUtime_L = new QLabel(centralWidget);
        mUtime_L->setObjectName(QStringLiteral("mUtime_L"));
        mUtime_L->setGeometry(QRect(420, 10, 21, 21));
        mUtime_LE = new QLineEdit(centralWidget);
        mUtime_LE->setObjectName(QStringLiteral("mUtime_LE"));
        mUtime_LE->setEnabled(true);
        mUtime_LE->setGeometry(QRect(440, 10, 111, 22));
        mUtime_LE->setFocusPolicy(Qt::NoFocus);
        mUtime_LE->setReadOnly(true);
        qos_L = new QLabel(centralWidget);
        qos_L->setObjectName(QStringLiteral("qos_L"));
        qos_L->setGeometry(QRect(250, 10, 31, 21));
        qos_PrB = new QProgressBar(centralWidget);
        qos_PrB->setObjectName(QStringLiteral("qos_PrB"));
        qos_PrB->setGeometry(QRect(280, 10, 118, 23));
        qos_PrB->setValue(0);
        qos_PrB->setTextVisible(true);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(570, 10, 171, 45));
        groupBox->setLayoutDirection(Qt::LeftToRight);
        groupBox->setStyleSheet(QLatin1String("QGroupBox::title\n"
"{\n"
"subcontrol-origin: margin;\n"
"subcontrol-position:bottom center;\n"
"}\n"
"QGroupBox\n"
"{\n"
"margin-top: -2.5ex;\n"
"border:1px solid gray;\n"
"border-radius:5px;\n"
"} \n"
""));
        groupBox->setFlat(false);
        telemetry_L = new QLabel(groupBox);
        telemetry_L->setObjectName(QStringLiteral("telemetry_L"));
        telemetry_L->setGeometry(QRect(10, 10, 71, 20));
        telemetry_L->setStyleSheet(QLatin1String("background-color:rgb(255, 0, 4);\n"
"color:#454545;\n"
"border-radius:3px;"));
        telemetry_L->setAlignment(Qt::AlignCenter);
        commands_L_2 = new QPushButton(groupBox);
        commands_L_2->setObjectName(QStringLiteral("commands_L_2"));
        commands_L_2->setGeometry(QRect(90, 10, 71, 22));
        commands_L_2->setFocusPolicy(Qt::NoFocus);
        commands_L_2->setStyleSheet(QStringLiteral("background-color:transparent"));
        commands_L_2->setFlat(true);
        commands_L = new QLabel(groupBox);
        commands_L->setObjectName(QStringLiteral("commands_L"));
        commands_L->setGeometry(QRect(90, 10, 71, 20));
        commands_L->setStyleSheet(QLatin1String("background-color:rgb(255, 0, 4);\n"
"color:#454545;\n"
"border-radius:3px;"));
        commands_L->setAlignment(Qt::AlignCenter);
        commands_L->raise();
        telemetry_L->raise();
        commands_L_2->raise();
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        log_TW->setCurrentIndex(1);
        toolBox->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rover control", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        reboot_BT->setToolTip(QApplication::translate("MainWindow", "Hard reboot of rover", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        reboot_BT->setText(QApplication::translate("MainWindow", "Reboot", Q_NULLPTR));
        uptime_GB->setTitle(QApplication::translate("MainWindow", "Up-time", Q_NULLPTR));
        deltams_L->setText(QApplication::translate("MainWindow", "\316\224 ", Q_NULLPTR));
        ms_L->setText(QApplication::translate("MainWindow", "s", Q_NULLPTR));
        ms_L_2->setText(QApplication::translate("MainWindow", "s", Q_NULLPTR));
        orientation_GB->setTitle(QApplication::translate("MainWindow", "Orienatation", Q_NULLPTR));
        roll_L->setText(QApplication::translate("MainWindow", "R", Q_NULLPTR));
        pitch_L->setText(QApplication::translate("MainWindow", "P", Q_NULLPTR));
        yaw_L->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        status_GB->setTitle(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        platform_L->setText(QApplication::translate("MainWindow", "Platform", Q_NULLPTR));
        engines_L->setText(QApplication::translate("MainWindow", "Engines", Q_NULLPTR));
        comm_L->setText(QApplication::translate("MainWindow", "Comm", Q_NULLPTR));
        radar_L->setText(QApplication::translate("MainWindow", "Radar", Q_NULLPTR));
        inertial_L->setText(QApplication::translate("MainWindow", "Inertial", Q_NULLPTR));
        hardware_L->setText(QApplication::translate("MainWindow", "Hardware", Q_NULLPTR));
        clearStat_PB->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        scan_bt->setText(QApplication::translate("MainWindow", "Scan", Q_NULLPTR));
        steering->setTitle(QApplication::translate("MainWindow", "Steering", Q_NULLPTR));
        fwd_PB->setText(QApplication::translate("MainWindow", "\342\206\221", Q_NULLPTR));
        left_PB->setText(QApplication::translate("MainWindow", "\342\206\220", Q_NULLPTR));
        right_PB->setText(QApplication::translate("MainWindow", "\342\206\222", Q_NULLPTR));
        bck_PB->setText(QApplication::translate("MainWindow", "\342\206\223", Q_NULLPTR));
        clrLog->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        log_TW->setTabText(log_TW->indexOf(guilog_TAB), QApplication::translate("MainWindow", "GUI log", Q_NULLPTR));
        clrVel_PB->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        filter_CB->clear();
        filter_CB->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "All", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ERROR", Q_NULLPTR)
         << QApplication::translate("MainWindow", "HANG", Q_NULLPTR)
         << QApplication::translate("MainWindow", "INIT", Q_NULLPTR)
         << QApplication::translate("MainWindow", "OK", Q_NULLPTR)
         << QApplication::translate("MainWindow", "PRIOINV", Q_NULLPTR)
         << QApplication::translate("MainWindow", "STARTUP", Q_NULLPTR)
         << QApplication::translate("MainWindow", "UNINIT", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ESP8266", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Radar", Q_NULLPTR)
         << QApplication::translate("MainWindow", "MPU9250", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Engines", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Platform", Q_NULLPTR)
        );
        log_TW->setTabText(log_TW->indexOf(vel_TAB), QApplication::translate("MainWindow", "Vehicle event log", Q_NULLPTR));
        latency_GB->setTitle(QApplication::translate("MainWindow", "Latency (ms)", Q_NULLPTR));
        updateTime_L->setText(QApplication::translate("MainWindow", "Refresh rate(s)", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Overview", Q_NULLPTR));
        inertial_L_2->setText(QApplication::translate("MainWindow", "Inertial", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        inReb_PB->setToolTip(QApplication::translate("MainWindow", "<html><head/><body style=\"p {padding:0px; margin:0px;}\"><p>Hard reboot of Inertial unit</p><p>Triggers software reboot of MPU9250,</p><p>Reuploads DMP firmware,</p><p>Configures sampling &amp; interrupt</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        inReb_PB->setText(QApplication::translate("MainWindow", "Hard reboot", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "Roll", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("MainWindow", "Pitch", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("MainWindow", "Yaw", Q_NULLPTR));
        imuSamp_CB->setText(QApplication::translate("MainWindow", "Enable sampling", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        inerPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        inSofReb_PB->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Soft reboot of Inertial unit</p><p>resets only event logger status</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        inSofReb_PB->setText(QApplication::translate("MainWindow", "Soft reboot", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(inertial_TB), QApplication::translate("MainWindow", "MPU9250", Q_NULLPTR));
        platform_L_2->setText(QApplication::translate("MainWindow", "Platform", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        platPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        commI_GB->setTitle(QApplication::translate("MainWindow", "Communication", Q_NULLPTR));
        commReb_PB->setText(QApplication::translate("MainWindow", "Reboot", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        commPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        comm_L_2->setText(QApplication::translate("MainWindow", "Communication", Q_NULLPTR));
        tsI_GB->setTitle(QApplication::translate("MainWindow", "Task scheduler", Q_NULLPTR));
        tsUpd_PB->setText(QApplication::translate("MainWindow", "Update", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        tsPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        ts_L_2->setText(QApplication::translate("MainWindow", "Task scheduler", Q_NULLPTR));
        evlog_GB->setTitle(QApplication::translate("MainWindow", "Event logger", Q_NULLPTR));
        evlogReb_PB->setText(QApplication::translate("MainWindow", "Reboot", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        evlogPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        evlog_L_2->setText(QApplication::translate("MainWindow", "Event logger", Q_NULLPTR));
        evlogUpd_PB->setText(QApplication::translate("MainWindow", "Update", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        platReb_PB->setToolTip(QApplication::translate("MainWindow", "Soft rebot only resets status", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        platReb_PB->setText(QApplication::translate("MainWindow", "Reboot", Q_NULLPTR));
        softReb_L->setText(QApplication::translate("MainWindow", "Soft reboot", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(platform_TB), QApplication::translate("MainWindow", "Platform", Q_NULLPTR));
        radar_L_2->setText(QApplication::translate("MainWindow", "Radar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        radPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBox->setItemText(toolBox->indexOf(radar_TB), QApplication::translate("MainWindow", "Radar", Q_NULLPTR));
        engines_L_2->setText(QApplication::translate("MainWindow", "Engines", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        engPinv_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Priority inversion event</p><p>Module emitted a lower-priority event after prevoiusly </p><p>emitting a higher priority one. This doesn't necessarily </p><p>point to module malfunctioning but it may be an </p><p>indicator. Try to reboot the module.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        engReb_PB->setText(QApplication::translate("MainWindow", "Reboot", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(engines_TB), QApplication::translate("MainWindow", "Engines", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Instruments", Q_NULLPTR));
        mStart_L->setText(QApplication::translate("MainWindow", "Mission starting time T=                                s", Q_NULLPTR));
        mStart_LE->setPlaceholderText(QApplication::translate("MainWindow", "[ms]", Q_NULLPTR));
        missionT_GB->setTitle(QApplication::translate("MainWindow", "Mission tasks", Q_NULLPTR));
        addTask_PB->setText(QApplication::translate("MainWindow", "Add task", Q_NULLPTR));
        schedMiss_PB->setText(QApplication::translate("MainWindow", "Schedule\n"
"mission", Q_NULLPTR));
        missPer_CB->setText(QApplication::translate("MainWindow", "Create periodic mission", Q_NULLPTR));
        missPer_LE->setPlaceholderText(QApplication::translate("MainWindow", "Period [ms]", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        missRep_LE->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Number of times to repeat the mission</p><p>Set to -1 for infinite number of repeats</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        missRep_LE->setText(QString());
        missRep_LE->setPlaceholderText(QApplication::translate("MainWindow", "Repeats", Q_NULLPTR));
        mUtime_L_2->setText(QApplication::translate("MainWindow", "Current vehice time T=                                 s", Q_NULLPTR));
        mUtime_LE_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        warn_GV->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>WARNING</p><p>Mission is scheduled in past according to vehicle's</p><p>internal timer. This means that all tasks will be </p><p>executed as soon as they arrive at vehicle.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Mission planner", Q_NULLPTR));
        mUtime_L->setText(QApplication::translate("MainWindow", "T=", Q_NULLPTR));
        mUtime_LE->setText(QString());
        qos_L->setText(QApplication::translate("MainWindow", "QoS", Q_NULLPTR));
        qos_PrB->setFormat(QApplication::translate("MainWindow", "%p%", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Streams", Q_NULLPTR));
        telemetry_L->setText(QApplication::translate("MainWindow", "Telemetry", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        commands_L_2->setToolTip(QApplication::translate("MainWindow", "Click to reset communication module", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        commands_L_2->setText(QString());
        commands_L->setText(QApplication::translate("MainWindow", "Commands", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
