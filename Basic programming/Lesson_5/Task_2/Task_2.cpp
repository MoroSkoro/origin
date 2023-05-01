
#include <iostream>
#include <string>

class Figure {
public:
    Figure(int sides_count, std::string name) : sides_count(sides_count), name(name){
        sides_count = 0;
        name = "Фигура";
    }
    int get_sides() {
        return sides_count;
    }
    std::string get_name() {
        return name;
    }
    virtual void print() {
        std::cout << get_name() << ": " << std::endl;
        std::cout << "Количество сторон: " << get_sides() << std::endl;
        std::cout << std::endl;
    }
    ~Figure() {};
private:
    int sides_count{0};
    std::string name{"Фигура"};
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c, int A, int B, int C) : Figure(3, "Треугольник")
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->A = A;
        this->B = B;
        this->C = C;
    }
    Triangle(int a, int b, int c, int A, int B):Figure(3, "Прямоугольный треугольник") {
        this->a = a;
        this->b = b;
        this->c = c;
        this->A = A;
        this->B = B;
        this->C = 90;
    }
    Triangle(int a, int b, int A, int B) :Figure(3, "Равнобедренный треугольник") {
        this->a = a;
        this->b = b;
        this->c = a;
        this->A = A;
        this->B = B;
        this->C = A;
    }
    
    Triangle(int a) :Figure(3, "Равносторонний треугольник") {
        this->a = a;
        this->b = a;
        this->c = a;
        this->A = 60;
        this->B = 60;
        this->C = 60;
    }

    int get_a() {
        return a;
    }
    int get_b() {
        return b;
    }
    int get_c() {
        return c;
    }
    int get_A() {
        return A;
    }
    int get_B() {
        return B;
    }
    int get_C() {
        return C;
    }
    virtual void print() override {
        std::cout << get_name() << ": " << std::endl;
        std::cout << "Количество сторон: " << get_sides() << std::endl;
        std::cout << "Стороны: " << "a=" << get_a() << " b=" << get_b() << " c=" << get_c() << std::endl;
        std::cout << "Углы: " << "A=" << get_A() << " B=" << get_B() << " C=" << get_C() << std::endl;
        std::cout << std::endl;
    }
    ~Triangle() {};
private:
    int a{ 1 };
    int b{ 1 };
    int c{ 1 };
    int A{ 1 };
    int B{ 1 };
    int C{ 1 };
};

class Right_triangle : public Triangle {
public:
    Right_triangle(int a, int b, int c, int A, int B):Triangle(a, b, c, A, B){}
    ~Right_triangle() {};
};

class Isosceles_triangle : public Triangle {
public:
    Isosceles_triangle(int a, int b, int A, int B):Triangle(a, b, A, B) {}
    ~Isosceles_triangle() {};
};

class Equilateral_triangle : public Triangle {
public:
    Equilateral_triangle(int a):Triangle(a) {}
    ~Equilateral_triangle() {};
};

class Quadrangle : public Figure {
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) : Figure(4, "Четырехугольник") {
        this->a = a;
        this->b = b;
        this->c = c;;
        this->d = d;
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
    }
    Quadrangle(int a, int b) : Figure(4, "Прямоугольник") {
        this->a = a;
        this->b = b;
        this->c = a;;
        this->d = b;
        this->A = 90;
        this->B = 90;
        this->C = 90;
        this->D = 90;
    }
    Quadrangle(int a) : Figure(4, "Квадрат") {
        this->a = a;
        this->b = a;
        this->c = a;;
        this->d = a;
        this->A = 90;
        this->B = 90;
        this->C = 90;
        this->D = 90;
    }
    Quadrangle(int a, int b, int A, int B) : Figure(4, "Параллелограмм") {
        this->a = a;
        this->b = b;
        this->c = a;;
        this->d = b;
        this->A = A;
        this->B = B;
        this->C = A;
        this->D = B;
    }
    Quadrangle(int a, int A, int B) : Figure(4, "Ромб") {
        this->a = a;
        this->b = a;
        this->c = a;;
        this->d = a;
        this->A = A;
        this->B = B;
        this->C = A;
        this->D = B;
    }

    int get_a() {
        return a;
    }
    int get_b() {
        return b;
    }
    int get_c() {
        return c;
    }
    int get_d() {
        return d;
    }
    int get_A() {
        return A;
    }
    int get_B() {
        return B;
    }
    int get_C() {
        return C;
    }
    int get_D() {
        return D;
    }
    virtual void print() override {
        std::cout << get_name() << ": " << std::endl;
        std::cout << "Количество сторон: " << get_sides() << std::endl;
        std::cout << "Стороны: " << "a=" << get_a() << " b=" << get_b() << " c=" << get_c() << " d=" << get_d() << std::endl;
        std::cout << "Углы: " << "A=" << get_A() << " B=" << get_B() << " C=" << get_C() << " D=" << get_D() << std::endl;
        std::cout << std::endl;
    }
    ~Quadrangle() {};
private:
    int a;
    int b;
    int c;
    int d;
    int A;
    int B;
    int C;
    int D;
};

class Rectangle : public Quadrangle {
public:
    Rectangle(int a, int b):Quadrangle(a, b){}
    Rectangle(int a) :Quadrangle(a) {}
    ~Rectangle() {};
};

class Square : public Rectangle {
public:
    Square(int a) :Rectangle(a) {}
    ~Square() {};
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B) :Quadrangle(a, b, A, B) {}
    Parallelogram(int a, int A, int B) :Quadrangle(a, A, B) {}
    ~Parallelogram() {};
};

class Phomb : public Parallelogram {
public:
    Phomb(int a, int A, int B):Parallelogram(a, A, B) {}
    ~Phomb() {};
};


void print_info(Figure* ptr) {
    ptr->print();
}

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Figure f(0, "Фигура");
    Triangle t(15,15,15,60,60,60);
    Right_triangle r_t(3,8,12,33,57);
    Isosceles_triangle i_t(12,6,40,100);
    Equilateral_triangle e_t(22);

    Quadrangle q(12, 34, 23, 10, 60,120,40,140);
    Rectangle r_q(20, 10);
    Square s_q(50);
    Parallelogram p_q(10, 20, 40, 140);
    Phomb ph_q(12,30,150);

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
}
