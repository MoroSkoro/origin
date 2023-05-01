
#include <iostream>

class Calculator {
  public:
      Calculator() {};
    double num1;
    double num2;
    double add() { return (num1 + num2); }
    double multiply() { return num1 * num2; }
    double subtract_1_2() { return(num1 - num2); }
    double subtract_2_1() { return(num2 - num1); }
    double divide_1_2() { return num1/num2; }
    double divide_2_1() { return num2/num1; }
    bool set_num1(double num1) {
        if (num1 != 0) {
            this->num1 = num1;
            return true;
        }
        else {
            return false;
        }
    }
    bool set_num2(double num2) {
        if (num2 != 0) {
            this->num2 = num2;
            return true;
        }
        else {
            return false;
        }
    }
    ~Calculator() {};
};

int main()
{
    setlocale(LC_ALL, "Russian");
    
    Calculator c;
    double num1, num2;

    do {
        std::cout << "Введите num1: ";
        std::cin >> num1;
        while (!c.set_num1(num1)) {
            std::cout << "Неверный ввод!\n";
            std::cout << "Введите num1: ";
            std::cin >> num1;
        }
        std::cout << "Введите num2: ";
        std::cin >> num2;
        while (!c.set_num2(num2)) {
            std::cout << "Неверный ввод!\n";
            std::cout << "Введите num2: ";
            std::cin >> num2;
        }
        std::cout << "num1 + num2 = " << c.add() << std::endl;
        std::cout << "num1 - num2 = " << c.subtract_1_2() << std::endl;
        std::cout << "num2 - num1 = " << c.subtract_2_1() << std::endl;
        std::cout << "num1 * num2 = " << c.multiply() << std::endl;
        std::cout << "num1 / num2 = " << c.divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << c.divide_2_1() << std::endl;
            
    } while (true);
}
