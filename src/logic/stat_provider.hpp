#pragma once

class IStatProvider
{
public:
    virtual ~IStatProvider() = default;
    virtual int getIterations()const = 0;
    virtual int getOperations()const = 0;
};