#include <iostream>
#include <string>
#include <windows.h>
#include "LeaverDll.h"



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::string name;

    std::cout << "Введите имя: ";
    std::getline(std::cin, name);
    std::cout << Leaver::leave(&name);

    std::cin.get();
}
