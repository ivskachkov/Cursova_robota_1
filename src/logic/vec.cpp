#include "vec.hpp"
#include <cmath>
#include <stdexcept>

std::ostream& operator << (std::ostream& os, const Vector& v) {
    for ( int i = 0; i < v.size(); ++i ){
        os << Vector::round_up(v[i], 3) << "\t";
        //os << v[i] << "\t";
    }
    return os;
}

double Vector::E = 1e-6;

double Vector::round_up(double value, int dec){
    double factor = pow(10, dec);
    return ceil(value * factor) / factor;
}

Vector::Vector(int size) : data(size) 
{    
}

Vector::Vector(const std::vector<double> & v) : data(v) 
{

}

bool Vector::operator== (const Vector & v) const {
    if ( data.size() != v.data.size() )
        return false;
    for ( int i = 0; i < data.size(); ++i ){
        if ( fabs(data[i] - v.data[i]) > E ){
            //std::cout << data[i] << " " << v.data[i] << std::endl;
            return false;
        }
    }
    return true;
}
bool Vector::operator!= (const Vector & v) const {
    return !(*this == v);
}
Vector Vector::operator+ (const Vector & v) const {
    if ( data.size() != v.data.size() )
        throw std::runtime_error("Vectors must have the same size");
    Vector result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result.data[i] = data[i] + v.data[i];
    }
    return result;
}
Vector Vector::operator- (const Vector & v) const {
    if ( data.size() != v.data.size() )
        throw std::runtime_error("Vectors must have the same size");
    Vector result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result.data[i] = data[i] - v.data[i];
    }
    return result;
}
double Vector::operator* (const Vector & v) const {
    if ( data.size() != v.data.size() )
        throw std::runtime_error("Vectors must have the same size");
    double result = 0;
    for ( int i = 0; i < data.size(); ++i ){
        result += data[i] * v.data[i];
    }
    return result;
}
Vector Vector::operator* (double scalar) const {
    Vector result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result.data[i] = data[i] * scalar;
    }
    return result;
}
Vector Vector::operator/ (double scalar) const {
    Vector result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result.data[i] = data[i] / scalar;
    }
    return result;
}
Vector Vector::operator + (double scalar) const {
    Vector result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result.data[i] = data[i] + scalar;
    }
    return result;
}
Vector Vector::operator - (double scalar) const {
    Vector result(data.size());
    for ( int i = 0; i < data.size(); ++i ){
        result.data[i] = data[i] - scalar;
    }
    return result;
}
double & Vector::operator[] (int index) {
    return data[index];
}
double Vector::operator[] (int index) const {
    return data[index];
}
int Vector::size() const {
    return data.size();
}

Vector::operator std::vector<double> () const {
    return data;
}

bool Vector::isValid() const {
    for ( int i = 0; i < data.size(); ++i ){
        if ( isnan(data[i]) )
            return false;
    }
    return true;
}
