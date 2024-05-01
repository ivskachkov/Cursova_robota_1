#pragma once

#include "matrix_eigen_vv.hpp"
#include "matrix.hpp"
#include "extremum_finder.hpp"
#include <memory>

class DanylevskyMatrixEigenVV : public IMatrixEigenVV
{
public:
    DanylevskyMatrixEigenVV(std::unique_ptr<IExtremumFinder> finder);
    Result calculate(const Mat & matrix) override;

private:
    static double func(double x, const std::vector<double> & v);
    Matrix makeM(const Matrix & m, int n) const;
    Matrix makeMR(const Matrix & m, int n) const;
    std::unique_ptr<IExtremumFinder> finder;
    Matrix m;
    Matrix s;
};