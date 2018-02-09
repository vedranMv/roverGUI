#include "mainwindow.h"

///-----------------------------------------------------------------------------
///         Stream data parsers                           [TELEMETRY & COMMANDS]
///-----------------------------------------------------------------------------
/**
 * @brief Parse response on a give command (such as radar scan)
 * @param respStr Response from vehicle to a sent command
 */
bool MainWindow::ParseCommandResp(QString respStr)
{
    //  Setup graph background
    OCVGraph image(blank);

    uint16_t it = 0;

    if(respStr.length() < 100)
        return false;
    for (uint16_t i = 10; i <170; i++)
        image.LinePolar((double)i, (double)((int)respStr.at(i-10+it).toAscii()/2), cv::Point2d(0,0), COLOR_WHITE);

    // Show the image
    ui->radarPlot->showImage( image.GetMatImg() );

    return true;
}

/**
 *  @brief Parse incoming telemetry frame. Format is:
 *  uptimeMS:Roll:Pitch:Yaw:distanceLeft:distanceRight:speedLeft:speedRight:accX:accY:accZ
 *  @param teleStr
 */
void MainWindow::ParseTelemetry(QString teleStr)
{
    //  Saved variables from previous call to this function
    static double oldTime = 0,
                  oldRoll = 0,
                  oldPitch = 0,
                  oldYaw = 0;

    //  Find '1*' sequence, start of EventLog telemetry frame
    QStringList entries = teleStr.split("1*");

    //  Loop through all events in this list
    for (QString X : entries)
    {
        QStringList parts = X.split(":", QString::SkipEmptyParts);
        //  Skip broken/short frames
        if (parts.length() < 10)
            continue;

        ///EXTRACT uptime and update GUI elements using it
        ui->utime_LE->setText(QString::number(parts[0].toDouble()/1000));
        ui->mUtime_LE_2->setText(QString::number(parts[0].toDouble()/1000));
        //  Convert time in string to number (ms -> s)
        uint32_t dd, hh, mm;
        double ss = parts[0].toDouble()/1000;
        mm = (ss/60);
        ss -= ((double)mm)*60;
        hh = mm / 60;
        mm -= hh * 60;
        dd = hh / 24;
        hh -= dd * 24;
        //  Updatime time on top of window
        ui->mUtime_LE->setText(QString::number(dd)+"d, "+QString::number(hh)+":"+QString::number(mm)+":"+QString::number(ss));
        //  Calculate time since last received frame to estimate latency
        ui->deltams_LE->setText(QString::number(parts[0].toDouble()/1000-oldTime));
        oldTime = parts[0].toDouble()/1000;

        ///EXTRACT Roll-Pitch-Yaw information
        ui->roll_LE->setText(parts[1]);
        AppendToGraph(rollGraph, oldRoll, parts[1].toDouble(), ui->rollPlot);
        oldRoll = parts[1].toDouble();

        ui->pitch_LE->setText(parts[2]);
        AppendToGraph(pitchGraph, oldPitch, parts[2].toDouble(), ui->pitchPlot);
        oldPitch = parts[2].toDouble();

        ui->yaw_LE->setText(parts[3]);
        AppendToGraph(yawGraph, oldYaw, parts[3].toDouble(), ui->yawPlot);
        oldYaw = parts[3].toDouble();

        //  Update Roll-pitch graph
        UpdateRPPlot(ui->roll_LE->text().toDouble(), ui->pitch_LE->text().toDouble());

        //  Update latency plot with delta value
        cv::Point2d endP(98, (ui->deltams_LE->text().toDouble()-ui->updateTime_SB->value())*1000.0);
        latencyGraph.LineCartesian(endP, cv::Point2d(98, 0));

        //  Shift data in latency plot one column to the left
        cv::Mat &lastPlot = latencyGraph.GetMatImg();
        cv::Mat out(lastPlot.size(), lastPlot.type(), cv::Scalar::all(255));
        lastPlot(cv::Rect(1,0, lastPlot.cols-1,lastPlot.rows)).copyTo(out(cv::Rect(0,0,lastPlot.cols-1,lastPlot.rows)));
        out.copyTo(lastPlot);
        //  Match color of background in shifted line with that of GUI background
        for (uint16_t i = 0; i < lastPlot.rows; i++)
        {
            cv::Vec3b &pix = lastPlot.at<cv::Vec3b>(i, lastPlot.cols-1);

            if (pix.val[0] != 0xFF)
                break;
            pix.val[0] = 0x45;
            pix.val[1] = 0x45;
            pix.val[2] = 0x45;
        }

        //  Copy graph into new holder to be able to apply axes
        OCVGraph temp(latencyGraph);

        //  Draw axes and horizontal lines for every 10ms
        temp.AddAxes(15, 10, 15, 1);
        temp.LineCartesian(cv::Point2d(-1, 10), cv::Point2d(99, 10), COLOR_25GREY);
        temp.LineCartesian(cv::Point2d(-1, 20), cv::Point2d(99, 20), COLOR_25GREY);
        temp.LineCartesian(cv::Point2d(-1, 30), cv::Point2d(99, 30), COLOR_25GREY);
        temp.LineCartesian(cv::Point2d(-1, 40), cv::Point2d(99, 40), COLOR_25GREY);

        ui->latencyPlot->showImage( temp.GetMatImg() );

        ///EXTRACT Engine data
        ui->enLDist_LE->setText(parts[4]);
        ui->enRDist_LE->setText(parts[5]);
        ui->enLSpeed_LE->setText(parts[6]);
        ui->enRSpeed_LE->setText(parts[7]);

        uint8_t val = abs(100.0*(parts[6].toDouble()/25.0));
        ui->maxSpeedL_PB->setValue((val>100)?100:val);
        val = abs(100.0*(parts[7].toDouble()/25.0));
        ui->maxSpeedR_PB->setValue((val>100)?100:val);

        if ((ui->maxSpeedL_PB->value() > 0) && (ui->maxSpeedR_PB->value() > 0))
            ui->engActive_GV->setStyleSheet("background-image:url(:/new/prefix1/imgs/backBoth.png);");
        else if (ui->maxSpeedL_PB->value() > 0)
            ui->engActive_GV->setStyleSheet("background-image:url(:/new/prefix1/imgs/backLeft.png);");
        else if (ui->maxSpeedR_PB->value() > 0)
            ui->engActive_GV->setStyleSheet("background-image:url(:/new/prefix1/imgs/backRight.png);");
        else
            ui->engActive_GV->setStyleSheet("background-image:url(:/new/prefix1/imgs/back.png);");

        ///EXTRACT acceleration data
        ui->accelX_LE->setText(parts[8]);
        ui->accelY_LE->setText(parts[9]);
        ui->accelZ_LE->setText(parts[10]);
    }
}

/**
 * @brief Parse a telemetry line containing event log data
 * @param teleStr String containing event log entri(es)
 */
void MainWindow::ParseEventLog(QString teleStr)
{
    //  Find '2*' sequence, start of EventLog telemetry frame
    QStringList entries = teleStr.split("2*");

    //  Loop through all events in this list
    for (QString X : entries)
    {
        QStringList parts = X.split(":", QString::SkipEmptyParts);
        //  Skip broken/short frames
        if (parts.length() < 5)
            continue;

        QString msg;
        msg = parts[1] + ": " + QString(events[parts[4].toInt()]) + " in "
              + QString(libName[parts[2].toInt()]) + " on task " +
               QString(parts[3]);
        LogLine(msg, ui->vel_TE);

        //  Update GUI elements with data from event log
        EventUpdateGUI((Events)parts[4].toInt(), parts[2].toInt());

        //  If this is the last line from event log (one indexed 0)
        if ((parts[0].toInt() == 0))
        {
            uint16_t commandLen = 0,
                     i = 1; //  Start at 1 to skip '[' on first position
            char command[50] = {0},
                 args[5] = {0};
            QString tmpStr;
            uint32_t timeStamp;

            //  Extract timestamp in ms from this frame and save it to args
            //  for constructing the request
            while(parts[1][i] != ']')
                tmpStr += parts[1][i++];
            //  Convert string to int
            timeStamp = tmpStr.toLong();
            //  Copy int value to arguments list
            memcpy(args, &timeStamp, sizeof(uint32_t));

            //  Send request to drop internal event log on the MCU
            MakeRequest((uint8_t*)command, EVLOG_UID, EVLOG_DROP, 0, 0);
            AppendArgs((uint8_t*)command, &commandLen, (void*)args, sizeof(uint32_t));
            //  Send command to TCP client
            SendCommand(command, commandLen);
        }
    }
}

/**
 * @brief Parse a telemetry line containing task scheduler entries
 * @param teleStr String containing event log entri(es)
 */
void MainWindow::ParseTaskEntry(QString teleStr)
{
    //  Find '3*' sequence, start of TaskScheudler telemetry frame
    QStringList entries = teleStr.split("3*");

    //  Loop through all events in this list
    for (QString X : entries)
    {
        QStringList parts = X.split(":", QString::SkipEmptyParts);
        //  Skip broken/short frames
        if (parts.length() < 11)
            continue;

        QString msg;
        double avgMiss = (parts[7].toDouble())/(parts[6].toDouble());
        msg = parts[0] + "-|" + parts[4] + "|: " + QString(allTasks[parts[1].toInt()][parts[2].toInt()])
              + ", " + parts[3] +" ms \n";
        msg += "    "+parts[6]+"("+QString::number(avgMiss)+")"+"/"+parts[5];
        if (parts[5].toInt() != 0.0)
            //  parts[9] is run-time accumulator in seconds, convert to ms first!
            msg += "    <avg: "+QString::number((parts[8].toDouble()+1000.0*parts[9].toDouble())/parts[5].toDouble())+", max: "+parts[10]+">";
        else
            msg += "    <avg: 0, max: "+parts[10]+">";

        LogLine(msg, ui->tsLog_TE);
    }
}
