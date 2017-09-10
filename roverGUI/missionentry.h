#ifndef MISSIONENTRY_H
#define MISSIONENTRY_H

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFrame>
#include <QWidget>

#include <vector>
#include "roverinterface.h"
#include <string>

class MissionEntry : public QObject
{
    Q_OBJECT
public:
    MissionEntry(uint8_t arg, QWidget *parent, QLineEdit *startT);
    ~MissionEntry();

    void ChangeIndex(uint8_t newI);

    QWidget *Container();

    int LibUID();
    int TaskID();

    void ArgCleanup();
    void ToReq(char *comm, uint16_t &commandLen, int32_t repeats, int32_t period);
    void Validate();

public slots:
    void Delete();
    void UpdateArguments(int index);
    void UpdateTaskCB(int index);
    void UpdateEngUnit(int index);


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
    bool        validTask;

    //  Task argument holders
    std::vector<QLineEdit*>args;
    QComboBox   *argCB;

    QLineEdit   *sTime;
    //Ui::MainWindow *ui;
};

#endif // MISSIONENTRY_H
