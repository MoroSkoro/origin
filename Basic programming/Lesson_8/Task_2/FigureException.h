#pragma once
#include <exception>
#include <stdexcept>

class FigureException :public std::domain_error {
public:
    FigureException(const char* e);
    ~FigureException() {};
};