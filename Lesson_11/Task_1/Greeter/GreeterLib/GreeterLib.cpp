#include "GreeterLib.h"
#include <string>



std::string Greeter::greet(std::string* name) {
	std::string hi = ("������������, " + *name + "!");
	return (hi);
}