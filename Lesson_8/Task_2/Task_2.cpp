
#include <iostream>
#include <string>
#include "Figure.h"
#include "Triangle.h"
#include "Right_triangle.h"
#include "Isosceles_triangle.h"
#include "Equilateral_triangle.h"
#include "Quadrangle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Parallelogram.h"
#include "Phomb.h"
#include <exception>
#include <stdexcept>
#include "FigureException.h"

#define Catch catch (FigureException e) { \
std::cout << e.what() << std::endl << std::endl; \
    }

void print_info(Figure* ptr) {
    ptr->print();
}

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Figure f(0, "Фигура");
    Figure* ptr = &f;
    print_info(ptr);
    
    try { 
        Triangle t (15, 15, 15, 61, 60, 60);
        print_info(&t);
    }
    Catch
        
    try {
        Right_triangle r_t(3, 8, 12, 46, 44);
        print_info(&r_t);
    }
    Catch

    try {
        Isosceles_triangle i_t(12, 6, 40, 100);
        print_info(&i_t);
    }
    Catch

    try {
        Equilateral_triangle e_t(22);
        print_info(&e_t);
    }
    Catch
    
    try {
        Quadrangle q(12, 34, 23, 10, 60, 120, 40, 140);
        print_info(&q);
    }
    Catch
    
    try {
        Rectangle r_q(20, 10);
        print_info(&r_q);
    }
    Catch

    try {
        Square s_q(50);
        print_info(&s_q);
    }
    Catch
    
    try {
        Parallelogram p_q(10, 20, 40, 140);
        print_info(&p_q);
    }
    Catch
    
    try {
        Phomb ph_q(12, 31, 150);
        print_info(&ph_q);
    }
    Catch  
}
