/**
 *  Date created: 1.6.2017
 *  Author: Vedran Mikov
 *
 *  OpenCV-based simple graph plotter. Allows user to set center of the graph at
 *  any pixel in the image and then plot simple curves in reference to that point
 *  as origin of coordinate system.
 *
 *  Current API tries to follow OpenCV argument naming and order as much as possible
 *
 *  @version 1.3.1
 *  V1.0.0 - 1.6.2017
 *  +Custom origin of coordinate system at any point of image. Support for
 *  plotting circles, lines (in Cartesian and polar coordinate system) and
 *  writing text.
 *  V1.1.0
 *  +Save plot to a given path
 *  V1.2.0 - 17.6.2017
 *  +Added clear function to reset the graph
 *  +Added option to plot N-degree polynomials in Cartesian, within given range
 *  +Show data axes, variable number of divisions for X and Y axes
 *  V1.3.0 - 20.6.2017
 *  +Added macros for common colors
 *  +Can print legend based on the color of a function
 *  +Added interface for setting X and Y intervals for axes
 *  +Expanded PolyN function by adding more options for customization
 *  V1.3.1 - 2.7.2017
 *  +Bugfix: Printing axis lables when outside of range
 *  +Bugfix: Constructor copies original Mat holder, instead of passing reference
 *
 *  TODO:
 *  +Add ability to plot arbitrary functions
 */

#ifndef OCVGRAPH_H
#define OCVGRAPH_H

#include <opencv2/opencv.hpp>
#include <string>
#include <tuple>
#include <vector>

/* Commonly used colors    */
#define COLOR_BLACK     cv::Scalar(  0,  0,  0)
#define COLOR_WHITE     cv::Scalar(255,255,255)
#define COLOR_25GREY    cv::Scalar(192,192,192)
#define COLOR_50GREY    cv::Scalar(128,128,128)
#define COLOR_75GREY    cv::Scalar( 64, 64, 64)
#define COLOR_RED       cv::Scalar(  0,  0,255)
#define COLOR_GREEN     cv::Scalar(  0,255,  0)
#define COLOR_BLUE      cv::Scalar(255,  0,  0)
#define COLOR_YELLOW    cv::Scalar(  0,255,255)
#define COLOR_PURPLE    cv::Scalar(0x80,0,0x80)
#define COLOR_BROWN     cv::Scalar(0x2A,0x2A,0xA5)

//  Perimitted directions to place legend
enum legLoc {TopLeft, TopRight, BottomLeft, BottomRight, Left, Right};

typedef std::tuple<uint8_t, cv::Scalar, std::string, int, double> legEntry;

class OCVGraph
{
public:
    OCVGraph(OCVGraph &graph);
    OCVGraph(cv::Mat &graphplot);
    OCVGraph(int height, int width, const cv::Scalar &s =cv::Scalar::all(255));
    ~OCVGraph();

    void            SetCenter(int uc, int vc);
    void            SetCenter(cv::Point2i center);
    cv::Point2i&    GetCenter();

    void SetRange(double xmin, double xmax, double ymin, double ymax);
    void SetXRangeKeepAspectR(double xmin, double xmax, bool moveCenter=false);

    void LineCartesian(cv::Point2d p1, cv::Point2d p2 = cv::Point2d(0,0),
                       cv::Scalar color = cv::Scalar::all(0),
                       int thickness=1, int lineType=8, int shift=0);

    void LinePolar(double angle, double rad, cv::Point2d p2 = cv::Point2d(0,0),
                   cv::Scalar color = cv::Scalar::all(0),
                   int thickness=1, int lineType=8, int shift=0);

    void Circle(double rad, cv::Point2d p1 = cv::Point2d(0,0),
                cv::Scalar color = cv::Scalar::all(0), int thickness=1,
                int lineType=8, int shift=0);

    void PolyN(std::vector<double>&coefs, double xmin=0, double xmax=0,
               cv::Scalar color = cv::Scalar::all(0), int thickness=1,
               int lineType=8, int shift=0);

    void Text(std::string txt, cv::Point2d p1, int fontFace=2, double scale=0.3,
              cv::Scalar color=cv::Scalar::all(128), int thickness=1,
              int lineType=8, bool blo=false);

    void AddAxes(double xticks = 1.0, double yticks = 1.0, int xlarge = 5,
                 int ylarge = 5);
    void AddToLegend(uint8_t index, cv::Scalar color, std::string txt,
                     int fontFace=2, double scale=0.4);
    void AppendLegend(legLoc location = TopRight);

    void        Export(std::string path);
    cv::Mat&    GetMatImg();
    void        Clear(bool resetCenter = false);

    OCVGraph& operator=(OCVGraph& arg);
    OCVGraph& operator=(OCVGraph arg);


private:
    cv::Point2d _UVtoXY(cv::Point2i imageCoord);
    cv::Point2i _XYtoUV(cv::Point2d graphCoord);


private:
    cv::Mat                 _graphHolder;
    cv::Point2i             _center;
    cv::Scalar              _background;
    std::vector<legEntry>   _legend;
    double                  _xlim[2];
    double                  _ylim[2];
};

#endif // OCVGRAPH_H
