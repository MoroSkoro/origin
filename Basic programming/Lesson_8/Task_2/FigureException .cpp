#include <iostream>
#include "FigureException.h"

FigureException::FigureException(const char* e) :std::domain_error(e) {}
   