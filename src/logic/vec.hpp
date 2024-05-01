#pragma once

#include <vector>
#include <iostream>

class Vector
{
    static double E;
public:
    static double round_up(double value, int dec);
    Vector(int size = 0);
    Vector(const std::vector<double> & v);
    bool operator== (const Vector & v) const;
    bool operator!= (const Vector & v) const;
    Vector operator+ (const Vector & v) const;
    Vector operator- (const Vector & v) const;
    double operator* (const Vector & v) const;
    Vector operator* (double scalar) const;
    Vector operator/ (double scalar) const;
    Vector operator + (double scalar) const;
    Vector operator - (double scalar) const;
    double & operator[] (int index);
    double operator[] (int index) const;
    int size() const;
    operator std::vector<double> () const;

private:
    std::vector<double> data;
};

std::ostream& operator << (std::ostream& os, const Vector& v);