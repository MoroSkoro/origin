#pragma once


#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

#include "Transport.h"
#include "Camel.h"
#include "CamelFast.h"
#include "Krahotabl.h"
#include "Boots_AllTerrain.h"
#include "Broom.h"
#include "Eagle.h"
#include "Magic_carpet.h"


bool check(double& d, std::vector < std::string >& v_check, int& number_of_participants, int& reg);

void print_check(double& d, std::vector < std::string >& v_check, int& number_of_participants, int& reg);

void registration(double& d, std::string& tRace, int typeRace, std::vector < std::string >& v_check, int& number_of_participants);

bool sortBy_t(Transport l_t, Transport r_t);

void gonka(std::vector<std::string >& v_check, double& d);