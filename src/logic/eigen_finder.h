#pragma once

#include "matrix_eigen_vv.hpp"
#include <memory>

std::unique_ptr<IMatrixEigenVV> createDanylevskyMatrixEigenVV();
std::unique_ptr<IMatrixEigenVV> createRotationMatrixEigenVV();