#include "missionentry.h"
#include "roverinterface.h"

MissionEntry::MissionEntry(uint8_t arg, QWidget *parent, QLineEdit *startT)
    : taskF(new QFrame(parent)), dead(false), argCB(0), sTime(startT)
{
    //  Create all elements
    taskL = new QLabel(taskF);
    taskLE = new QLineEdit(taskF);
    taskCB = new QComboBox(taskF);
    taskPB = new QPushButton(taskF);

    //  Configure container frame
    taskF->setMaximumWidth(720);
    taskF->setMaximumHeight(42);
    taskF->setMinimumWidth(720);
    taskF->setMinimumHeight(42);
    taskF->resize(720, 42);
    taskF->setLineWidth(1);
    taskF->setFrameShape(QFrame::Shape::StyledPanel);
    taskF->setFrameShadow(QFrame::Shadow::Sunken);
    taskF->show();

    //  Configure Label
    taskL->setText(QString::number(arg)+". T+                                s");
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

    //  Configure ComboBox for selecting libUID
    taskCB->move(220,10);
    taskCB->resize(100, 22);
    for (uint8_t i = 0; i < 8; i++)
    {
        taskCB->addItem(QString(libName[i]));
    }
    //  When selected module, create another comboBox to for selecting tasks
    //  offered by selected module
    connect(taskCB, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateTaskCB(int)));
    UpdateTaskCB(0);
}
MissionEntry::~MissionEntry()
{
    Delete();
}

/**
 * @brief Updates index of tasks when one of the preceeding tasks has been deleted
 * @param newI New index of this task
 */
void MissionEntry::ChangeIndex(uint8_t newI)
{
    QStringList oldLabel = taskL->text().split(".");
    taskL->setText(QString::number(newI)+"."+oldLabel[1]);
}
/**
 * @brief Return pointer to QWidget in which all mission entry elements are
 * contained
 * @return
 */
QWidget* MissionEntry::Container()
{
    return taskF;
}
/**
 * @brief Return library/module of this mission task
 * @return
 */
int MissionEntry::LibUID()
{
    return taskCB->currentIndex();
}

/**
 * @brief Return taskID withing module that's connected to this mission task
 * @return
 */
int MissionEntry::TaskID()
{
    return taskTCB->currentIndex();
}

void MissionEntry::Delete()
{
    ArgCleanup();

    taskL->deleteLater();
    taskLE->deleteLater();
    taskCB->deleteLater();
    taskPB->deleteLater();
    taskF->deleteLater();

    dead = true;
    emit(Deleted());
}

/**
 * @brief Update event to create drop-down menu with tasks avavilable in the
 * selected module
 * Connected to taskCB, creates taskTCB
 * @param index
 */
void MissionEntry::UpdateTaskCB(int index)
{
    //  Cleanup: Delete all previous argument elements
    ArgCleanup();

    //  Once a module has been selected, offer selecting the task
    taskTCB = new QComboBox(taskF);
    taskTCB->move(330,10);
    taskTCB->resize(90, 22);
    taskTCB->show();
    for (uint8_t i = 0; allTasks[index][i][0] != 0; i++)
        taskTCB->addItem(QString(allTasks[index][i]));

    //  Connect event
    connect(taskTCB, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateArguments(int)));
    connect(taskTCB, SIGNAL(highlighted(int)), this, SLOT(UpdateArguments(int)));

    validTask = false;
    Validate();
}

void MissionEntry::UpdateEngUnit(int index)
{
    if (index < 2)
        args[0]->setPlaceholderText("Dist [cm]");
    else
        args[0]->setPlaceholderText("Angle [deg]");
}


/**
 * @brief Update event to create argument fields once a task has been selcted
 * Connected to taskTCB, creates GUI elements for entering arguments every time
 * an item in taskTCB has been highlighted
 * This is one of the ugliest parts of code in the whole project :(
 * @param index
 */
void MissionEntry::UpdateArguments(int index)
{
    //  Cleanup: Delete all previous argument elements
    ArgCleanup();

    //  Most tasks require at least one QLineEdit, create it here (it might get
    //  destroyed in if statements)
    QLineEdit *tmp = new QLineEdit(taskF);
    tmp->resize(170, 22);
    tmp->move(430, 10);
    //tmp->show();
    validTask = true;

    if (LibUID() == ESP_UID)
    {
        validTask = false;
        //  This is only valid task from ESP
        if (index == ESP_T_REBOOT)
        {
            tmp->show();
            tmp->setPlaceholderText("Enter reboot code");
            tmp->setText("23");
            args.push_back(tmp);
        }
        else
            validTask = false;
    }
    else if (LibUID() == RADAR_UID)
    {
        //  Scan takes no arguments, delete tmp and return here
        if (index == RADAR_SCAN)
        {
            tmp->hide();
            tmp->deleteLater();
        }
        else
        {
            //  Other 2 tasks in radar module use QLineEdit, with different placeholder
            if ((taskTCB->currentIndex()) == RADAR_SETH)
                tmp->setPlaceholderText("Horizontal angle [deg]");
            else if ((taskTCB->currentIndex()) == RADAR_SETV)
                tmp->setPlaceholderText("Vertical angle [deg]");

            tmp->show();
            args.push_back(tmp);
        }
    }
    else if (LibUID() == ENGINES_UID)
    {
        //  2 of 3 tasks here require ComboBox, create it here and delete if
        //  not needed
        argCB = new QComboBox(taskF);
        argCB->move(430, 10);
        argCB->resize(100, 22);
        argCB->show();

        //  Populate drop-down menu with options for direction
        for (uint8_t i = 0; engineDirN[i][0] != 0; i++)
            argCB->addItem(QString(engineDirN[i]));

        if (TaskID() == ENG_T_MOVE_ENG)
        {
            //tmp->resize(100, 22);
            tmp->move(540, 10);
            tmp->setPlaceholderText("Dist [cm]");
            tmp->show();
            args.push_back(tmp);

            //  Update field's placeholder with units (deg/cm) based on which
            //  movement is selected (turning/driving)
            connect(argCB, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateEngUnit(int)));
            UpdateEngUnit(0);   //  First selected index is 0
        }
        else if (TaskID() == ENG_T_MOVE_ARC)
        {
            //  This task doesn't use premade LineEdit nor ComboBox, delete them
            tmp->hide();
            tmp->deleteLater();
            argCB->hide();
            argCB->deleteLater();
            argCB = 0;

            //  Construct required arg fields
            for (uint8_t i = 0; i < 3; i++)
            {
                QLineEdit *tmp = new QLineEdit(taskF);
                tmp->resize(80, 22);
                tmp->move(430+i*90, 10);
                tmp->show();
                args.push_back(tmp);
            }
            args[0]->setPlaceholderText("Dist [cm]");
            args[1]->setPlaceholderText("Angle [deg]");
            args[2]->setPlaceholderText("Small-rad [cm]");
        }
        else if (TaskID() == ENG_T_MOVE_PERC)
        {
            //  This task uses ComboBox, don't delete it, but doesn't use premade
            //  LineEdit
            tmp->hide();
            tmp->deleteLater();

            //  Task requires 2 LineEdits for entering wheel's speed
            for (uint8_t i = 0; i < 2; i++)
            {
                QLineEdit *tmp = new QLineEdit(taskF);
                tmp->resize(80, 22);
                tmp->move(540+i*90, 10);
                tmp->show();
                args.push_back(tmp);
            }
            args[0]->setPlaceholderText("Left %");
            args[1]->setPlaceholderText("Right %");
        }
    }
    else if (LibUID() == MPU_UID)
    {
        if (TaskID() == MPU_REBOOT)
        {
            tmp->show();
            tmp->setPlaceholderText("Enter reboot code");
            tmp->setText("23");
            args.push_back(tmp);
        }
        else if (TaskID() == MPU_GET_DATA)
        {
            //  Doesn't use premade LineEdit
            tmp->hide();
            tmp->deleteLater();
            //validTask = false;
        }
        else
        {
            //  Doesn't use premade LineEdit
            tmp->hide();
            tmp->deleteLater();

            argCB = new QComboBox(taskF);
            argCB->move(430, 10);
            argCB->resize(100, 22);
            argCB->show();
            //  Listen takes one argument, false(0) or true(1)
            argCB->addItem(QString("Disable"));
            argCB->addItem(QString("Enable"));
        }
    }
    else if (LibUID() == DATAS_UID)
    {
        //  Requires pointer to existing DataStream which cannot be obtained from
        //  GUI. Therefore no valid tasks here
        validTask = false;
        //  No task here uses premade LineEdit
        tmp->hide();
        tmp->deleteLater();
    }
    else if (LibUID() == PLAT_UID)
    {
        //  These two tasks take one argument through LineEdit
        if ((TaskID() == PLAT_REBOOT) || (TaskID() == PLAT_SOFT_REBOOT))
        {
            tmp->show();
            tmp->setPlaceholderText("Enter reboot code");
            tmp->setText("23");
            args.push_back(tmp);
        }
        //  All other tasks are valid and take no arguments
        else
        {
            //  Takes no arg.
            tmp->hide();
            tmp->deleteLater();
        }
    }
    else if (LibUID() == EVLOG_UID)
    {
        if (TaskID() == EVLOG_DROP)
        {
            tmp->show();
            tmp->setPlaceholderText("Timestamp");
            args.push_back(tmp);
        }
        else if (TaskID() == EVLOG_REBOOT)
        {
            tmp->show();
            tmp->setPlaceholderText("Enter reboot code");
            tmp->setText("23");
            args.push_back(tmp);
        }
        else if (TaskID() == EVLOG_SOFT_REBOOT)
        {
//            tmp->show();
//            tmp->setPlaceholderText("LibUID");
//            tmp->setText("0");
//            args.push_back(tmp);

            //  Doesn't use premade LineEdit
            tmp->hide();
            tmp->deleteLater();

            argCB = new QComboBox(taskF);
            argCB->move(430, 10);
            argCB->resize(100, 22);
            argCB->show();
            for (uint8_t i = 0; i < 8; i++)
                argCB->addItem(QString(libName[i]));
        }
    }
    else if (LibUID() == TASKSCHED_UID)
    {
        if (TaskID() == TASKSCHED_T_ENABLE)
        {
            //  Doesn't use premade LineEdit
            tmp->hide();
            tmp->deleteLater();

            argCB = new QComboBox(taskF);
            argCB->move(430, 10);
            argCB->resize(100, 22);
            argCB->show();
            //  Listen takes one argument, false(0) or true(1)
            argCB->addItem(QString("Disable"));
            argCB->addItem(QString("Enable"));
        }
        else if (TaskID() == TASKSCHED_T_KILL)
        {
            tmp->show();
            tmp->setPlaceholderText("Enter PID to kill");
            args.push_back(tmp);
        }
    }

    Validate();
}

/**
 * @brief Delete GUI elements containing arguments
 */
void MissionEntry::ArgCleanup()
{
    //  Cleanup: Delete all previous argument elements
    if (argCB != 0)
        argCB->deleteLater();
    argCB = 0;
    while (!args.empty())
    {
        args.front()->deleteLater();
        args.erase(args.begin());
    }
}

/**
 * @brief Convert MissionTask parameters into a rover-compatible request
 * @return
 */
void MissionEntry::ToReq(char *command, uint16_t &commandLen, int32_t repeats, int32_t period)
{
    char        reqArgs[50] = {0};
    uint8_t     argCnt = 0;


    MakeRequest((uint8_t*)command, LibUID(), TaskID(),
                (taskLE->text().toInt()+sTime->text().toLongLong())*1000, repeats, period);

    if ((TaskID() == EVLOG_SOFT_REBOOT) && (LibUID() == EVLOG_UID))
        memcpy((void*)(reqArgs+argCnt++), (void*)&(softRebCode), 1);

    if (argCB != 0)
    {
        uint8_t argCBInt = 0;

        if (LibUID() == ENGINES_UID)
            argCBInt = engineDirV[argCB->currentIndex()];
        else if ((LibUID() == MPU_UID) || (LibUID() == EVLOG_UID) || (LibUID() == TASKSCHED_UID))
            argCBInt = argCB->currentIndex();

        memcpy((void*)(reqArgs+argCnt), (void*)&(argCBInt), 1);
        argCnt++;
    }


    for (auto X : args)
    {
        if ((LibUID() == ENGINES_UID))
        {
            float argF = X->text().toFloat();
            memcpy((void*)(reqArgs+argCnt), &argF, 4);
            argCnt += 4;
        }
        else if ((LibUID() == EVLOG_UID) && (TaskID() == EVLOG_DROP))
        {
            uint32_t argUL = X->text().toULong();
            memcpy((void*)(reqArgs+argCnt), &argUL, 4);
            argCnt += 4;
        }
        else if ((LibUID() == EVLOG_UID) && (TaskID() == EVLOG_SOFT_REBOOT))
        {
            uint8_t argUS = X->text().toUShort();
            memcpy((void*)(reqArgs+argCnt), &argUS, 1);
            argCnt += 1;
        }
        else if ((LibUID() == TASKSCHED_UID) && (TaskID() == TASKSCHED_T_KILL))
        {
            uint16_t argUL = X->text().toULong();
            memcpy((void*)(reqArgs+argCnt), &argUL, 2);
            argCnt += 2;
        }
        else
        {
            uint8_t argUL = X->text().toUShort();
            memcpy((void*)(reqArgs+argCnt), &argUL, 1);
            argCnt += 1;
        }

    }

    //  For this task manually append argument saying that it's a non-blocking call
    if ((LibUID() == ENGINES_UID) && (TaskID() == ENG_T_MOVE_ENG))
    {
        reqArgs[argCnt++] = 0;
    }

    //  If there's no arguments provided send one 0 as argument
    if (argCnt == 0)
    {
        reqArgs[0] = 0x00;
        argCnt++;
    }

    AppendArgs((uint8_t*)command, &commandLen, (void*)reqArgs, argCnt);
}

void MissionEntry::Validate()
{
    if (validTask)
    {
        taskF->setStyleSheet("");
        taskF->setToolTip("");
    }
    else
    {
        taskF->setStyleSheet("background-color:#4c0906;");
        taskF->setToolTip("Task is invalid, it won't be sent!");
        taskF->setMouseTracking(true);
    }
}
