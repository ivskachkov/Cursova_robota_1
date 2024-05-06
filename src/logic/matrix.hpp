#pragma once

#include "vec.hpp"

class Matrix
{
public:
    Matrix(int rows = 0, int cols = 0);
    Matrix(int sizeSquareM, std::initializer_list<double> list);
    Matrix(const std::vector<Vector> & m);
    bool operator== (const Matrix & m) const;
    bool operator!= (const Matrix & m) const;
    Matrix operator+ (const Matrix & m) const;
    Matrix operator- (const Matrix & m) const;
    Matrix operator* (const Matrix & m) const;
    Matrix operator* (double scalar) const;
    Vector operator* (const Vector & v) const;
    Matrix operator/ (double scalar) const;
    Matrix operator + (double scalar) const;
    Matrix operator - (double scalar) const;
    Vector & operator[] (int index);
    const Vector & operator[] (int index) const;
    int rows() const;
    int cols() const;
    Matrix transpose() const;
    Vector diagonal() const;
    Vector col(int index) const;

private:
    std::vector<Vector> data;
};

std::ostream& operator << (std::ostream& os, const Matrix& m);

