
#include "pch.h"
//#include <utility>
//#include <limits.h>
#include "LeaverDll.h"
#include <string>



std::string Leaver::leave(std::string* name) {
	std::string hi = ("До свидания, " + *name + "!");
	return (hi);
}