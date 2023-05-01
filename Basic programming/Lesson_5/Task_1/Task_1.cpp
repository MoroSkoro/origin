
#include <iostream>
#include <string>

class Figure {
public:
    Figure() {
        sides_count = 0;
        name = "Фигура";
    }
    int get_sides() {
        return sides_count;
    }
    std::string get_name() {
        return name;
    }
    ~Figure() {};
protected:
    int sides_count;
    std::string name;
};

class Triangle: public Figure {
public:
    Triangle() {
        sides_count = 3;
        name = "Треугольник";
    }
   
    ~Triangle() {};
};

class Quadrangle : public Figure {
public:
    Quadrangle() {
        sides_count = 4;
        name = "Четырехугольник";
    }

    ~Quadrangle() {};
};


int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Figure f;
    Triangle t;
    Quadrangle q;

    std::cout << "Количество сторон:" << std::endl;
    std::cout << f.get_name() << ": " << f.get_sides() << std::endl;
    std::cout << t.get_name() << ": " << t.get_sides() << std::endl;
    std::cout << q.get_name() << ": " << q.get_sides() << std::endl;

}
