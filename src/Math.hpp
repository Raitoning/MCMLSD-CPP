#ifndef _MATH_H_
#define _MATH_H_

#include <Eigen/Dense>


double Round2Frac (double value, double fraction);


void MeshGrid (const Eigen::VectorXd& a, const Eigen::VectorXd& b,
               Eigen::MatrixXd& matrixA, Eigen::MatrixXd& matrixB);


#endif
