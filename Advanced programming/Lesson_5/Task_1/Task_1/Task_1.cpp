#include <iostream>
#include <vector>

template <typename T>
void squ(T& a) {
    int n = a * a;
    std::cout << "[IN]: " << a << "\n";
    std::cout << "[OUT]: " << n << "\n";
}

template <>
void squ(std::vector<int>& a) {
    std::vector<int> n = a;
    size_t x{ 0 };

    for (auto i : n) {
        n[x] = i * i;
        x++;
    }

    std::cout << "\n";
    std::cout << "[IN]: ";
    for (auto i : a) {
       std::cout << i << " ";
    }

    std::cout << "\n";
    std::cout << "[OUT]: ";
    for (auto i : n) {
        std::cout << i << " ";
    }
    
}

int main()
{
    int a = 4;
    squ(a);

    std::vector<int> arr{ -1, 4, 8 };
    squ(arr);
}
