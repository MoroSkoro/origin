#pragma once
#include <iostream>
#include <string>


class Transport
{
private:
	double speed{ 1 };
	std::string name = "transport";
	char type_transport = 't';
protected:
	double t{1};
	double rest_time1{0};
	virtual double rase();
public:
	Transport();
	~Transport() {};
	double distance{0};
	double get_speed();
	void set_speed(double speed);
	std::string get_name();
	void set_name(std::string name);
	char get_type_transport();
	void set_type_transport(char);
	double get_t();
};

