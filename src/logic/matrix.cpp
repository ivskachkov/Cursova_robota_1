#include "matrix.hpp"

std::ostream& operator << (std::ostream& os, const Matrix& m) {
    for ( int i = 0; i < m.rows(); ++i ){
        os << m[i] << std::endl;
    }
    return os;
}

Matrix::Matrix(int rows, int cols) : data(rows, Vector(cols)) {
    if ( rows < 0 || cols < 0 )
        throw std::runtime_error("The number of rows and columns must be greater than or equal to zero");
    if ( rows == 0 && cols != 0 )
        throw std::runtime_error("The number of rows must be greater than zero");
    if ( rows != 0 && cols == 0 )
        throw std::runtime_error("The number of columns must be greater than zero");
    if ( rows == cols ){
        for ( int i = 0; i < rows; ++i ){
            data[i][i] = 1;
        }
    }
}
Matrix::Matrix(int sizeSquareM, std::initializer_list<double> list) : data(sizeSquareM, Vector(sizeSquareM)){
    if ( list.size() != sizeSquareM * sizeSquareM )
        throw std::runtime_error("The number of elements in the list must be equal to the square of the size of the matrix");
    sizeSquareM *= sizeSquareM;
    int i = 0;
    for ( auto it = list.begin(); it != list.end(); ++it ){
        data[i / sizeSquareM][i % sizeSquareM] = *it;
        i++;
    }
}
Matrix::Matrix(const std::vector<Vector> & m) : data(m)
{

}

bool Matrix::operator== (const Matrix & m) const {
    if ( data.size() != m.data.size() )
        return false;
    for ( int i = 0; i < data.size(); ++i ){
        if ( data[i].size() != m.data[i].size() )
            return false;
        if ( data[i] != m.data[i] )
            return false;
    }
    return true;
}
bool Matrix::operator!= (const Matrix & m) const {
    return !(*this == m);
}
Matrix Matrix::operator+ (const Matrix & m) const {
    if ( m.data.empty() || data.size() != m.data[0].size() )
        throw std::runtime_error("Matrices must have the same number of rows");
    std::vector<Vector> result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result[i] = data[i] + m.data[i];
    }
    return Matrix(result);
}
Matrix Matrix::operator- (const Matrix & m) const {
    if ( m.data.empty() || data.size() != m.data[0].size() )
        throw std::runtime_error("Matrices must have the same number of rows");
    std::vector<Vector> result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result[i] = data[i] - m.data[i];
    }
    return Matrix(result);
}
Matrix Matrix::operator* (const Matrix & m) const {
    if ( m.data.empty() || data[0].size() != m.data.size() ){
        std::cout << data[0].size() << " " << m.data.size() << std::endl;
        throw std::runtime_error("Number of columns in the first matrix must be equal to the number of rows in the second matrix");
    }
    std::vector<Vector> result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result[i] = Vector(m.data.size());
        for ( int j = 0; j < m.data.size(); ++j ){
            for ( int k = 0; k < data[i].size(); ++k ){
                result[i][j] += data[i][k] * m.data[k][j];
            }
        }
    }
    return Matrix(result);
}

Vector Matrix::operator* (const Vector & v) const {
    Matrix m(v.size(), 1);
    for ( int i = 0; i < v.size(); ++i ){
        m[i][0] = v[i];
    }
    Matrix product = *this * m;
    Vector result(product.rows());
    for ( int i = 0; i < product.rows(); ++i ){
        result[i] = product[i][0];
    }
    return result;
}

Matrix Matrix::operator* (double scalar) const {
    std::vector<Vector> result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result[i] = data[i] * scalar;
    }
    return Matrix(result);
}
Matrix Matrix::operator/ (double scalar) const {
    std::vector<Vector> result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result[i] = data[i] / scalar;
    }
    return Matrix(result);
}
Matrix Matrix::operator + (double scalar) const {
    std::vector<Vector> result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result[i] = data[i] + scalar;
    }
    return Matrix(result);
}
Matrix Matrix::operator - (double scalar) const {
    std::vector<Vector> result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result[i] = data[i] - scalar;
    }
    return Matrix(result);
}
Vector & Matrix::operator[] (int index) {
    return data[index];
}
const Vector & Matrix::operator[] (int index) const {
    return data[index];
}
int Matrix::rows() const {
    return data.size();
}
int Matrix::cols() const {
    return data[0].size();
}
Matrix Matrix::transpose() const {
    Matrix result(cols(), rows());
    for ( int i = 0; i < data[0].size(); ++i ){
        for ( int j = 0; j < data.size(); ++j ){
            result[i][j] = data[j][i];
        }
    }
    return result;
}

Vector Matrix::diagonal() const {
    if ( data.size() != data[0].size() )
        throw std::runtime_error("The matrix must be square");
    Vector result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result[i] = data[i][i];
    }
    return result;
}

//-a[n][1..] / a[n][n-1]
