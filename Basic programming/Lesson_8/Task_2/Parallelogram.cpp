#include <iostream>
#include "Parallelogram.h"
#include "FigureException.h"

Parallelogram::Parallelogram(int a, int b, int A, int B) :Quadrangle(a, b, a, b, A, B, A, B, "Параллелограмм") {
    if ((get_a() != get_c()) || (get_b() != get_d())) throw FigureException("Ошибка создания фигуры. Причина: стороны a,c и b,d попарно не равны.");
    if ((get_A() != get_C()) || (get_B() != get_D())) throw FigureException("Ошибка создания фигуры. Причина: углы A,C и B,D попарно не равны.");
}
Parallelogram::Parallelogram(int a, int A, int B) :Quadrangle(a, a, a, a, A, B, A, B, "Ромб") {}
   