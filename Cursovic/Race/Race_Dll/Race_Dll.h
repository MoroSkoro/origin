#pragma once
#include <string>

#ifdef Rase_Dll_EXPORTS
#define PROJECTAPI __declspec(dllexport)
#else
#define PROJECTAPI __declspec(dllimport)
#endif

#include "Transport/Transport.h"
#include "Transport/Ground_transport/Camel.h"
#include "Centaur.h"
