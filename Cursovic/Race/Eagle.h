#pragma once
#include "Broom.h"

class  Eagle : public Broom {
public:
    Eagle(double);
    virtual ~Eagle() {};

protected:
    virtual double rase();
};

