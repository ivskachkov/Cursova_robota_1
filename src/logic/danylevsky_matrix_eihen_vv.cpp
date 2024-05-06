#include "danylevsky_matrix_eigen_vv.hpp"

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
    res.resize(m.rows());
    auto values = finder->findExtremums([v = m[0]](double x)->double { return func(x, v); });
    for ( int i = 0; i < values.size(); ++i ){
        res[i].eigenValue = values[i];
        double v = values[i];
        for ( int j = 0; j < m.rows(); ++j ){
            vecS[i][j][0] = pow(v, m.rows()-j-1);
        }
        vecS[i] = s * vecS[i];
        res[i].eigenVector = vecS[i].transpose()[0];
    }
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
