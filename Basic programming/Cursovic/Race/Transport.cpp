
#include "Transport.h"

Transport::Transport(){}

double Transport::get_speed() {
	return speed;
}

void Transport::set_speed(double speed) {
	this->speed = speed;
}

std::string Transport::get_name() {
	return name;
}

void Transport::set_name(std::string name) {
	this->name = name;
}

double Transport::rase(){
	double t = 0;
	return t;
}

double Transport::get_t() {
	return t;
}

char Transport::get_type_transport() {
	return type_transport;
}
void Transport::set_type_transport(char type_transport) {
	this->type_transport = type_transport;
}