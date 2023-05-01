#pragma once
#include "Quadrangle.h"

class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B);
    Parallelogram(int a, int A, int B);
    ~Parallelogram() {};
};
