
#include <iostream>
#include <vector>

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::vector<int> vec = { 11,22,33,44,55,66 };
    std::cout << "Входные данные: ";
    for (auto var : vec){
        std::cout << var << " ";
    }
    std::cout << "\n";

    std::cout << "Выходные данные: ";
    for (auto var : vec) {
        [&var]{
            if (var % 2 != 0) {
                std::cout << (var * 3) << " ";
            }
            else std::cout << var << " ";
        }();
    }
}