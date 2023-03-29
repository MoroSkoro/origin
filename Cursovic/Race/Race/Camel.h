#pragma once
#include "Transport.h"

//class PROJECTAPI Camel : public Transport {
    class  Camel : public Transport {
public:
    Camel(double);
    virtual ~Camel() {};
    double get_t();
//private:
protected:
    double driving_time{0};
    double rest_time{0};
    //double rest_time{0};
    //double t{0};
    virtual void rase();
};