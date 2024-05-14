#pragma once

#include <vector>
#include <cmath>
#include <functional>

class IMatrixEigenVV
{
public:
    using Mat = std::vector<std::vector<double>>;
    using Vec = std::vector<double>;
    struct Eigen
    {
        double eigenValue;
        Vec eigenVector;
    };
    struct Result{
        std::vector<Eigen> data;
        std::function<double(double)> func;
        double funcMaxX;
        std::vector<double> coefficients;
    };
    virtual ~IMatrixEigenVV() = default;
    virtual Result calculate (const Mat & matrix) = 0;
};