#pragma once

#include <vector>

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
    using Result = std::vector<Eigen>;
    virtual ~IMatrixEigenVV() = default;
    virtual Result calculate (const Mat & matrix) = 0;
};