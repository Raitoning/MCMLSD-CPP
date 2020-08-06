#include "Kernel.hpp"

#include <cmath>
#include <vector>
#include <Eigen/Dense>
#include <Instrumentor.h>

#include "Math.hpp"



struct KernelStruct
{
    Eigen::MatrixXd kernel;
    int index;
};


KernelInfo KernelInitialization (int width, int height)
{
    PROFILE_FUNCTION();

    // 800 is the diagonal length of a 640x480 image.
    double scaleFactor = sqrt ( width * width + height * height ) / 800.0;

    double maxR = floor (400.0 * scaleFactor);

    double sigmaX = 0.4;
    double rRes = 0.2;
    double thRes = 0.002;

    double sigmaTheta = 5.4 * ( M_PI / 180.0 );

    return PrecomputeKernelSparseRes2 (maxR, sigmaX, sigmaTheta, rRes, thRes);
}


KernelInfo PrecomputeKernelSparseRes2 (double rMax, double sigmaX,
                                       double sigmaTh, double rRes,
                                       double thRes)
{
    PROFILE_FUNCTION();

    KernelInfo kernelInfo;

    // Preallocate enough memory to not have to reallocate/move the vectors.
    kernelInfo.kernels.reserve (rMax);
    kernelInfo.kernelsFlip.reserve (rMax);
    kernelInfo.kernelsParams.reserve (rMax);

    for (double e = -rMax; e < rMax; e++)
    {
        KernelStruct kernelStruct = ComputeKernel (e, rMax, sigmaX, sigmaTh,
                                                   rRes, thRes);

        kernelInfo.kernels.push_back (kernelStruct.kernel);
        kernelInfo.kernelsFlip.push_back (kernelStruct.kernel);
        kernelInfo.kernelsParams.push_back (kernelStruct.kernel.maxCoeff());
    }

    return kernelInfo;
}


KernelStruct ComputeKernel (double e, double rMax, double sigmaX, double sigmaTh,
                            double rRes, double thRes)
{
    PROFILE_FUNCTION();

    double rTh = e;

    Eigen::Matrix2d matrix;
    matrix(0, 0) = sigmaX * sigmaX + (rTh * rTh) * (sigmaTh * sigmaTh);
    matrix(0, 1) = rTh * (sigmaTh * sigmaTh);
    matrix(1, 0) = rTh * (sigmaTh * sigmaTh);
    matrix(1, 1) = sigmaTh * sigmaTh;

    Eigen::Matrix2d matrixInverse = matrix.inverse();
    double matrixDeterminant = matrix.determinant();

    double n = 1.0 / (2.0 * M_PI * sqrt (matrixDeterminant));

    double low = -Round2Frac (3.0 * sqrt (matrix (0, 0)), rRes);
    double high = Round2Frac (3.0 * sqrt (matrix (0, 0)), rRes);
    int size = (high - low) / rRes + 1;

    Eigen::VectorXd r(size);

    for (int i = 0; i < size; i++)
    {
        r(i) = low + (rRes * i);
    }


    low = -Round2Frac (3 * sigmaTh, thRes);
    high = Round2Frac (3 * sigmaTh, thRes);
    size = (high - low) / thRes + 1;

    Eigen::VectorXd th(size);

    for (int i = 0; i < size; i++)
    {
        th(i) = low + (thRes * i);
    }

    double c = matrixInverse (0, 0);
    double d = matrixInverse (0, 1);
    double g = matrixInverse (1, 0);
    double f = matrixInverse (1, 1);

    Eigen::MatrixXd a;
    Eigen::MatrixXd b;

    MeshGrid (r, th, a, b);

    Eigen::MatrixXd values = n * (-0.5 * (((a * c + b * g).array() * a.array()) + ((a * d + b * f).array() * b.array()))).exp();

    // NOTE: [r, c] = find(vals > 0.05*max(vals(:)))
    int cols = values.cols();
    int rows = values.rows();

    std::vector< std::pair<int, int> > indices;

    double max = values.maxCoeff();

    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            if (values(row, col) > (max * 0.05))
            {
                indices.emplace_back (row, col);
            }
        }
    }

    int minC = __INT_MAX__;
    int minR = __INT_MAX__;

    for (unsigned int i = 0; i < indices.size(); i++)
    {
        if (indices[i].first < minR)
        {
            minR = indices[i].first;
        }

        if (indices[i].second < minC)
        {
            minC = indices[i].second;
        }
    }

    std::vector<int> linearIndices;
    linearIndices.reserve (indices.size());

    for (unsigned int i = 0; i < indices.size(); i++)
    {
        linearIndices.emplace_back (indices[i].second * rows + indices[i].first);
    }

    KernelStruct kernelStruct;
    kernelStruct.kernel = Eigen::MatrixXd(linearIndices.size(), 3);

    for (unsigned int i = 0; i < linearIndices.size(); i++)
    {
        kernelStruct.kernel(i, 0) = indices[i].first - minC;
        kernelStruct.kernel(i, 1) = indices[i].second - minC;
        kernelStruct.kernel(i, 2) = values(linearIndices[i]);
    }

    kernelStruct.index = e + rMax + 1;

    return kernelStruct;
}
