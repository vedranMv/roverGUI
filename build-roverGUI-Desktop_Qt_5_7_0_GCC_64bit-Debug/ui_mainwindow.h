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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <cqtopencvviewergl.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *scan_bt;
    QGroupBox *logBox;
    QPushButton *clrLog;
    QPlainTextEdit *log;
    CQtOpenCVViewerGl *radarPlot;
    QGroupBox *orientationGB;
    QLineEdit *roll_LE;
    QLabel *roll_L;
    QLineEdit *pitch_LE;
    QLabel *pitch_L;
    QLabel *yaw_L;
    QLineEdit *yaw_LE;
    QLabel *utime_L;
    QLineEdit *utime_LE;
    QLabel *ms_L;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(595, 388);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        scan_bt = new QPushButton(centralWidget);
        scan_bt->setObjectName(QStringLiteral("scan_bt"));
        scan_bt->setGeometry(QRect(10, 10, 80, 22));
        logBox = new QGroupBox(centralWidget);
        logBox->setObjectName(QStringLiteral("logBox"));
        logBox->setGeometry(QRect(0, 240, 421, 131));
        clrLog = new QPushButton(logBox);
        clrLog->setObjectName(QStringLiteral("clrLog"));
        clrLog->setGeometry(QRect(340, 20, 80, 22));
        log = new QPlainTextEdit(logBox);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(0, 20, 421, 111));
        log->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        log->setReadOnly(true);
        log->setCenterOnScroll(false);
        log->raise();
        clrLog->raise();
        radarPlot = new CQtOpenCVViewerGl(centralWidget);
        radarPlot->setObjectName(QStringLiteral("radarPlot"));
        radarPlot->setGeometry(QRect(20, 40, 400, 200));
        orientationGB = new QGroupBox(centralWidget);
        orientationGB->setObjectName(QStringLiteral("orientationGB"));
        orientationGB->setGeometry(QRect(440, 30, 131, 91));
        roll_LE = new QLineEdit(orientationGB);
        roll_LE->setObjectName(QStringLiteral("roll_LE"));
        roll_LE->setGeometry(QRect(30, 20, 101, 22));
        roll_L = new QLabel(orientationGB);
        roll_L->setObjectName(QStringLiteral("roll_L"));
        roll_L->setGeometry(QRect(10, 20, 59, 21));
        pitch_LE = new QLineEdit(orientationGB);
        pitch_LE->setObjectName(QStringLiteral("pitch_LE"));
        pitch_LE->setGeometry(QRect(30, 40, 101, 22));
        pitch_L = new QLabel(orientationGB);
        pitch_L->setObjectName(QStringLiteral("pitch_L"));
        pitch_L->setGeometry(QRect(10, 40, 59, 21));
        yaw_L = new QLabel(orientationGB);
        yaw_L->setObjectName(QStringLiteral("yaw_L"));
        yaw_L->setGeometry(QRect(10, 60, 59, 21));
        yaw_LE = new QLineEdit(orientationGB);
        yaw_LE->setObjectName(QStringLiteral("yaw_LE"));
        yaw_LE->setGeometry(QRect(30, 60, 101, 22));
        utime_L = new QLabel(centralWidget);
        utime_L->setObjectName(QStringLiteral("utime_L"));
        utime_L->setGeometry(QRect(430, 130, 59, 21));
        utime_LE = new QLineEdit(centralWidget);
        utime_LE->setObjectName(QStringLiteral("utime_LE"));
        utime_LE->setGeometry(QRect(440, 150, 113, 22));
        ms_L = new QLabel(centralWidget);
        ms_L->setObjectName(QStringLiteral("ms_L"));
        ms_L->setGeometry(QRect(560, 150, 21, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 595, 19));
        menuBar->setNativeMenuBar(false);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rover control", 0));
        scan_bt->setText(QApplication::translate("MainWindow", "Scan", 0));
        logBox->setTitle(QApplication::translate("MainWindow", "Log", 0));
        clrLog->setText(QApplication::translate("MainWindow", "Clear", 0));
        orientationGB->setTitle(QApplication::translate("MainWindow", "Orienatation", 0));
        roll_L->setText(QApplication::translate("MainWindow", "R", 0));
        pitch_L->setText(QApplication::translate("MainWindow", "P", 0));
        yaw_L->setText(QApplication::translate("MainWindow", "Y", 0));
        utime_L->setText(QApplication::translate("MainWindow", "Up-time", 0));
        ms_L->setText(QApplication::translate("MainWindow", "s", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
