
#include "Broom.h"

Broom::Broom(double d) : Transport() {
    set_name("Метла");
    set_type_transport('a');
    set_speed(20);
    this->distance = d;
    t = rase();
}

double Broom::rase() {
    double t = 0;
    int a = distance / 1000;
    if (a == 0) { coef = 1; }
    else {
        coef = 1- (double)a / 100;
    }
    distance = distance * coef;
    t = distance / get_speed();
    return t;
}
