
#include "Eagle.h"

Eagle::Eagle(double d) : Broom(d) {
    set_name("Орел");
    set_type_transport('a');
    set_speed(8);
    coef = 0.94;
    this->distance = d;
    t = this->rase();
}

double Eagle::rase() {
    double t = 0;
    distance = distance * coef;
    t = distance / get_speed();
    return t;
}
