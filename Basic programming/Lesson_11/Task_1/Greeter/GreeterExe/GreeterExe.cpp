#include <iostream>
#include <string>
#include <windows.h>
#include "GreeterLib.h"



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

	std::string name;

    std::cout << "Введите имя: ";
	std::getline (std::cin, name);
	std::cout << Greeter::greet(&name);

    std::cin.get();
}
