#include <iostream>
#include "Right_triangle.h"
#include "FigureException.h"

Right_triangle::Right_triangle(int a, int b, int c, int A, int B) :Triangle(a, b, c, A, B, 90, "Прямоугольный треугольник") {
    if (!((180 - (A + B)) == 90)) throw FigureException("Ошибка создания фигуры. Причина: угол С не равен 90.");
}
    