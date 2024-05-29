#pragma once

#include <vector>
#include <cmath>
#include <functional>
#include <cstdint>
#include <string>

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
        uint64_t time;
        std::string formula;
        int iterations;
        int operations;
    };
    virtual ~IMatrixEigenVV() = default;
    virtual Result calculate (const Mat & matrix) = 0;
};