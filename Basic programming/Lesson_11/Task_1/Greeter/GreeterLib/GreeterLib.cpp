#include "GreeterLib.h"
#include <string>



std::string Greeter::greet(std::string* name) {
	std::string hi = ("Здравствуйте, " + *name + "!");
	return (hi);
}