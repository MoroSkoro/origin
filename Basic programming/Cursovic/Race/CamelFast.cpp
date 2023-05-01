
#include "CamelFast.h"
#include <iostream>
#include <string>

CamelFast::CamelFast(double d): Camel(d) {
    set_name("Верблюд-быстроход");
    set_speed(40);
    driving_time = 10;
    rest_time1 = 5;
    rest_time2 = 6.5;
    this->distance = d;
    t = rase();
}

double CamelFast::rase() {
    double t = 0;
    t = distance / get_speed();
    if (t > driving_time) {
        t = driving_time + rest_time1;
        distance = distance - get_speed() * driving_time;
        if (distance > (get_speed() * driving_time)) {
            t = driving_time + rest_time2;
            distance = distance - get_speed() * driving_time;
        }
        while (distance > (get_speed() * driving_time))
        {
            t = t + driving_time + rest_time3;
            distance = distance - get_speed() * driving_time;
        }
        double t_race = distance / get_speed();
        t = t + t_race;
    }
    return t;  
}