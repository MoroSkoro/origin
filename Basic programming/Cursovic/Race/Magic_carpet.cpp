
#include "Magic_carpet.h"

Magic_carpet::Magic_carpet(double d) : Broom(d) {
    set_name("Ковер-самолет");
    set_type_transport('a');
    set_speed(10);
    this->distance = d;
    t = rase();
}

double Magic_carpet::rase() {
    double t = 0;

    if (distance < 1000){
        coef = 1;
        distance = distance * coef;
        t = distance / get_speed();
    }
    else if (distance < 5000) {
        coef = 0.97;
        distance = distance * coef;
        t = distance / get_speed();
        }
        else if (distance < 10000) {
            coef = 0.9;
            distance = distance * coef;
            t = distance / get_speed();
        }
        else if (distance >= 10000) {
        coef = 0.95;
        distance = distance * coef;
        t = distance / get_speed();
        }
    
    return t;
}