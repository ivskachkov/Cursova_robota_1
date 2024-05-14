#include "eigen_finder.h"

#include "danylevsky_matrix_eigen_vv.hpp"
#include "iteration_extremum_finder.hpp"
#include "rotation_matrix_eigen_vv.hpp"

std::unique_ptr<IMatrixEigenVV> createDanylevskyMatrixEigenVV()
{
    return std::make_unique<DanylevskyMatrixEigenVV>(std::make_unique<IterationExtremumFinder>(-1000, 1000, 0.001, 0.01));
}

std::unique_ptr<IMatrixEigenVV> createRotationMatrixEigenVV()
{
    return std::make_unique<RotationMatrixEigenVV>();
}