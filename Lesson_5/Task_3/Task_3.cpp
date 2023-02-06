
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
    virtual void print_info() {
        std::cout << get_name() << ": " << std::endl;
        if (check()) {
            std::cout << "Правильная" << std::endl;
        }
        else { std::cout << "Неправильная" << std::endl; }
        std::cout << "Количество сторон: " << get_sides() << std::endl;
        std::cout << std::endl;
    }
    ~Figure() {};
protected:
    int sides_count{ 0 };
    std::string name{ 0 };
    //bool control = true;
    virtual bool check() {
        if (sides_count == 0) { return true; }
        else { return false; }
    }
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c, int A, int B, int C) : a(a), b(b), c(c), A(A), B(B), C(C)
    {
        sides_count = 3;
        name = "Треугольник";
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
    virtual void print_info() override {
        std::cout << get_name() << ": " << std::endl;
        if (check()) {
            std::cout << "Правильная" << std::endl;
        }
        else { std::cout << "Неправильная" << std::endl; }
        std::cout << "Количество сторон: " << get_sides() << std::endl;
        std::cout << "Стороны: " << "a=" << get_a() << " b=" << get_b() << " c=" << get_c() << std::endl;
        std::cout << "Углы: " << "A=" << get_A() << " B=" << get_B() << " C=" << get_C() << std::endl;
        std::cout << std::endl;
    }
    ~Triangle() {};
protected:
    Triangle() {};
    int a{ 1 };
    int b{ 1 };
    int c{ 1 };
    int A{ 1 };
    int B{ 1 };
    int C{ 1 };
    virtual bool check() override {
        if ((sides_count == 3)&&((A+B+C)==180)) { return true; }
        else { return false; }
    }
};

class Right_triangle : public Triangle {
public:
    Right_triangle(int a, int b, int c, int A, int B) {
        sides_count = 3;
        name = "Прямоугольный треугольник";
        this->a = a;
        this->b = b;
        this->c = c;
        this->A = A;
        this->B = B;
        this->C = 90;
    }
    ~Right_triangle() {};
protected:
    virtual bool check() override {
        if ((sides_count == 3) && ((A + B + C) == 180)&&(C==90)) { return true; }
        else { return false; }
    }
};

class Isosceles_triangle : public Triangle {
public:
    Isosceles_triangle(int a, int b, int A, int B) {
        sides_count = 3;
        name = "Равнобедренный треугольник";
        this->a = a;
        this->b = b;
        this->c = a;
        this->A = A;
        this->B = B;
        this->C = A;
    }
    ~Isosceles_triangle() {};
protected:
    virtual bool check() override {
        if ((sides_count == 3) && ((A + B + C) == 180) && (a == c)&&(A==C)) { return true; }
        else { return false; }
    }
};

class Equilateral_triangle : public Triangle {
public:
    Equilateral_triangle(int a) {
        sides_count = 3;
        name = "Равносторонний треугольник";
        this->a = a;
        this->b = a;
        this->c = a;
        this->A = 60;
        this->B = 60;
        this->C = 60;
    }
    ~Equilateral_triangle() {};
protected:
    virtual bool check() override {
        if ((sides_count == 3) && ((A + B + C) == 180) && ((a == b)&&(a == c)) && ((A == B)&&(A == C)&&(A==60))) { return true; }
        else { return false; }
    }
};

class Quadrangle : public Figure {
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) {
        sides_count = 4;
        name = "Четырехугольник";
        this->a = a;
        this->b = b;
        this->c = c;;
        this->d = d;
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
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
    virtual void print_info() override {
        std::cout << get_name() << ": " << std::endl;
        if (check()) {
            std::cout << "Правильная" << std::endl;
        }
        else { std::cout << "Неправильная" << std::endl; }
        std::cout << "Количество сторон: " << get_sides() << std::endl;
        std::cout << "Стороны: " << "a=" << get_a() << " b=" << get_b() << " c=" << get_c() << " d=" << get_d() << std::endl;
        std::cout << "Углы: " << "A=" << get_A() << " B=" << get_B() << " C=" << get_C() << " D=" << get_D() << std::endl;
        std::cout << std::endl;
    }
    ~Quadrangle() {};
protected:
    Quadrangle() {};
    int a;
    int b;
    int c;
    int d;
    int A;
    int B;
    int C;
    int D;
protected:
    virtual bool check() override {
        if ((sides_count == 4) && ((A + B + C +D) == 360)) { return true; }
        else { return false; }
    }
};

class Rectangle : public Quadrangle {
public:
    Rectangle(int a, int b) {
        sides_count = 4;
        name = "Прямоугольник";
        this->a = a;
        this->b = b;
        this->c = a;;
        this->d = b;
        this->A = 90;
        this->B = 90;
        this->C = 90;
        this->D = 90;
    }
    ~Rectangle() {};
protected:
    Rectangle() {};
    virtual bool check() override {
        if ((sides_count == 4) && ((A + B + C + D) == 360)&&(a==c)&&(b==d)&&(A==B)&&(A==C)&&(A==D)&&(A==90)) { return true; }
        else { return false; }
    }
};

class Square : public Rectangle {
public:
    Square(int a) {
        sides_count = 4;
        name = "Квадрат";
        this->a = a;
        this->b = a;
        this->c = a;;
        this->d = a;
        this->A = 90;
        this->B = 90;
        this->C = 90;
        this->D = 90;
    }
    ~Square() {};
protected:
    virtual bool check() override {
        if ((sides_count == 4) && ((A + B + C + D) == 360) && (a == b) &&(a==c)&& (a == d) && (A == B) && (A == C) && (A == D) && (A == 90)) { return true; }
        else { return false; }
    }
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B) {
        sides_count = 4;
        name = "Параллелограмм";
        this->a = a;
        this->b = b;
        this->c = a;;
        this->d = b;
        this->A = A;
        this->B = B;
        this->C = A;
        this->D = B;
    }
    ~Parallelogram() {};
protected:
    Parallelogram() {};
protected:
    virtual bool check() override {
        if ((sides_count == 4) && ((A + B + C + D) == 360) && (a == c) && (b == d) && (A == C) && (B == D)) { return true; }
        else { return false; }
    }
};

class Phomb : public Parallelogram {
public:
    Phomb(int a, int A, int B) {
        sides_count = 4;
        name = "Ромб";
        this->a = a;
        this->b = a;
        this->c = a;;
        this->d = a;
        this->A = A;
        this->B = B;
        this->C = A;
        this->D = B;
    }
    ~Phomb() {};
protected:
    Phomb() {};
protected:
    virtual bool check() override {
        if ((sides_count == 4) && ((A + B + C + D) == 360) && (a == b) && (a == c) && (a == d) && (A == C) && (B == D)) { return true; }
        else { return false; }
    }
};

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Figure f;
    Figure* ptr = &f;
    Triangle t(15, 15, 15, 60, 60, 60);
    Right_triangle r_t(3, 8, 12, 33, 57);
    Isosceles_triangle i_t(12, 6, 40, 100);
    Equilateral_triangle e_t(22);

    Quadrangle q(20,30,40,50,30,140,40,150);
    Rectangle r_q(20, 10);
    Square s_q(50);
    Parallelogram p_q(10, 20, 40, 140);
    Phomb ph_q(12, 30, 150);

    ptr->print_info();
    ptr = &t;
    ptr->print_info();
    ptr = &r_t;
    ptr->print_info();
    ptr = &i_t;
    ptr->print_info();
    ptr = &e_t;
    ptr->print_info();
    ptr = &q;
    ptr->print_info();
    ptr = &r_q;
    ptr->print_info();
    ptr = &s_q;
    ptr->print_info();
    ptr = &p_q;
    ptr->print_info();
    ptr = &ph_q;
    ptr->print_info();
}
