#include <iostream>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <Instrumentor.h>

#include "Kernel.hpp"
#include "LikelihoodModel.hpp"
#include "LineSegmentation.hpp"

using namespace cv;

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: MCMLSD-CPP image" << std::endl;
        std::cout << "image: image used for detection" << std::endl;
        std::cout << "Exiting now..." << std::endl;

        return EXIT_FAILURE;
    }

    PROFILE_BEGIN_SESSION("Profile", "Profile.json");
    PROFILE_FUNCTION();

    // NOTE: I took the liberty to already load the likelihood model
    //       before it is done in the original MATLAB implementation,
    //       as I/O *can* be slow and reduce the performance of the algorithm.
    //       Loading the model shouldn't be inside the algorithm while it is
    //       busy computing stuff.
    LikelihoodModel model = LoadModel ("res/likelihood_model/");

    cv::Mat image = cv::imread (argv[1]);
    if (image.empty())
    {
        std::cerr << "Couldn't open the " << argv[1] << " image." << std::endl;

        return EXIT_FAILURE;
    }

    cv::Mat resizedImage;

    cv::resize (image, resizedImage, cv::Size(), 0.25, 0.25);

    KernelInfo kernels = KernelInitialization (resizedImage.rows,
                                               resizedImage.cols);

    LineSegmentation_HighRes (resizedImage, kernels, model);

    PROFILE_END_SESSION();

    return EXIT_SUCCESS;
}
