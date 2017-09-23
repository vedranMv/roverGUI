#include "mainwindow.h"

/**
 * @brief Apply filter on vehicle's event log, displaying only the lines
 * containing the specified keyword (arg1)
 * @param arg1
 */
void MainWindow::on_filter_CB_currentTextChanged(const QString &arg1)
{
    //  Check filtering setting
    if (arg1 == "All")
        ui->vel_TE->setPlainText(vhLog);
    else
    {
        QStringList source = vhLog.split("\n");
        ui->vel_TE->setPlainText("");

        for (QString line : source)
        {
            if (line.contains(arg1, Qt::CaseSensitive))
                ui->vel_TE->setPlainText(ui->vel_TE->toPlainText()+line+'\n');
        }
    }
}

/**
 * @brief Changes time-period for sending telemetry data, default 1.5s
 * (Overview)
 */
void MainWindow::on_updateTime_SB_editingFinished()
{
    static double oldVal = 0;

    //  Refresh update interval for telemetry only if spinBox value has changed
    if (oldVal != ui->updateTime_SB->value())
    {
        LogLine("Changing update time to " + QString::number(ui->updateTime_SB->value()));
        oldVal = ui->updateTime_SB->value();
    }
}

///-----------------------------------------------------------------------------
///         Tab button events                                          [CLICKED]
///-----------------------------------------------------------------------------
/**
 * @brief Initiate radar scan (Overview->Scan)
 */
void MainWindow::on_scan_bt_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x00"};

    MakeRequest((uint8_t*)command, RADAR_UID, RADAR_SCAN, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Reboot whole platform (Overview->Reboot)
 */
void MainWindow::on_reboot_BT_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, PLAT_UID, PLAT_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Clear status labels for event logger status (Overview->Clear)
 */
void MainWindow::on_clearStat_PB_clicked()
{
    for (int i = 0; i < 8; i++)
    {
        if (pinv[i] != NULL)
            pinv[i]->setVisible(false);
        if (labOverview[i] != 0)
            labOverview[i]->setStyleSheet("background-color:rgb(126, 189, 189);\ncolor:#454545;\nborder-radius:3px;");
        if (labInstruments[i] != 0)
        {
            labInstruments[i]->setStyleSheet("background-color:rgb(126, 189, 189);\ncolor:#454545;\nborder-radius:3px;");
            labInstruments[i]->setText(events[0]);
        }
    }
}

/**
 * @brief Clear GUI log (Overview->GUI log)
 */
void MainWindow::on_clrLog_clicked()
{
    ui->log->setPlainText("");
}

/**
 * @brief Clear vehicle's event log (Overview->Vehicle event log)
 */
void MainWindow::on_clrVel_PB_clicked()
{
    ui->vel_TE->setPlainText("");
    vhLog = "";
}


///-----------------------------------------------------------------------------
///         Steering buttons (pressed & released events)               [CLICKED]
///-----------------------------------------------------------------------------
/**
 * @brief Called by steering buttons when they are released, immidiately halts
 * all running engines
 */
void MainWindow::HaltEngines()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    const float perc = 0.0;
    char args[8] = {0};

    MakeRequest((uint8_t*)command, ENGINES_UID, ENG_T_MOVE_PERC, 0, 0);
    //  Assemble arguments
    args[0] = ENG_DIR_FW;
    memcpy((void*)(args+1), &perc, sizeof(float));
    memcpy((void*)(args+1+sizeof(float)), &perc, sizeof(float));

    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 9);

    SendCommand(command, commandLen);
}

void MainWindow::on_fwd_PB_pressed()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    const float perc = 100.0;
    char args[8] = {0};

    MakeRequest((uint8_t*)command, ENGINES_UID, ENG_T_MOVE_PERC, 0, 0);
    //  Assemble arguments
    args[0] = ENG_DIR_FW;
    memcpy((void*)(args+1), &perc, sizeof(float));
    memcpy((void*)(args+1+sizeof(float)), &perc, sizeof(float));

    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 9);

    SendCommand(command, commandLen);
    ui->fwd_PB->setStyleSheet("background-color:#00FF00;");
}

void MainWindow::on_bck_PB_pressed()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    const float perc = 100.0;
    char args[8] = {0};

    MakeRequest((uint8_t*)command, ENGINES_UID, ENG_T_MOVE_PERC, 0, 0);
    //  Assemble arguments
    args[0] = ENG_DIR_BW;
    memcpy((void*)(args+1), &perc, sizeof(float));
    memcpy((void*)(args+1+sizeof(float)), &perc, sizeof(float));

    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 9);

    SendCommand(command, commandLen);
    ui->bck_PB->setStyleSheet("background-color:#00FF00;");
}

void MainWindow::on_right_PB_pressed()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    float perc = 100.0;
    char args[8] = {0};

    MakeRequest((uint8_t*)command, ENGINES_UID, ENG_T_MOVE_PERC, 0, 0);
    //  Assemble arguments
    args[0] = ENG_DIR_FW;
    memcpy((void*)(args+1), &perc, sizeof(float));
    perc = 0.0;
    memcpy((void*)(args+1+sizeof(float)), &perc, sizeof(float));

    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 9);

    SendCommand(command, commandLen);
    ui->right_PB->setStyleSheet("background-color:#00FF00;");
}

void MainWindow::on_left_PB_pressed()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    float perc = 0.0;
    char args[8] = {0};

    MakeRequest((uint8_t*)command, ENGINES_UID, ENG_T_MOVE_PERC, 0, 0);
    //  Assemble arguments
    args[0] = ENG_DIR_FW;
    memcpy((void*)(args+1), &perc, sizeof(float));
    perc = 100.0;
    memcpy((void*)(args+1+sizeof(float)), &perc, sizeof(float));

    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 9);

    SendCommand(command, commandLen);
    ui->left_PB->setStyleSheet("background-color:#00FF00;");
}

void MainWindow::on_fwd_PB_released()
{
    HaltEngines();
    ui->fwd_PB->setStyleSheet("background-color:#454545;");
}

void MainWindow::on_bck_PB_released()
{
    HaltEngines();
    ui->bck_PB->setStyleSheet("background-color:#454545;");
}

void MainWindow::on_right_PB_released()
{
    HaltEngines();
    ui->right_PB->setStyleSheet("background-color:#454545;");
}

void MainWindow::on_left_PB_released()
{
    HaltEngines();
    ui->left_PB->setStyleSheet("background-color:#454545;");
}
