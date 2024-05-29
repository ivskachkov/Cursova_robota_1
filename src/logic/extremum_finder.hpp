#pragma once

#include <vector>
#include <functional>
#include "stat_provider.hpp"

class IExtremumFinder: public IStatProvider
{
public:
    virtual ~IExtremumFinder() = default;
    virtual std::vector<double> findExtremums(const std::function<double(double)> & f)const = 0;
};
