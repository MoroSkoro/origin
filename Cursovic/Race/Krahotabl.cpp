#include "Krahotabl.h"

Krahotabl::Krahotabl(double d) : Camel(d) {
    set_name("Кентавр");
    set_speed(15);
    driving_time = 8;
    rest_time1 = 2;
    this->distance = d;
    t = rase();
}

double Krahotabl::rase() {
    double t = 0;
    t = distance / get_speed();
        if (t > driving_time) {
            t = driving_time + rest_time1;
            distance = distance - get_speed() * driving_time;
            while (distance > (get_speed() * driving_time))
            {
                t = t + driving_time + rest_time1;
                distance = distance - get_speed() * driving_time;
            }
            double t_race = distance / get_speed();
            t = t + t_race;
        }

    return t;
}