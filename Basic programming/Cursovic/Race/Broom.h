#pragma once
#include "Transport.h"

class Broom : public Transport {
public:
    Broom(double);
    virtual ~Broom() {};
protected:
    double coef{ 1 };
    virtual double rase();
};
