
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::vector<int> vec = { 11,22,33,44,55,66 };
    std::cout << "Входные данные: ";
    for_each(vec.begin(), vec.end(), [](int i){std::cout << i << " ";});
    std::cout << "\n\n";

    std::cout << "Выходные данные: ";
    for_each(vec.begin(), vec.end(),
        [](int i) {
            if (i % 2 != 0) {
                std::cout << (i * 3) << " ";
            }
            else std::cout << i << " ";
        }
    );
    std::cout << "\n\n";
}