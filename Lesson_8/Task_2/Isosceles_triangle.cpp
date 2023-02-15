#include <iostream>
#include "Isosceles_triangle.h"
#include "FigureException.h"

Isosceles_triangle::Isosceles_triangle(int a, int b, int A, int B) :Triangle(a, b, a, A, B, A, "Равнобедренный треугольник") {
    if (!(a == get_c())) throw FigureException("Ошибка создания фигуры. Причина: стороны a и c не равны.");
    if (!(A == get_C())) throw FigureException("Ошибка создания фигуры. Причина: углы A и C не равны.");
}
    