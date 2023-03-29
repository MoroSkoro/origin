//#include "../../pch.h"
#include "Boots_AllTerrain.h"

Boots_AllTerrain::Boots_AllTerrain(double d) : Camel(d) {
    set_name("Ботинки-вездеходы");
    set_speed(6);
    driving_time = 60;
    rest_time1 = 10;
    rest_time = 5;
}

//void Boots_AllTerrain::rase() {}