#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "ocvgraph.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void LogLine(QString arg);
    void ParseTelemetry(QString teleStr);
    void ParseCommandResp(QString respStr);

private slots:
    void on_scan_bt_clicked();
    void acceptCliTelemetry(void);
    void acceptCliCommands(void);
    void readDataTelemetry(void);
    void readDataCommands(void);
    void on_clrLog_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer tcpStelemetry;
    QTcpServer tcpScommands;
    QTcpSocket* tcpCliTelemetry;
    QTcpSocket* tcpCliCommands;
    QTcpSocket *tcpServerConnection;
    //  Setting up graph plotting in openCV
    double scale = 2.5;
    OCVGraph blank;
};

#endif // MAINWINDOW_H
