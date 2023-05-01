#pragma once
#include "Camel.h"

class Boots_AllTerrain : public Camel {
    public:
        Boots_AllTerrain(double d);
        virtual ~Boots_AllTerrain() {};
protected:
        virtual double rase();
};

