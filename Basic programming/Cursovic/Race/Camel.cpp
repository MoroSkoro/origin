
#include "Camel.h"

Camel::Camel(double d) : Transport() {
    set_name("�������");
    set_type_transport('g');
    set_speed(10);
    driving_time = 30;
    rest_time1 = 5;
    rest_time2 = 8;
    this->distance = d;
    t = rase();
}

double Camel::rase(){
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
