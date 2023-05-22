#include <iostream>
#include <windows.h>
#include <set>
#include <vector>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    size_t size;
    std::set<int, std::greater<>> no_dupl;

    std::cout << "Введите количество элементов, далее сами значения:\n";
    std::cin >> size;
    std::vector<int> vec(size); //= { 1, 5, 1, 3, 4, 4 };
    for (size_t i = 0; i < size; i++) {
        std::cout << "Введите " << i + 1 << " число: ";
        std::cin >> vec[i];
        no_dupl.insert(vec[i]);
    }

    std::cout << "\n";
    std::cout << "[IN]:\n";
    std::cout << size << "\n";
    for (auto a : vec) { std::cout << a << "\n"; }
   
    std::cout << "OUT:\n";
    for (auto a : no_dupl) { std::cout << a << "\n"; }
    system("pause");
}