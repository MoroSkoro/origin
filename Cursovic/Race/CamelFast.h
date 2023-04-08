#pragma once
#include "Camel.h"

class CamelFast: public Camel {
public:
    CamelFast(double d);
     virtual ~CamelFast() {};
protected:
    double rest_time3 = 8;
    virtual double rase();
};