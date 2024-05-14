#include "utils.hpp"
#include <cmath>

double calcStep(double x, double * max)
{
    double prefix = 1;
    while ( fabs(x) < 1 ) {
        x *= 10;
        prefix *= 10;
    }
    while ( fabs(x) > 10 ) {
        x /= 10;
        prefix /= 10;
    }
    if ( max ){
        *max = int(ceil(x)/prefix);
        if ( int(*max) %2 == 1 )
            *max += 1;
    }
    return ceil(2*x*0.1)/prefix;;
}