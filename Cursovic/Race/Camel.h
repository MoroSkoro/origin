#pragma once
#include "Transport.h"

    class Camel : public Transport {
public:
    Camel(double);
    virtual ~Camel() {};
protected:
    double driving_time{0};
    double rest_time2{0};
    virtual double rase();
};