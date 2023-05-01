#include "Calc.h"
#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    double a, b;
    char oper = '1';

    std::cout << "Введите первое число: ";
    std::cin >> a;
    std::cout << "Введите второе число: ";
    std::cin >> b;
    do {
        std::cout << "Выберите операцию (1 - сложение, 2 - вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень, q - выход): ";
        std::cin >> oper;
        switch (oper) {
        case '1':
            std::cout << a << "+" << b << "=" << add(a, b) << std::endl;
            break;
        case '2':
            std::cout << a << "-" << b << "=" << subtract(a, b) << std::endl;
            break;
        case '3':
            std::cout << a << "*" << b << "=" << multiply(a, b) << std::endl;
            break;
        case '4':
            if (b != 0) {
                std::cout << a << "/" << b << "=" << divide(a, b) << std::endl;
            }
            else { std::cout << "Деление на 0 запрещено!" << std::endl; }
            break;
        case '5':
            std::cout << a << " в степени " << b << " = " << power_of(a, b) << std::endl;
            break;
        }
    } while (oper != 'q');
}
