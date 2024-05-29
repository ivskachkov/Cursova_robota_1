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
    iterations = 0;
    operations = 0;
    double x = leftx;
    double yl = f(x);
    double yr = f(x+step);
    while (x < rightx) {
        if (yl * yr < 0) {
            roots.push_back(findRoot(x, x + step, eps, f));
        }
        x += step;
        yl = yr;
        yr = f(x+step);
        iterations++;
        operations += 4;
    }
    return roots;
}

double IterationExtremumFinder::findRoot(double leftx, double rightx, double eps, const std::function<double(double)> & f) const
{
    std::vector<double> roots;
    double x = leftx;
    double yl = f(x);
    double yr = f(x+eps);
    while (x < rightx) {
        iterations++;
        if (yl * yr < 0) {
            operations += 2;
            return x+eps/2;
        }
        x += eps;
        yl = yr;
        yr = f(x+eps);
        operations += 4;
    }
    throw std::runtime_error("Root not found");
}
