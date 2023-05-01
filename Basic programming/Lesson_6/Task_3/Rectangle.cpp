#include <iostream>
#include "Rectangle.h"

Rectangle::Rectangle(int a, int b) :Quadrangle(a, b, a, b, 90, 90, 90, 90, "Прямоугольник") {}
Rectangle::Rectangle(int a) :Quadrangle(a, a, a, a, 90, 90, 90, 90, "Квадрат") {}
   