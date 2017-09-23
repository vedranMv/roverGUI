#include "mainwindow.h"

/**
 * @brief MainWindow::on_schedMiss_PB_clicked
 */
void MainWindow::on_schedMiss_PB_clicked()
{
    //  Reset status
    sendStatus = COMMANDS_RESET;
    //  Start sending through timeout event
    sendTimer->start(200);  //  send max 5 commands per second
}

/**
 * @brief Field evaluation triggered by changing content of mission time
 * Function evaluates content of mission starting time text box in order to
 * ensure that content of it always evaluates to a number
 * @param arg1
 */
void MainWindow::on_mStart_LE_textChanged(const QString &arg1)
{
    //  Allow user to type in only digits and decimal comma
    if (arg1.length() > 0)
        if (!(arg1[arg1.length()-1].isDigit() || (arg1[arg1.length()-1] == '.')))
        {
            if (arg1.length() == 1)
                ui->mStart_LE->setText("");
            else
                ui->mStart_LE->setText(arg1.left(arg1.length()-1));
        }

    ui->missionT_GB->setEnabled((arg1.length() > 0));
    ui->missionT_GB->setVisible((arg1.length() > 0));

    //  Display warning if mission is scheduled in past
    if (ui->mStart_LE->text().toDouble() < ui->mUtime_LE_2->text().toDouble())
        ui->warn_GV->setVisible(true);
    else
        ui->warn_GV->setVisible(false);
}

/**
 * @brief Adds another entry to the mission task list
 * (Mission planner->Mission tasks)
 */
void MainWindow::on_addTask_PB_clicked()
{
    //  Create new entry
    MissionEntry *tmp = new MissionEntry(mEntries.size(), ui->scrollAreaWidgetContents, ui->mStart_LE);
    mEntries.push_back(tmp);
    //  Connect 'Deleted' signal to 'UpdateIDs' slot so that we automatically
    //  change IDs of all entries when signal is deleted
    connect(mEntries.back(), SIGNAL(Deleted()), this, SLOT(UpdateIDs()));
    //  Add mission entry to scrollable area
    ui->scrollAreaWidgetContents->layout()->addWidget(mEntries.back()->Container());
}

/**
 * @brief Enable periodic mission (Mission->Create Periodc Mission)
 * @param checked
 */
void MainWindow::on_missPer_CB_clicked(bool checked)
{
    ui->missPer_LE->setVisible(checked);
    ui->missRep_LE->setVisible(checked);
}

/**
 * @brief Called every time a task has been deleted from mission, handles
 * renumbering the tasks in case the task in the middle has been deleted
 * (Mission planner->Mission tasks)
 */
void MainWindow::UpdateIDs()
{
    //  House keeping: Check all 'dead' (deleted) entries from mEntries vector
    //  and remove them
    for (uint8_t i = 0; i < mEntries.size(); i++)
        if (mEntries[i]->dead)
        {
            //  Delete object from heap
            //delete mEntries[i];
            //  Delete entry from vector
            mEntries.erase(mEntries.begin()+i);
        }
    //std::cout<<"Deleted, updating labels\n";
    //  After deleting do one more pass through entries to update their number
    for (uint8_t i = 0; i < mEntries.size(); i++)
        mEntries[i]->ChangeIndex(i);
}
