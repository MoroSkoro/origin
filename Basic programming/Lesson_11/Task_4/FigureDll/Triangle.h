#pragma once
#include "Figure.h"

class PROJECTAPI Triangle : public Figure {
    public:

    Triangle(int a, int b, int c, int A, int B, int C, std::string name = "Треугольник");
    
    int get_a();
    int get_b();
    int get_c();
    int get_A();
    int get_B();
    int get_C();
    virtual void print() override;
    ~Triangle() {};
    private:
    int a{ 1 };
    int b{ 1 };
    int c{ 1 };
    int A{ 1 };
    int B{ 1 };
    int C{ 1 };
};
