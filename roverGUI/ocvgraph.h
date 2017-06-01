#ifndef OCVGRAPH_H
#define OCVGRAPH_H

#include <opencv2/opencv.hpp>
#include <string>


class OCVGraph : public cv::Mat
{
public:
    //OCVGraph();
    OCVGraph(int height, int width, int type = CV_8UC3,
             const cv::Scalar &s =cv::Scalar::all(255));

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

    cv::Mat& GetMatImg();
private:
    cv::Point2i _UVtoXY(cv::Point2i &imageCoord);
    cv::Point2i _XYtoUV(cv::Point2i &graphCoord);

private:
    cv::Mat         _graphHolder;
    cv::Point2i     _center;
};

#endif // OCVGRAPH_H
