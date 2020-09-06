#include "LineSegmentation.hpp"

#include <Instrumentor.h>

LineStruct LineSegmentation_HighRes(cv::Mat &img, KernelInfo &kernels,
                                    LikelihoodModel &model)
{
    PROFILE_FUNCTION();

    // use 640x480 image as a reference. the diagonal size of this image is 800
    // if image size 640x480 scale factor = 1
    // if image size 1280x960 scale factor = 2 ... etc.
    // the lines variable contains the detected line segmentations it arranged as
    // [x1 y1 x2 y2 probability]
    // The fullLines are the detected lines. It is arranged as [rho theta probability]

    // principle point
    std::pair<double, double> principlePoint = {307.551305282635,
                                                251.454244960136};

    // threshold for the line detection
    double sigBound = 3;

    // the theshold for the rho
    double rRes = 0.2;

    // the threshold for theta
    double thRes = 0.002;

    int width = img.cols;
    int height = img.rows;

    // 800 is the diagnal length of 640x480 image
    double scaleFactor = sqrt (width * width + height * height) / 800.0;

    // the kernel of the algorithm is calibrated on 640x480 image
    // rescale the principle point
    principlePoint.first = principlePoint.first * width / 640.0;
    principlePoint.second = principlePoint.second * height / 480.0;

    return RunLineSegmentAlgorithm (kernels, sigBound, rRes, thRes, img,
                                    scaleFactor, principlePoint, model);
}


LineStruct RunLineSegmentAlgorithm (KernelInfo &kernels, double sigBound,
                                    double rRes, double thRes, cv::Mat &img,
                                    double scaleFactor,
                                    std::pair<double, double> principlePoint,
                                    LikelihoodModel &model)
{
    PROFILE_FUNCTION();

    double frac = 0.05;

    DetermineHoughLinesKernelVoteRemove (img, principlePoint, kernels, 0, rRes,
                                         thRes, sigBound, frac, scaleFactor);
}


LineStruct DetermineHoughLinesKernelVoteRemove (cv::Mat &img,
                                                std::pair<double, double> pp,
                                                KernelInfo &kernels,
                                                int num, double rRes,
                                                double thRes, double sigBound,
                                                double frac,
                                                double scaleFactor)
{

}
