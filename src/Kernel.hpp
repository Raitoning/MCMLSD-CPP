#ifndef _KERNEL_H_
#define _KERNEL_H_


#include <vector>
#include <Eigen/Dense>


struct KernelInfo
{
    std::vector<Eigen::MatrixXd> kernels;
    std::vector<Eigen::MatrixXd> kernelsFlip;
    std::vector<double> kernelsParams;
};


struct KernelStruct;


KernelInfo KernelInitialization (int width, int height);


KernelInfo PrecomputeKernelSparseRes2 (double rMax, double sigmaX,
                                       double sigmaTh, double rRes,
                                       double thRes);


KernelStruct ComputeKernel (double e, double rMax, double sigmaX, double sigmaTh,
                            double rRes, double thRes);


#endif
