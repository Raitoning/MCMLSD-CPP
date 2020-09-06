#include "MainEdge.hpp"


OutputData MainEdge (cv::Mat img, double scale, double noise, double edgew,
                     double conss, double congrd, double subpixelflag)
{
    // If the image isn't grayscale, convert it to grayscale
    if (img.channels() != 1)
    {
        cv::cvtColor (img, img, CV_BGR2GRAY);
    }

    img.convertTo (img, CV_64F);
}
