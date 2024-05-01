#pragma once

#include <vector>
#include <functional>

class IExtremumFinder
{
public:
    virtual ~IExtremumFinder() = default;
    virtual std::vector<double> findExtremums(const std::function<double(double)> & f)const = 0;
};
