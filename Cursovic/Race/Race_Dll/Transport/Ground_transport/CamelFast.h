#pragma once
#include "Camel.h"

class  CamelFast: public Camel {
public:
    CamelFast(double d): Camel(d){};
     virtual ~CamelFast() {};
     double get_rest_time2();
     void set_rest_time2(double);
protected:
    double rest_time2 = 6.5;
    virtual void rase();
};