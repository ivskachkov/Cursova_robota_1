#pragma once

#include <vector>

class IMatrixEigenVV
{
public:
    using Mat = std::vector<std::vector<double>>;
    using Vec = std::vector<double>;
    struct Result
    {
        std::vector<double> eigenValues;
        std::vector<Vec> eigenVectors;
    };
    virtual ~IMatrixEigenVV() = default;
    virtual Result calculate (const Mat & matrix) = 0;
};