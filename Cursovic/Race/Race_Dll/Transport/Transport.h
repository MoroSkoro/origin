#pragma once
#include <iostream>
#include <string>

//#ifdef Rase_Dll_EXPORTS
//#define PROJECTAPI __declspec(dllexport)
//#else
//#define PROJECTAPI __declspec(dllimport)
//#endif

class  Transport
{
private:
	double speed{0};
	std::string name = "transport";
	char type_transport = 't';
protected:
	double t{0};
	double rest_time1{0};
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
};

