#include "iteration_extremum_finder.hpp"
#include <cmath>
#include <stdexcept>

IterationExtremumFinder::IterationExtremumFinder(double leftx, double rightx, double eps, double step)
    : leftx(leftx), rightx(rightx), eps(eps), step(step)
{
}

std::vector<double> IterationExtremumFinder::findExtremums(const std::function<double(double)> & f) const
{
    std::vector<double> roots;
    double x = leftx;
    double y = f(x);
    while (x < rightx) {
        if (y * f(x + step) < 0) {
            roots.push_back(findRoot(x, x + step, eps, f));
        }
        x += step;
        y = f(x);
    }
    return roots;
}

double IterationExtremumFinder::findRoot(double leftx, double rightx, double eps, const std::function<double(double)> & f) const
{
    double x = (leftx + rightx) / 2;
    double y = f(x);
    double prefix = f(x + eps) > y ? 1 : -1;
    int i = 0;
    while (fabs(y) > eps && i++ < 10000) {
        if (y * prefix > 0) {
            rightx = x;
        } else {
            leftx = x;
        }
        x = (leftx + rightx) / 2;
        y = f(x);
    }
    if (i == 1000) {
        throw std::runtime_error("Root not found");
    }
    return x;
}
