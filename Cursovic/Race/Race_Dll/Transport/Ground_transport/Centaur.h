#pragma once
#include "Camel.h"

    class  Ñentaur : public Camel {
    public:
        //ÑamelFast(double distance);
        Ñentaur(double d) : Camel(d) {};
        virtual ~Ñentaur() {};
    protected:
        virtual void rase();
    };
