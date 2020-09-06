#ifndef _LINE_SEGMENTATION_H_
#define _LINE_SEGMENTATION_H_

#include <opencv2/opencv.hpp>

#include "Kernel.hpp"
#include "LikelihoodModel.hpp"


// Dummy structure, only for compiling
struct LineStruct
{
    int lines;
    int fullLines;
};


LineStruct LineSegmentation_HighRes(cv::Mat &img, KernelInfo &kernels,
                                    LikelihoodModel &model);


LineStruct RunLineSegmentAlgorithm (KernelInfo &kernels, double sigBound,
                                    double rRes, double thRes, cv::Mat &img,
                                    double scaleFactor,
                                    std::pair<double, double> principlePoint,
                                    LikelihoodModel &model);

LineStruct DetermineHoughLinesKernelVoteRemove (cv::Mat &img,
                                                std::pair<double, double> pp,
                                                KernelInfo &kernels,
                                                int num, double rRes,
                                                double thRes, double sigBound,
                                                double frac,
                                                double scaleFactor);


#endif
