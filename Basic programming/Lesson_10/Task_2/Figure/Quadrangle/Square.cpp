#include <iostream>
#include "Square.h"
#include "FigureException.h"

Square::Square(int a) :Rectangle(a) {
    if ((get_a() != get_b()) || (get_a() != get_c()) || (get_a() != get_d())) throw FigureException("Ошибка создания фигуры. Причина: все стороны не равны.");
}
   