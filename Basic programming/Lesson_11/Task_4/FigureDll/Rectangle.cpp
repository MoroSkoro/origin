#include <iostream>
#include "Rectangle.h"

Rectangle1::Rectangle1(int a, int b) : Quadrangle(a, b, a, b, 90, 90, 90, 90, "Прямоугольник") {}
Rectangle1::Rectangle1(int a) : Quadrangle(a, a, a, a, 90, 90, 90, 90, "Квадрат") {}
   