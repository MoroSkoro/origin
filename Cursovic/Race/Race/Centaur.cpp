//#include "../../pch.h"
#include "Centaur.h"
#include <iostream>
#include <string>

Ñentaur::Ñentaur(double d) : Camel(d) {
    set_name("Êåíòàâð");
    set_speed(15);
    driving_time = 8;
    rest_time = 2;
}

void Ñentaur::rase() {
    t = distance / get_speed();
    if (t > driving_time) {
        t = driving_time + rest_time;
        distance = distance - get_speed() * driving_time;
        while (distance > (get_speed() * driving_time))
        {
            t = t + driving_time + rest_time;
            distance = distance - get_speed() * driving_time;
        }
        double t_race = distance / get_speed();
        t = t + t_race;
    }
    //return t;  
}