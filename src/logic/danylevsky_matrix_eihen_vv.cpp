#include "danylevsky_matrix_eigen_vv.hpp"
#include <cmath>

DanylevskyMatrixEigenVV::DanylevskyMatrixEigenVV(std::unique_ptr<IExtremumFinder> finder) : finder(std::move(finder))
{
}

DanylevskyMatrixEigenVV::Result DanylevskyMatrixEigenVV::calculate(const Mat & matrix)
{
    std::vector<Vector> arg;
    std::transform(matrix.begin(), matrix.end(), std::back_inserter(arg), [](const Vec & v) { return Vector(v); });
    m = Matrix(arg);
    s = Matrix(m.rows(), m.cols());
    for ( int i = m.rows()-1; i > 0; --i ){
        Matrix ma = makeM(m, i);
        Matrix mr = makeMR(m, i);
        m = mr * m * ma;
        s = s * ma;
    }
    std::vector<Matrix> vecS(m.rows(), Matrix(m.cols(), 1));
    Result res;
    res.data.resize(m.rows());
    res.coefficients = m[0];
    res.func = [v = m[0]](double x)->double { return func(x, v); };
    auto values = finder->findExtremums(res.func);
    for ( int i = 0; i < values.size(); ++i ){
        res.data[i].eigenValue = values[i];
        double v = values[i];
        for ( int j = 0; j < m.rows(); ++j ){
            vecS[i][j][0] = pow(v, m.rows()-j-1);
        }
        vecS[i] = s * vecS[i];
        res.data[i].eigenVector = vecS[i].transpose()[0];
    }
    
    auto e = std::remove_if(res.data.begin(), res.data.end(), [res](const Eigen & e) { return fabs(e.eigenValue) < 1E-4; });
    res.data.erase(e, res.data.end());

    int lastID = res.data.size()-1;
    res.funcMaxX = fabs(res.data[0].eigenValue) > fabs(res.data[lastID].eigenValue) ? res.data[0].eigenValue : res.data[lastID].eigenValue;
    //std::transform(vecS.begin(), vecS.end(), std::back_inserter(res.eigenVectors), [](const Matrix & v) { return v.transpose()[0]; });
    return res;
}

double DanylevskyMatrixEigenVV::func(double x, const std::vector<double> & v)
{
    double res = pow(x, v.size());
    auto iter = v.rbegin();
    for (int i = 0; i < v.size(); i++, iter++)
    {
        res -= *iter * pow(x, i);
    }
    return res;
}

Matrix DanylevskyMatrixEigenVV::makeM(const Matrix & m, int d) const
{
    Matrix result = makeMR(m, d);
    result[d-1][d-1] = -1;
    if ( m[d][d-1] == 0 )
        throw std::runtime_error("The element a[n][n-1] must not be equal to zero");
    else
        result[d-1] = result[d-1] / -m[d][d-1];
    return result;
}

Matrix DanylevskyMatrixEigenVV::makeMR(const Matrix & m, int d) const
{
    if ( d <= 0 || d >= m.rows() )
        throw std::runtime_error("The number of the row must be greater than zero and less than the number of rows in the matrix");
    Matrix result(m.rows(), m.cols());
    result[d-1] = m[d];
    return result;
}
