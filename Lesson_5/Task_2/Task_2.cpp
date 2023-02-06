
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
    int sides_count{0};
    std::string name{0};
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c, int A, int B, int C): a(a), b(b), c(c), A(A), B(B), C(C)
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
    ~Triangle() {};
protected:
    Triangle() {};
    int a{ 1 };
    int b{ 1 };
    int c{ 1 };
    int A{ 1 };
    int B{ 1 };
    int C{ 1 };
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
    //this->A = 60;
    ~Equilateral_triangle() {};
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
};


void print_info_q(Quadrangle* n) {
    std::cout << n->get_name() << ": " << std::endl;
    std::cout << "Стороны: " << "a=" << n->get_a() << " b=" << n->get_b() << " c=" << n->get_c() << " d=" << n->get_d() << std::endl;
    std::cout << "Углы: " << "A=" << n->get_A() << " B=" << n->get_B() << " C=" << n->get_C() << " D=" << n->get_D() << std::endl;
    std::cout << std::endl;
}

void print_info_t(Triangle* n) {
    std::cout << n->get_name() << ": " << std::endl;
    std::cout << "Стороны: " << "a=" << n->get_a() << " b=" << n->get_b() << " c=" << n->get_c() << std::endl;
    std::cout << "Углы: " << "A=" << n->get_A() << " B=" << n->get_B() << " C=" << n->get_C() << std::endl;
    std::cout << std::endl;
}

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Triangle t(15,15,15,60,60,60);
    Right_triangle r_t(3,8,12,33,57);
    Isosceles_triangle i_t(12,6,40,100);
    Equilateral_triangle e_t(22);

    Rectangle r_q(20, 10);
    Square s_q(50);
    Parallelogram p_q(10, 20, 40, 140);
    Phomb ph_q(12,30,150);

    print_info_t(&t);
    print_info_t(&r_t);
    print_info_t(&i_t);
    print_info_t(&e_t);

    print_info_q(&r_q);
    print_info_q(&s_q);
    print_info_q(&p_q);
    print_info_q(&ph_q);
}
