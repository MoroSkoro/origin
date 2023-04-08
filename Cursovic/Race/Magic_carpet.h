#pragma once
#include "Broom.h"


class  Magic_carpet : public Broom {
public:
    Magic_carpet(double);
    virtual ~Magic_carpet() {};

protected:
    virtual double rase();
};

