#include <iostream>
#define MODE 1

#if MODE==1
double add(double a, double b) { return (a + b); }
#endif

int main()
{
    //SetConsoleCP(1251);
     //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    
    double a, b;

#ifndef MODE
#error Необходимо определить MODE
#endif // !MODE

#if MODE==0
    std::cout << "«Работаю в режиме тренировки»";
#elif MODE==1
    std::cout << "«Работаю в боевом режиме»\n";
    std::cout << "«Введите число 1: ";
    std::cin >> a;
    std::cout << "«Введите число 2: ";
    std::cin >> b;
    std::cout << "«Результат сложения: " << add(a, b) << std::endl;
#else
    std::cout << "«Неизвестный режим. Завершение работы»";
#endif

}
