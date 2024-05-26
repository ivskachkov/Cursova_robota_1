#include "rotation_matrix_eigen_vv.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>
#include "utils.hpp"

Matrix RotationMatrixEigenVV::gaussMeethod(const Matrix & m, int count){
    Matrix result = m;
    count = count == -1 ? m.rows() : count;
    for ( int k = 0; k < count; ++k ){
        if ( result[k][k] == 0 )
            throw std::runtime_error("The element a[n][n] must not be equal to zero");
        result[k] = result[k] / result[k][k];
        for ( int i = k+1; i < m.rows(); ++i ){
            result[i] = result[i] - result[k] * result[i][k];
        }
    }
    for ( int k = count-1; k > 0; --k ){
        for ( int i = k-1; i >= 0; --i ){
            result[i] = result[i] - result[k] * result[i][k];
        }
    }
    return result;
}

RotationMatrixEigenVV::RotationMatrixEigenVV()
{
}

RotationMatrixEigenVV::MaxElementInfo RotationMatrixEigenVV::getMax() const
{
    MaxElementInfo a;  
    a.value = 0;
    a.row = 0;
    a.col = 1;
    for(int i = 0; i < m.rows(); i++){
        for(int j = 0; j < m.cols(); j++){
            if(i != j && fabs(a.value) < fabs(m[i][j])){
                a.value = m[i][j];
                a.row = i;
                a.col = j;
            }
        }
    }
    return a;
}

double RotationMatrixEigenVV::calculateF(const MaxElementInfo & a) const
{
    //using atan2 instead of atan to get the correct sign
    //double result = 1.0/2.0 *( atan2((a.value * 2.0), (m[a.row][a.row] - m[a.col][a.col])) );
    double result = 1.0/2.0 *( atan((a.value * 2.0) / (m[a.row][a.row] - m[a.col][a.col])) );
    return result;
}

Matrix RotationMatrixEigenVV::getU(const MaxElementInfo& a) const
{
    Matrix result(m.rows(), m.cols());
    double f = calculateF(a);
    result[a.row][a.row] = cos(f);
    result[a.col][a.col] = cos(f);
    result[a.row][a.col] = -sin(f);
    result[a.col][a.row] = sin(f);
    return result;
}

double RotationMatrixEigenVV::calculateNDE() const
{
    double result = 0;
    for(int i = 0; i < m.rows(); i++){
        for(int j = 0; j < m.cols(); j++){
            if(i == j){
                continue;
            }
            result += pow(m[i][j], 2.0);
        }
    }
    return result;
}

Matrix RotationMatrixEigenVV::applyL(double value)
{
    Matrix result(init.rows(), init.cols());
    for(int i = 0; i < init.rows(); i++){
        for(int j = 0; j < init.cols(); j++){
            if(i == j){
                result[i][j] = init[i][j] - value;
            } else {
                result[i][j] = init[i][j];
            }
        }
    }
    return result;
}

IMatrixEigenVV::Result RotationMatrixEigenVV::calculate(const Mat & matrix)
{
    std::vector<Vector> arg;
    std::transform(matrix.begin(), matrix.end(), std::back_inserter(arg), [](const Vec & v) { return Vector(v); });
    m = Matrix(arg);
    init = m;
    uint64_t tStart = currentTimestamp(), tEnd = 0;
    double E = 1E-4;
    int i = 10000;
    Matrix uVector(m.rows(), m.cols());
    while(E < calculateNDE() && i >= 0){
        MaxElementInfo a = getMax();
        Matrix U = getU(a);
        Matrix tU = U.transpose();
        m = tU * m * U;
        uVector = uVector * U;
        i--;
    }

    Result res;
    res.data.resize(m.rows());
    auto values = m.diagonal();
    for ( int i = 0; i < res.data.size(); ++i ){
        res.data[i].eigenValue = values[i];
        auto v = uVector.col(i);
        v = v / v[m.rows()-1];
        if ( v.isValid() )
            res.data[i].eigenVector = v;
    }
    tEnd = currentTimestamp();
    res.time = tEnd - tStart;
    std::sort(res.data.begin(), res.data.end(), [](const Eigen & a, const Eigen & b) { return a.eigenValue < b.eigenValue; });
    auto e = std::remove_if(res.data.begin(), res.data.end(), [res](const Eigen & e) { return fabs(e.eigenValue) < 1E-6 || e.eigenVector.empty(); });
    res.data.erase(e, res.data.end());
    return res;
}