
#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>

class Counter {
private:
    int count;
public:
    Counter() { count = 1; };
    Counter(int count) { this->count = count; };
    void increase() { ++count; }
    void decrease() { --count; }
    void set_count(int count) {
        this->count = count;
    }
    int get_count() {
        return count;
    }
    ~Counter() {};
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Counter c;
    int count, n;
    std::string s;
    bool t = false;
    
    do {
        t = false;
        std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
        std::cin >> s;
        if (s == "да") {
            std::cout << "Введите начальное значение счётчика: ";
            std::cin >> count;
            c.set_count(count);
        }
        else if (s != "нет") {
            std::cout << "Введите да или нет\n";
            t = true;
        }
    } while (t);
    
        
    do {
        std::cout << "Введите команду (Пожалуйста, переключитесь на английскую раскладку клавиатуры!) ('+', '-', '=' или 'x'): ";
        n = _getch();
        std::cout << std::endl;
        if (n == '+') {
            c.increase();
        }
        if (n == '-') {
            c.decrease();
        }
        if (n == '=') {
            std::cout << c.get_count() << std::endl;
        }
    } while (n != 'x');
    std::cout << "До свидания!";
        
}
