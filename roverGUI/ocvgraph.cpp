#include "ocvgraph.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


OCVGraph::OCVGraph(int height, int width, int type, const cv::Scalar& s)
    : _graphHolder(height+1, width+1, type, s), _center(width/2, height/2)
{

}

/**
 * @brief Set center of a graph in image coordinate (which pixel corresponds to 0,0)
 * @param uc pixel's x-coordinate (along width of the image)
 * @param vc pixel's y-coordinate (along height of the image)
 */
void OCVGraph::SetCenter(int uc, int vc)
{
    _center = cv::Point2i(uc, uc);
}
void OCVGraph::SetCenter(cv::Point2i center)
{
    _center = center;
}

/**
 * @brief Get center of a graph(0,0)
 * @return center point(0,0) of graph in image coordinates
 */
cv::Point2i& OCVGraph::GetCenter()
{
    return _center;
}

/**
 * @brief Draw a line in cartesian coordinate system between points p1 and p2
 * @param p1 starting point of the line in graph coordinates(!!)
 * @param p2 ending point of the line in graph coordinates(!!)
 */
void OCVGraph::LineCartesian(cv::Point2i p1, cv::Point2i p2, cv::Scalar color)
{
    cv::line(_graphHolder, _XYtoUV(p1), _XYtoUV(p2), color);
}

/**
 * @brief Draw a line from p1 in polar coordinate system given angle and radius
 * @param angle in degrees
 * @param rad
 * @param p1 starting point of the line in graph coordinates(!!)
 * @param color
 */
void OCVGraph::LinePolar(double angle, double rad, cv::Point2i p1, cv::Scalar color)
{
    //  Convert angle to radians
    angle = angle * 3.14159625 / 180;
    //  Calculate ending point in cartesian coordinates
    cv::Point2i p2(rad * cos(angle) + p1.x, rad * sin(angle) + p1.y);

    //  Plot line in cartesian coordinate
    LineCartesian(p1, p2);
}

/**
 * @brief Draw a circle with given center, radius and (optionally) color
 * @param rad radius of circle
 * @param color
 * @param p1 center of circle in graph coordinates
 */
void OCVGraph::Circle(double rad, cv::Scalar color, cv::Point2i p1)
{
    cv::circle(_graphHolder, _XYtoUV(p1), rad, color, 1);
}

/**
 * @brief Add text to a specific point in graph
 * @param txt
 * @param p1
 */
void OCVGraph::Text(std::string txt, cv::Point2i p1)
{
    cv::putText(_graphHolder, txt, _XYtoUV(p1), 2, 0.3, cv::Scalar::all(128));
}

/**
 * @brief Get image of a graph currently stored in this object
 * @return Mat type image of current graph
 */
cv::Mat& OCVGraph::GetMatImg()
{
    return _graphHolder;
}

/**
 * @brief Convert U,V pixel coordinates into a corresponding X,Y graph coordinates
 * @param imageCoord coordinates of pixel in image coordinates
 * @return cv::Point2i X,Y graph coordinates
 */
cv::Point2i OCVGraph::_UVtoXY(cv::Point2i &imageCoord)
{
    return cv::Point2i(imageCoord.x-_center.x, _center.y-imageCoord.y);
}

/**
 * @brief Convert graph coordinates to image coordinates
 * @param graphCoord
 * @return
 */
cv::Point2i OCVGraph::_XYtoUV(cv::Point2i &graphCoord)
{
    return cv::Point2i(graphCoord.x+_center.x, _center.y-graphCoord.y);
}
