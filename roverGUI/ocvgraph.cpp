#include "ocvgraph.h"
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


/**
 *  Double to string with max 2 decimal places
 */
std::string dtos(double arg)
{
    std::string retVal;

    if (arg < 0.0)
        retVal += '-';

    arg = std::abs(arg);
    retVal += std::to_string((int)arg);

    //  Have decimals, extract max two
    if (arg-(trunc(arg)) != 0.0)
    {
        retVal += '.';
        retVal += std::to_string((int)((arg-trunc(arg))*100.0));
    }

    return retVal;
}

///-----------------------------------------------------------------------------
///                      Class constructor & destructor                 [PUBLIC]
///-----------------------------------------------------------------------------

OCVGraph::OCVGraph(OCVGraph &graph)
    : _center(graph._center)
{
    _background = cv::Scalar::all(255);
    _xlim[0] = graph._xlim[0];
    _xlim[1] = graph._xlim[1];
    _ylim[0] = graph._ylim[0];
    _ylim[1] = graph._ylim[1];

    graph._graphHolder.copyTo(_graphHolder);
}

OCVGraph::OCVGraph(cv::Mat &graphplot)
    : _graphHolder(graphplot), _center(graphplot.cols/2, graphplot.rows/2)
{
    _background = cv::Scalar::all(255);
    _xlim[0] = -graphplot.cols/2;
    _xlim[1] =  graphplot.cols/2;
    _ylim[0] = -graphplot.rows/2;
    _ylim[1] =  graphplot.rows/2;
}

OCVGraph::OCVGraph(int height, int width, const cv::Scalar& s)
    : _graphHolder(height, width, CV_8UC3, s), _center(width/2, height/2)
{
    _background = s;
    _xlim[0] = -width/2;
    _xlim[1] =  width/2;
    _ylim[0] = -height/2;
    _ylim[1] =  height/2;
}

OCVGraph::~OCVGraph()
{}

///-----------------------------------------------------------------------------
///                      Manipulation of center of graph                [PUBLIC]
///-----------------------------------------------------------------------------

/**
 * @brief Set center of a graph in image coordinate (which pixel corresponds to 0,0)
 * @param uc Pixel's x-coordinate (along width of the image)
 * @param vc Pixel's y-coordinate (along height of the image)
 */
void OCVGraph::SetCenter(int uc, int vc)
{
    _center = cv::Point2i(uc, vc);
}
void OCVGraph::SetCenter(cv::Point2i center)
{
    _center = center;
}

/**
 * @brief Get center of a graph(0,0)
 * @return Center point(0,0) of graph in image coordinates
 */
cv::Point2i& OCVGraph::GetCenter()
{
    return _center;
}

///-----------------------------------------------------------------------------
///                      Manipulation of scale of graph                 [PUBLIC]
///-----------------------------------------------------------------------------

/**
 * Set arbitrary range for both X and Y axis
 * @note Discouraged to use, it does not maintain graph proportions
 */
void OCVGraph::SetRange(double xmin, double xmax, double ymin, double ymax)
{
    _xlim[0] = xmin;
    _xlim[1] = xmax;

    _ylim[0] = ymin;
    _ylim[1] = ymax;
}

/**
 * Set the range for X axis and automatically adjust Y axis to meet proportions
 * @note Can move graph center in X to keep const step size within +X and -X
 * @param xmin -X
 * @param xmax +X
 * @param moveCenter If true, function adjusts center in X direction to preserve
 *  equal step size in +X and -X region of graph; If false, breaks proportion!
 */
void OCVGraph::SetXRangeKeepAspectR(double xmin, double xmax, bool moveCenter)
{
    _xlim[0] = xmin;
    _xlim[1] = xmax;

    //  Calculate step (units per pixel) in X-axis
    double step = (abs(_xlim[0])+abs(_xlim[1]))/((double)_graphHolder.cols);

    //  Apply same step size to Y-axis
    _ylim[0] = -((double)(_graphHolder.rows-_center.y)) * step;
    if (_ylim[0] == 0)
        _ylim[0] = -0.001;
    _ylim[1] = ((double)_center.y) * step;
    if (_ylim[1] == 0)
        _ylim[1] = 0.001;

    if (moveCenter)
        _center.x = -_xlim[0]/step;

}

///-----------------------------------------------------------------------------
///                      Plotting functions                             [PUBLIC]
///-----------------------------------------------------------------------------

/**
 * @brief Draw a line in Cartesian coordinate system between points p1 and p2
 * @param p1 Starting point of the line in graph coordinates(!!)
 * @param p2 Ending point of the line in graph coordinates(!!)
 * @param thickness Optional OpenCV parameter
 * @param lineType Optional OpenCV parameter
 * @param shift Optional OpenCV parameter
 */
void OCVGraph::LineCartesian(cv::Point2d p1, cv::Point2d p2, cv::Scalar color,
                             int thickness, int lineType, int shift)
{
    cv::line(_graphHolder, _XYtoUV(p1), _XYtoUV(p2), color, thickness,
             lineType, shift);
}

/**
 * @brief Draw a line from p1 in polar coordinate system given angle and radius
 * @param angle Angle in degrees
 * @param rad
 * @param p1 Starting point of the line in graph coordinates(!!)
 * @param color
 * @param thickness Optional OpenCV parameter
 * @param lineType Optional OpenCV parameter
 * @param shift Optional OpenCV parameter
 */
void OCVGraph::LinePolar(double angle, double rad, cv::Point2d p1, cv::Scalar color,
                         int thickness, int lineType, int shift)
{
    //  Convert angle to radians
    angle = angle * 3.14159625 / 180;
    //  Calculate ending point in Cartesian coordinates
    cv::Point2i p2(rad * cos(angle) + p1.x, rad * sin(angle) + p1.y);

    //  Plot line in Cartesian coordinate
    LineCartesian(p1, p2, color, thickness, lineType, shift);
}

/**
 * @brief Draw a circle with given center, radius and (optionally) color
 * @param rad Radius of circle
 * @param color
 * @param p1 Center of circle in graph coordinates
 * @param thickness Optional OpenCV parameter
 * @param lineType Optional OpenCV parameter
 * @param shift Optional OpenCV parameter
 */
void OCVGraph::Circle(double rad, cv::Point2d p1, cv::Scalar color,
                      int thickness, int lineType, int shift)
{
    //  Need to verify radius of ellipse in graph coordinates for each axis in
    //  case axes have different ranges -> result is ellipse
    cv::Point2i radUV = _XYtoUV(cv::Point2i(rad, rad));
    //  Calculate radius of ellipse in X and Y direction (based on scale of graph)
    cv::Size2i axes = cv::Size2i(-_center.x+(radUV.x), _center.y-(radUV.y));

    cv::ellipse(_graphHolder, _XYtoUV(p1), axes, 0, 0, 360, color, thickness,
                lineType, shift);
}

/**
 * Plot polynomial of form coefs[n-1]*x^(n-1)+coefs[n-2]*x^(n-2)+...+coefs[0]*x^(0)
 * in range between xmin and xmax. In case xmin and xmax are equal function is
 * plotted on interval visible in the graph
 * @param coefs Vector of polynomial coefficients. Coefficient at index i
 * is multiplied by x^i
 * @param xmin Lower bound of x while computing y
 * @param xmax Upper bound of x while computing y
 * @param color
 * @param thickness Optional OpenCV parameter
 * @param lineType Optional OpenCV parameter
 * @param shift Optional OpenCV parameter
 */
void OCVGraph::PolyN(std::vector<double>&coefs, double xmin, double xmax,
                     cv::Scalar color, int thickness, int lineType, int shift)
{
    cv::Point2i lastP;
    bool firstEntry = false;
    //  Function boundaries in image coordinates
    int umin = 0, umax = _graphHolder.cols;

    //  Update user-provided boundaries if given
    if (xmin != xmax)
    {
        umin = _XYtoUV(cv::Point2d(xmin, 0)).x;
        umax = _XYtoUV(cv::Point2d(xmax, 0)).x;
    }

    //  Compute function value only for X within image coordinates
    for (int iu = umin; iu < umax; iu++)
    {
        //  Function value saved here
        double y = 0;
        //  Translate image coordinate U into graph coordinate 'x'
        cv::Point2d tmp = _UVtoXY(cv::Point2i(iu, 0));

        //  Loop through all coefficients and calculate 'y'
        for (int i = (coefs.size()-1); i >= 0; i--)
            y += coefs[i] * pow(tmp.x, (double)(i));

        //  If within image boundaries turn pixel black to construct curve
        cv::Point2i imgC = _XYtoUV(cv::Point2d(tmp.x, y));

        if ((imgC.y >= 0) && (imgC.y < _graphHolder.rows) && firstEntry)
            cv::line(_graphHolder, imgC, lastP, color, thickness, lineType, shift);
        else if ((imgC.y >= 0) && (imgC.y < _graphHolder.rows) && !firstEntry)
            firstEntry = true;
        else
            continue;

        lastP = imgC;
    }
}

/**
 * @brief Add text to a point on graph
 * @param txt
 * @param p1 Origin point of text
 * @param fontFace
 * @param scale
 * @param color
 * @param thickness Optional OpenCV parameter
 * @param lineType Optional OpenCV parameter
 * @param blo Optional OpenCV parameter (Bottom left origin of text box)
 */
void OCVGraph::Text(std::string txt, cv::Point2d p1, int fontFace, double scale,
                    cv::Scalar color, int thickness, int lineType, bool blo)
{
    cv::putText(_graphHolder, txt, _XYtoUV(p1), fontFace, scale, color,
                thickness, lineType, blo);
}

/**
 * Plot data axes together with divisions and corresponding values
 * @param xticks Number of ticks between division lines on X-axis
 * @param yticks Number of ticks between division lines on Y-axis
 * @param xlarge Number of ticks between long division lines on X-axis
 * @param ylarge Number of ticks between long division lines on Y-axis
 */
void OCVGraph::AddAxes(double xticks, double yticks, int xlarge, int ylarge)
{
    //  Calculate longest side of each axis
    double xmax = (abs(_xlim[0]) > abs(_xlim[1])) ? abs(_xlim[0]) : abs(_xlim[1]);
    double ymax = (abs(_ylim[0]) > abs(_ylim[1])) ? abs(_ylim[0]) : abs(_ylim[1]);

    //  Draw axis lines
    LineCartesian(cv::Point2d(_xlim[0], 0), cv::Point2d(_xlim[1], 0));
    LineCartesian(cv::Point2d(0, _ylim[0]), cv::Point2d(0, _ylim[1]));

    //  Add ticks on X axis
    int tickCounter = 0;
    for (double ix = 0; ix < xmax; ix+=xticks)
    {
        double len;

        //  Larger division line is added every 'xlarge' ticks
        if ((tickCounter % xlarge) == 0)
        {
            //  Holds number of current tick in string format
            std::string txt;
            int baseline = 0;
            //  Size of larger division line. 100 chosen as a constant that
            //  produces lines of optimal length depending on the axis range
            len = (-_ylim[0]+_ylim[1])/100.0;

            if (ix < _xlim[1])
            {
                //  Add label with number 'ix'
                txt = dtos(ix);
                //  Calculate dimensions that text occupies (in image coord.)
                cv::Size txtSize = cv::getTextSize(txt, 2, 0.4, 1, &baseline);
                //  Convert image coord. to graph coord. (to match scaling)
                cv::Point2d txtimc = _UVtoXY(cv::Point2i(_center.x+txtSize.width/2, _center.y-txtSize.height));
                //  Appends text
                Text(txt, (cv::Point2d(ix, -1.5*len)-txtimc), 2, 0.4);
            }

            if ((-ix) > _xlim[0])
            {
                //  Add label with number '-ix'
                txt = dtos(-ix);
                //  Calculate dimensions that text occupies (in image coord.)
                cv::Size txtSize = cv::getTextSize(txt, 2, 0.4, 1, &baseline);
                //  Convert image coord. to graph coord. (to match scaling)
                cv::Point2d txtimc = _UVtoXY(cv::Point2i(_center.x+txtSize.width/2, _center.y-txtSize.height));
                //  Appends text
                Text(txt, (cv::Point2d(-ix, -1.5*len)-txtimc), 2, 0.4);
            }
        }
        else
            //  Size of smaller division line. 220 chosen as a constant that
            //  produces lines of optimal length depending on the axis range
            len = (-_ylim[0]+_ylim[1])/220.0;

        LineCartesian(cv::Point2d( ix, len), cv::Point2d( ix, -len));
        LineCartesian(cv::Point2d(-ix, len), cv::Point2d(-ix, -len));

        tickCounter++;
    }

    //  Add ticks on Y axis
    tickCounter = 0;
    for (double iy = 0; iy < ymax; iy+=yticks)
    {
        double len;

        //  Larger division line is added every 'ylarge' ticks
        if ((tickCounter % ylarge) == 0)
        {
            //  Holds number of current tick in string format
            std::string txt;
            int baseline = 0;
            //  Size of larger division line. 100 chosen as a constant that
            //  produces lines of optimal length depending on the axis range
            len = (-_xlim[0]+_xlim[1])/100.0;

            if (iy < _ylim[1])
            {
                //  Add label with number 'iy'
                txt = dtos(iy);
                //  Calculate dimensions that text occupies (in image coord.)
                cv::Size txtSize = cv::getTextSize(txt, 2, 0.4, 1, &baseline);
                //  Convert image coord. to graph coord. (to match scaling)
                cv::Point2d txtimc = _UVtoXY(cv::Point2i(_center.x+txtSize.width/2, _center.y-txtSize.height/2));
                txtimc.y = -txtimc.y;
                //  Appends text
                Text(txt, (cv::Point2d(len, iy)+txtimc), 2, 0.4);
            }

            if ((-iy) > _ylim[0])
            {
                //  Add label with number '-iy'
                txt = dtos(-iy);
                //  Calculate dimensions that text occupies (in image coord.)
                cv::Size txtSize = cv::getTextSize(txt, 2, 0.4, 1, &baseline);
                //  Convert image coord. to graph coord. (to match scaling)
                cv::Point2d txtimc = _UVtoXY(cv::Point2i(_center.x+txtSize.width/2, _center.y-txtSize.height/2));
                txtimc.y = -txtimc.y;
                //  Appends text
                Text(txt, (cv::Point2d(len, -iy)+txtimc), 2, 0.4);
            }
        }
        else
            //  Size of smaller division line. 220 chosen as a constant that
            //  produces lines of optimal length depending on the axis range
            len = (-_xlim[0]+_xlim[1])/220.0;

        LineCartesian(cv::Point2d(len,  iy), cv::Point2d(-len,  iy));
        LineCartesian(cv::Point2d(len, -iy), cv::Point2d(-len, -iy));

        tickCounter++;
    }
}

/**
 * Add new entry to the legend
 * @param index In the legend list
 * @param color Of the line connected to this entry
 * @param txt Description of entry in legend list(keep short)
 * @param fontFace Font type for writing 'txt'
 * @param scale Scale of font when writing 'txt'
 */
void OCVGraph::AddToLegend(uint8_t index, cv::Scalar color, std::string txt,
                            int fontFace, double scale)
{
    _legend.push_back(make_tuple(index, color, txt, fontFace, scale));
}

/**
 * Append legend with all its entry to a given position in graph
 * @param location Location of legend in current graph (one of legLoc enums)
 */
void OCVGraph::AppendLegend(legLoc location)
{
                      //Spacing between entries in list
    static const auto colOffset = cv::Point2i(0, 15),
                      //Length on line in the legend
                      lineLength = cv::Point2i(20, 0),
                      //Distance between line and text
                      linTxtDist = cv::Point2i(5, 0);
    //  Anchor point for legend entry
    cv::Point2i anchor;
    //  Length of the longest txt line in legend
    uint8_t legMaxLen;

    //  Sort _legend array based on first index and find max txt length
    cv::Size txtSize;
    int baseline=0;

    txtSize = cv::getTextSize(std::get<2>(_legend[0]), std::get<3>(_legend[0]),
                              std::get<4>(_legend[0]), 1, &baseline);

    legMaxLen = txtSize.width;
    //  Simple bubble sort to sort the array
    for (uint8_t i = 0; i < _legend.size(); i++)
        for (uint j = 1; j < _legend.size()-i; j++)
        {
            //  Note the longest length of the string(in pixels)
            txtSize = cv::getTextSize(std::get<2>(_legend[j]),
                    std::get<3>(_legend[j]), std::get<4>(_legend[j]), 1, &baseline);

            if (txtSize.width > legMaxLen)
                legMaxLen = txtSize.width;

            //  Swap elements
            if (std::get<0>(_legend[j-1]) > std::get<0>(_legend[j]))
            {
                legEntry tmp = _legend[j-1];
                _legend[j-1] = _legend[j];
                _legend[j] = tmp;
            }
        }

    //  Calculate anchor point based on where the legend needs to be
    switch(location)
    {
        case TopLeft:
            anchor = cv::Point2i(10, 10);
        break;

        case TopRight:
            anchor = cv::Point2i(_graphHolder.cols-10, 10);
            anchor = anchor - (lineLength+linTxtDist);
            anchor.x -= legMaxLen;
        break;

        case BottomLeft:
            anchor = cv::Point2i(10, _graphHolder.rows-10);
            anchor.y -= (colOffset.y+txtSize.height)*(_legend.size()-1)+txtSize.height;
        break;

        case BottomRight:
            anchor = cv::Point2i(_graphHolder.cols-10, _graphHolder.rows-10);
            anchor.y -= (colOffset.y+txtSize.height)*(_legend.size()-1)+txtSize.height;
            anchor = anchor - (lineLength+linTxtDist);
            anchor.x -= legMaxLen;
        break;
    }

    //	Add legend entries line-by-line
    for (auto X : _legend)
    {
        //  Calculate size of the text
        int baseline=0;
        cv::Size txtSize = cv::getTextSize(std::get<2>(X), std::get<3>(X),
                                           std::get<4>(X), 1, &baseline);

        //  Text halflength in Y-direction (used to center text)
        cv::Point2i txtOff = cv::Point2i(0, txtSize.height/2);

        //	Draw short line of given color
        cv::line(_graphHolder, anchor, anchor+lineLength, std::get<1>(X), 2);

        //	Write text corresponding to the line
        cv::putText(_graphHolder, std::get<2>(X), anchor+lineLength+linTxtDist+txtOff,
                    std::get<3>(X), std::get<4>(X), COLOR_BLACK);

        //  Move anchor point to the next line
        anchor = anchor + colOffset;
    }
}

///-----------------------------------------------------------------------------
///                      Miscellaneous functions                        [PUBLIC]
///-----------------------------------------------------------------------------

/**
 * Export current graph image into an image file at given location
 * @param path Path to image file
 */
void OCVGraph::Export(std::string path)
{
    cv::imwrite(path, _graphHolder);
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
 * Clear current graph and (if requested) reset its origin to center of image
 * @param resetCenter Whether or not to reset current center of graph to center
 * of underlying cv::Mat image file
 */
void OCVGraph::Clear(bool resetCenter)
{
    cv::Mat tmp (_graphHolder.rows, _graphHolder.cols, CV_8UC3, _background);

    tmp.copyTo(_graphHolder);

    if (resetCenter)
        _center = cv::Point2i(_graphHolder.cols/2, _graphHolder.rows/2);
}

///-----------------------------------------------------------------------------
///                      Operator definitions                           [PUBLIC]
///-----------------------------------------------------------------------------

OCVGraph& OCVGraph::operator=(OCVGraph& arg)
{
    _graphHolder = arg._graphHolder;
    _center = arg._center;
    _background = arg._background;
    _legend = arg._legend;
    memcpy(_xlim, arg._xlim, 2*sizeof(double));
    memcpy(_ylim, arg._ylim, 2*sizeof(double));

    return *this;
}

OCVGraph& OCVGraph::operator=(OCVGraph arg)
{
    _graphHolder = arg._graphHolder;
    _center = arg._center;
    _background = arg._background;
    _legend = arg._legend;
    memcpy(_xlim, arg._xlim, 2*sizeof(double));
    memcpy(_ylim, arg._ylim, 2*sizeof(double));

    return *this;
}

///-----------------------------------------------------------------------------
///                      Unit conversion functions                     [PRIVATE]
///-----------------------------------------------------------------------------

/**
 * @brief Convert U,V pixel coordinates into a corresponding X,Y graph coordinates
 * @param imageCoord Coordinates of pixel in image coordinates
 * @return cv::Point2i X,Y graph coordinates
 */
cv::Point2d OCVGraph::_UVtoXY(cv::Point2i imageCoord)
{
    cv::Point2d retVal;

    if (imageCoord.x > _center.x)
        retVal.x = _xlim[1]*((double)imageCoord.x-(double)_center.x)/((double)_graphHolder.cols-(double)_center.x);
    else if (imageCoord.x <= _center.x)
        retVal.x = -_xlim[0]*((double)imageCoord.x-(double)_center.x)/((double)_center.x);

    if (imageCoord.y > _center.y)
        retVal.y = _ylim[0]*((double)imageCoord.y-(double)_center.y)/((double)_graphHolder.rows-(double)_center.y);
    else if (imageCoord.y <= _center.y)
        retVal.y = -_ylim[1]*((double)imageCoord.y-(double)_center.y)/((double)_center.y);

    return retVal;
}

/**
 * @brief Convert graph coordinates to image coordinates
 * @param graphCoord
 * @return Image coordinates corresponding to graph coordinates
 */
cv::Point2i OCVGraph::_XYtoUV(cv::Point2d graphCoord)
{
    cv::Point2i retVal;

    if (graphCoord.x > 0) //  u has to be > center.u
        retVal.x = _center.x + ((double)(_graphHolder.cols-_center.x))*graphCoord.x/_xlim[1];
    else if (graphCoord.x <= 0)
        retVal.x = _center.x - ((double)(_center.x))*graphCoord.x/_xlim[0];

    if (graphCoord.y <= 0)
        retVal.y = _center.y + ((double)(_graphHolder.rows-_center.y))*graphCoord.y/_ylim[0];
    else if (graphCoord.y > 0)
        retVal.y = _center.y - ((double)(_center.y))*graphCoord.y/_ylim[1];

    return retVal;
}
