#include <iostream>
#include "Phomb.h"
#include "FigureException.h"

Phomb::Phomb(int a, int A, int B) :Parallelogram(a, A, B) {
    if ((get_a() != get_b()) || (get_a() != get_c()) || (get_a() != get_d())) throw FigureException("Ошибка создания фигуры. Причина: все стороны не равны.");
    if ((get_A() != get_C()) || (get_B() != get_D())) throw FigureException("Ошибка создания фигуры. Причина: углы A,C и B,D попарно не равны.");
}
    