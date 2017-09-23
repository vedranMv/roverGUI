#include "mainwindow.h"

///-----------------------------------------------------------------------------
///         Inertial group                                            [INERTIAL]
///-----------------------------------------------------------------------------
/**
 * @brief Toggle sampling of IMU data (Instruments->MPU9250)
 * @param checked If true turns on sampling of IMU on vehicle,
 *                if false sampling inhibited
 */
void MainWindow::on_imuSamp_CB_toggled(bool checked)
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {(char)checked, 0};

    MakeRequest((uint8_t*)command, MPU_UID, MPU_LISTEN, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Request Hard-Reboot of inertial unit (Instruments->MPU9250)
 */
void MainWindow::on_inReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, MPU_UID, MPU_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Soft-reboot of inertial unit (Instruments->MPU9250)
 */
void MainWindow::on_inSofReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, MPU_UID, MPU_SOFT_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}
///-----------------------------------------------------------------------------
///         Platform group                                            [PLATFORM]
///-----------------------------------------------------------------------------
/**
 * @brief Request status update for all modules from the vehicle
 * (Instruments->Platform->Event log)
 */
void MainWindow::on_evlogUpd_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x00"};

    MakeRequest((uint8_t*)command, PLAT_UID, PLAT_EVLOG_DUMP, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Request Hard-Reboot of communication module (Instruments->Platform)
 */
void MainWindow::on_commReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, ESP_UID, ESP_T_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Request print of all tasks currently in task scheduler
 * (Instruments->Platform->Task scheduler)
 */
void MainWindow::on_tsUpd_PB_clicked()
{
    ui->tsLog_TE->setPlainText("");

    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x00"};

    MakeRequest((uint8_t*)command, PLAT_UID, PLAT_TS_DUMP, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Sends command to clear and reset event logger
 * (Instruments->Platform->Event log)
 */
void MainWindow::on_evlogReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[2] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, EVLOG_UID, EVLOG_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

/**
 * @brief Request Hard-Reboot of Platform (Instruments->Platform->Reboot)
 */
void MainWindow::on_platReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {REBOOT_CODE, 0};

    MakeRequest((uint8_t*)command, PLAT_UID, PLAT_SOFT_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}

///-----------------------------------------------------------------------------
///         Radar group                                                  [RADAR]
///-----------------------------------------------------------------------------

///-----------------------------------------------------------------------------
///         Engines group                                              [ENGINES]
///-----------------------------------------------------------------------------
/**
 * @brief Request Hard-Reboot of engines (Instruments->Engine->Reboot)
 */
void MainWindow::on_engReb_PB_clicked()
{
    uint16_t commandLen = 0;
    char command[50] = {0};
    char args[] = {"\x17"};

    MakeRequest((uint8_t*)command, ENGINES_UID, ENG_T_REBOOT, 0, 0);
    AppendArgs((uint8_t*)command, &commandLen, (void*)args, 1);

    SendCommand(command, commandLen);
}



