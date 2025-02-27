#pragma once

#include "extremum_finder.hpp"

class IterationExtremumFinder : public IExtremumFinder
{
public:
    IterationExtremumFinder(double leftx, double rightx, double eps, double step);
    std::vector<double> findExtremums(const std::function<double(double)> & f) const override;
    int getIterations() const override { return iterations; }
    int getOperations() const override { return operations; }
private:
    double findRoot(double leftx, double rightx, double eps, const std::function<double(double)> & f) const;
    double leftx;
    double rightx;
    double eps;
    double step;
    mutable int iterations;
    mutable int operations;
};