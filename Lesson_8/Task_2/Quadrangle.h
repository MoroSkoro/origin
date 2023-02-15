#pragma once

#include "Figure.h"

class Quadrangle : public Figure {
public:

    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D, std::string name = "Четырехугольник");

    int get_a();
    int get_b();
    int get_c();
    int get_d();
    int get_A();
    int get_B();
    int get_C();
    int get_D();
    virtual void print();
    ~Quadrangle() {};
private:
    int a;
    int b;
    int c;
    int d;
    int A;
    int B;
    int C;
    int D;
};