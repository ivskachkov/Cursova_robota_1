#include "danylevsky_matrix_eigen_vv.hpp"
#include <cmath>
#include "utils.hpp"

DanylevskyMatrixEigenVV::DanylevskyMatrixEigenVV(std::unique_ptr<IExtremumFinder> finder) : finder(std::move(finder))
{
}

DanylevskyMatrixEigenVV::Result DanylevskyMatrixEigenVV::calculate(const Mat & matrix)
{
    std::vector<Vector> arg;
    std::transform(matrix.begin(), matrix.end(), std::back_inserter(arg), [](const Vec & v) { return Vector(v); });
    uint64_t tStart = currentTimestamp(), tEnd = 0;
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
    tEnd = currentTimestamp();
    res.time = tEnd - tStart;
    auto e = std::remove_if(res.data.begin(), res.data.end(), [res](const Eigen & e) { return fabs(e.eigenValue) < 1E-4; });
    res.data.erase(e, res.data.end());

    int lastID = res.data.size()-1;
    res.funcMaxX = fabs(res.data[0].eigenValue) > fabs(res.data[lastID].eigenValue) ? res.data[0].eigenValue : res.data[lastID].eigenValue;
    res.formula = formula(res);
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

static std::string doubleToString(double value)
{
    std::string res = std::to_string(value);
    if ( res.find('.') != std::string::npos )
    {
        while ( res.back() == '0' )
            res.pop_back();
        if ( res.back() == '.' )
            res.pop_back();
    }
    if ( value > 0 )
        res = "+" + res;
    return res;
}

std::string DanylevskyMatrixEigenVV::formula(const Result &result)
{
    std::string res = "f(x) = x^" + std::to_string(result.coefficients.size()) + " ";
    auto iter = result.coefficients.begin();
    for (int i = result.coefficients.size() - 1; i >= 0; i--, iter++)
    {
        if ( i == 0 )
            res += doubleToString(*iter * -1);
        else if ( i == 1 )
            res += doubleToString(*iter * -1) + "*x ";
        else
            res += doubleToString(*iter * -1) + "*x^" + std::to_string(i) + " ";
    }
    return res;
}