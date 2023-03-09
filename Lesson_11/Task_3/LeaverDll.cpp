
#include "LeaverDll.h"

std::string Leaver::leave(std::string* name) {
	std::string hi = ("До свидания, " + *name + "!");
	return (hi);
}