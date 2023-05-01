#include <iostream>
#include "Parallelogram.h"

Parallelogram::Parallelogram(int a, int b, int A, int B) :Quadrangle(a, b, a, b, A, B, A, B, "Параллелограмм") {}
Parallelogram::Parallelogram(int a, int A, int B) :Quadrangle(a, a, a, a, A, B, A, B, "Ромб") {}
Parallelogram::Parallelogram(int a) :Quadrangle(a, a, a, a, 90, 90, 90, 90, "Квадрат") {}
   