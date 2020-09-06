#ifndef _H_MAIN_EDGE_H_
#define _H_MAIN_EDGE_H_


#include <opencv2/opencv.hpp>


struct OutputData
{
    /* Dummy structure for compiling */
};


OutputData MainEdge (cv::Mat img, double scale, double noise, double edgew,
                     double conss, double congrd, double subpixelflag);

#endif
