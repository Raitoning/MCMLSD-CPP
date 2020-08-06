#include <iostream>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <Instrumentor.h>

#include "Kernel.hpp"
#include "Math.hpp"

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

    cv::Mat image = cv::imread (argv[1]);
    if (image.empty())
    {
        std::cerr << "Couldn't open the " << argv[1] << " image." << std::endl;

        return EXIT_FAILURE;
    }

    cv::Mat resizedImage;

    cv::resize (image, resizedImage, cv::Size(), 0.25, 0.25);

    KernelInitialization (resizedImage.rows, resizedImage.cols);

    PROFILE_END_SESSION();

    return EXIT_SUCCESS;
}
