#include <iostream>
#include <string>
#include "FigureDll.h"

void print_info(Figure* ptr) {
    ptr->print();
}

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Figure f(0, "Фигура");
    Triangle t(15, 15, 15, 60, 60, 60);
    Right_triangle r_t(3, 8, 12, 33, 57);
    Isosceles_triangle i_t(12, 6, 40, 100);
    Equilateral_triangle e_t(22);

    Quadrangle q(12, 34, 23, 10, 60, 120, 40, 140);
    Rectangle1 r_q(20, 10);
    Square s_q(50);
    Parallelogram p_q(10, 20, 40, 140);
    Phomb ph_q(12, 30, 150);

    Figure* ptr = &f;
    print_info(ptr);
    ptr = &t;
    print_info(ptr);
    ptr = &r_t;
    print_info(ptr);
    ptr = &i_t;
    print_info(ptr);
    ptr = &e_t;
    print_info(ptr);
    ptr = &q;
    print_info(ptr);
    ptr = &r_q;
    print_info(ptr);
    ptr = &s_q;
    print_info(ptr);
    ptr = &p_q;
    print_info(ptr);
    ptr = &ph_q;
    print_info(ptr);
    std::cin.get();
}
