
#include "Boots_AllTerrain.h"

Boots_AllTerrain::Boots_AllTerrain(double d) : Camel(d) {
    set_name("Ботинки-вездеходы");
    set_speed(6);
    driving_time = 60;
    rest_time1 = 10;
    rest_time2 = 5;
    this->distance = d;
    t = rase();
}

double Boots_AllTerrain::rase() {
    double t = 0;
    t = distance / get_speed();
    if (t > driving_time) {
        t = driving_time + rest_time1;
        distance = distance - get_speed() * driving_time;
        while (distance > (get_speed() * driving_time))
        {
            t = t + driving_time + rest_time2;
            distance = distance - get_speed() * driving_time;
        }
        double t_race = distance / get_speed();
        t = t + t_race;
    }

    return t;
}