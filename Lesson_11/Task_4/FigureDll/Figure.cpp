#include <iostream>
#include "Figure.h"

Figure::Figure(int sides_count, std::string name) : sides_count(sides_count), name(name) {
        sides_count = 0;
        name = "Фигура";
    }
    int Figure::get_sides() {
        return sides_count;
    }
    std::string Figure::get_name() {
        return name;
    }
    void Figure::print() {
        std::cout << get_name() << ": " << std::endl;
        std::cout << "Количество сторон: " << get_sides() << std::endl;
        std::cout << std::endl;
    }
