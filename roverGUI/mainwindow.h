#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_start_bt_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
};

#endif // MAINWINDOW_H
