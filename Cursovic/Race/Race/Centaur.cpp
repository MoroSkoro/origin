//#include "../../pch.h"
#include "Centaur.h"
#include <iostream>
#include <string>

�entaur::�entaur(double d) : Camel(d) {
    set_name("�������");
    set_speed(15);
    driving_time = 8;
    rest_time = 2;
}

void �entaur::rase() {
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