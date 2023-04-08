
#include <iostream>
#include <windows.h>

int more_x(int arr[], int &size, int& x) {
    int left = 0;
    int right = size - 1;
    int middl=0, n = 0;
    while (left < right) {
        middl = (left + right) / 2;
        if (arr[middl] <= x) {
            left = middl + 1;
            if (arr[size-1]<=x) { n = left + 1; }
            else n = left;  
        }
        else {
                right = middl - 1;
                if (arr[0] > x) { n = middl - 1; }
                else n = middl;
        }
    }
    return (size-n);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int arr[9]{ 14, 16, 19, 32, 32, 32, 56, 69, 72 };
    int size = 9;
    int x = 0, n = 0;
    int exit = 1;

    while (exit != 0) {
        std::cout << "Введите точку отсчёта: ";
        std::cin >> x;
        std::cout << "Количество элементов в массиве больших, чем " << x << ": " << more_x(arr, size, x) << "\n\n";
        std::cout << "Продолжить: 1. Выйти: 0. \n";
        std::cin >> exit;
    }
    
}
