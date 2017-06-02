/**
 *  Date created: 1.6.2017
 *  Author: Vedran Mikov
 *
 *  OpenCV-based simple graph plotter. Allows user to set center of the graph at
 * any pixel in the image and then plot simple curves in reference to that point
 * as origin of coordinate system.
 *
 *  @version 1.0.0
 *  V1.0.0 - 1.6.2017
 *  +Custom origin of coordinate system at any point of image. Support for
 * plotting circles, lines (in cartesian and polar coordinate system) and
 * writing text.
 *  V1.1.0
 *  +Save plot to a given path
 *
 *  TODO:
 *  +Add ability to plot arbitrary functions
 *  +Add support for zoom in/out
 */

#ifndef OCVGRAPH_H
#define OCVGRAPH_H

#include <opencv2/opencv.hpp>
#include <string>


class OCVGraph
{
public:
    OCVGraph(OCVGraph &graph);
    OCVGraph(cv::Mat &graphplot);
    OCVGraph(int height, int width, int type = CV_8UC3,
             const cv::Scalar &s =cv::Scalar::all(255));
    ~OCVGraph();

    void SetCenter(int uc, int vc);
    void SetCenter(cv::Point2i center);
    cv::Point2i& GetCenter();

    void LineCartesian(cv::Point2i p1, cv::Point2i p2 = cv::Point2i(0,0),
                       cv::Scalar color = cv::Scalar::all(0));
    void LinePolar(double angle, double rad, cv::Point2i p2 = cv::Point2i(0,0),
                   cv::Scalar color = cv::Scalar::all(0));
    void Circle(double rad, cv::Scalar color = cv::Scalar::all(0),
                cv::Point2i p1 = cv::Point2i(0,0));
    void Text(std::string txt, cv::Point2i p1);

    void SaveToFile(std::string path);
    cv::Mat& GetMatImg();

    OCVGraph& operator=(OCVGraph& arg);
    OCVGraph& operator=(OCVGraph arg);

private:
    cv::Point2i _UVtoXY(cv::Point2i &imageCoord);
    cv::Point2i _XYtoUV(cv::Point2i &graphCoord);

private:
    cv::Mat         _graphHolder;
    cv::Point2i     _center;
};

#endif // OCVGRAPH_H
