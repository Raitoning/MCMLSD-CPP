#include <cmath>
#include <Instrumentor.h>

#include "Math.hpp"


double Round2Frac (double value, double fraction)
{
    double res = value / fraction;
    res = round (res);
    return res * fraction;
}


// NOTE: Straight port of MeshGrid from MATLAB to C++
// There might be a better solution.
void MeshGrid (const Eigen::VectorXd& a, const Eigen::VectorXd& b,
               Eigen::MatrixXd& matrixA, Eigen::MatrixXd& matrixB)
{

    PROFILE_FUNCTION();

    matrixA = Eigen::MatrixXd (b.size(), a.size());
    for (int y = 0; y < b.size(); y++)
    {
        for (int x = 0; x < a.size(); x++)
        {
            matrixA(y, x) = a(x);
        }
    }

    matrixB = Eigen::MatrixXd (b.size(), a.size());
    for (int y = 0; y < b.size(); y++)
    {
        for (int x = 0; x < a.size(); x++)
        {
            matrixB(y, x) = b(y);
        }
    }
}
