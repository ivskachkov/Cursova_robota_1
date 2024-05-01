#include "matrix_eigen_vv.hpp"
#include "matrix.hpp"
#include <memory>

class RotationMatrixEigenVV : public IMatrixEigenVV
{
    struct MaxElementInfo
    {
        double value;
        int row, col;
    };
public:
    RotationMatrixEigenVV();
    Result calculate(const Mat & matrix) override;

private:
    static Matrix gaussMeethod(const Matrix & m, int count = -1);

private:
    Matrix m;
    Matrix init;
    double calculateF(const MaxElementInfo& a) const;
    double calculateNDE() const;
    MaxElementInfo getMax() const;
    Matrix getU(const MaxElementInfo& a) const;
    Matrix applyL(double value);
};