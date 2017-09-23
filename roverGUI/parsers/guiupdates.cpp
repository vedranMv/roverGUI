#include "mainwindow.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

///-----------------------------------------------------------------------------
///        Functions for refreshing GUI elements                           [GUI]
///-----------------------------------------------------------------------------
/**
 * @brief Update certain GUI labels with new status and color based on the event
 * which occurred in specified module
 * @param event
 * @param libUID
 */
void MainWindow::EventUpdateGUI(Events event, uint8_t libUID)
{
    QString lable = QString(events[event]);
    QString styleSheet;

    //  Select color based on event
    switch(event)
    {
    case EVENT_ERROR:
        {
            styleSheet = "background-color:rgb(255, 0, 4);";
        }
        break;
    case EVENT_UNINITIALIZED:
        {
            styleSheet = "background-color:rgb(126, 189, 189);";
        }
        break;
    case EVENT_STARTUP:
        {
            styleSheet = "background-color:rgb(177, 255, 134);";
            if (pinv[libUID] != 0)
                pinv[libUID]->setVisible(false);
        }
        break;
    case EVENT_INITIALIZED:
        {
            styleSheet = "background-color:rgb(170, 255, 0);";
        }
        break;
    case EVENT_OK:
        {
            styleSheet = "background-color:rgb(0, 255, 29);";
        }
        break;
    case EVENT_HANG:
        {
            styleSheet = "background-color:rgb(255, 167, 14);";
        }
        break;
    case EVENT_PRIOINV:
        {
            styleSheet = "background-color:rgb(120, 120, 120);";
            if (pinv[libUID] != 0)
                pinv[libUID]->setVisible(true);
        }
        break;
    }
    styleSheet += "\ncolor:#454545;\nborder-radius:3px;";

    //  Update labels with new text and color
    if (labOverview[libUID] != 0)
        labOverview[libUID]->setStyleSheet(styleSheet);
    if (labInstruments[libUID] != 0)
    {
        labInstruments[libUID]->setStyleSheet(styleSheet);
        labInstruments[libUID]->setText(lable);
    }
}
/**
 * @brief Append new measurement to one of realtime-graphs in GUI
 * @param graph Reference to the realtime-graph
 * @param old Last value plotted in graph
 * @param val New value being appended to graph
 * @param renderer Pointer to OpenGL graph holder
 */
void MainWindow::AppendToGraph(OCVGraph &graph, double old, double val, CQtOpenCVViewerGl *renderer)
{
    //  Update plot with delta value
    cv::Point2d endP(0, val);
    graph.LineCartesian(endP, cv::Point2d(0, old), COLOR_WHITE);

    //  Shift data in latency plot one column to the left
    cv::Mat &shiftPlot = graph.GetMatImg();
    cv::Mat out(shiftPlot.size(), shiftPlot.type(), cv::Scalar::all(255));
    shiftPlot(cv::Rect(1,0, shiftPlot.cols-1,shiftPlot.rows)).copyTo(out(cv::Rect(0,0,shiftPlot.cols-1,shiftPlot.rows)));
    out.copyTo(shiftPlot);
    //  Match color of background in shifted line with that of GUI background
    for (uint16_t i = 0; i < shiftPlot.rows; i++)
    {
        cv::Vec3b &pix = shiftPlot.at<cv::Vec3b>(i, shiftPlot.cols-1);

        if (pix.val[0] != 0xFF)
            break;
        pix.val[0] = 0x45;
        pix.val[1] = 0x45;
        pix.val[2] = 0x45;
    }

    //  Copy graph into new holder to be able to apply axes
    OCVGraph temp(graph);

    //  Draw axes and horizontal lines for every 10ms
    temp.AddAxes(20, 10, 2, 2);

    renderer->showImage( temp.GetMatImg() );
}

void MainWindow::UpdateRPPlot(double roll, double pitch)
{
    //  Rotation of crosshair (roll)
    cv::Mat tmp;
    rpDef.GetMatImg().copyTo(tmp);
    cv::Mat rot_mat = cv::getRotationMatrix2D( cv::Point2d(100, 100), -roll , 1);

    cv::warpAffine(rpDef.GetMatImg(), tmp, rot_mat, tmp.size(), CV_INTER_LINEAR, 0, cv::Scalar(0x45,0x45,0x45));

    //  Add axes to visualize pitch
    OCVGraph ne(tmp);
    ne.SetRange(-100, 100, -100+pitch, 100-pitch);
    ne.SetCenter(100, 100-pitch);
    ne.AddAxes(100, 10, 1, 2);

    //  Add perspective lines
    ne.LineCartesian(cv::Point2d(-80, -20), cv::Point2d(-20,0), COLOR_50GREY);
    ne.LineCartesian(cv::Point2d( 80, -20), cv::Point2d( 20,0), COLOR_50GREY);

    ne.LineCartesian(cv::Point2d(-80, -40), cv::Point2d(-20,-20), COLOR_50GREY);
    ne.LineCartesian(cv::Point2d( 80, -40), cv::Point2d( 20,-20), COLOR_50GREY);
    ui->rpPlot->showImage(ne.GetMatImg());
}
