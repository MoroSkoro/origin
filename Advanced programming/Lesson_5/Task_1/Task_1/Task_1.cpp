#include <iostream>
#include <vector>

template <typename T>
T& squ(T& a) {
    a = a * a;
    return a;
}

template <>
std::vector<int>& squ(std::vector<int>& a) {
    size_t x{ 0 };
    for (auto i : a) {
        a[x] = i * i;
        x++;
    }
    return a;
}

int main()
{
    int a = 4;
    
    std::cout << "[IN]: " << a << "\n";
    std::cout << "[OUT]: " << squ(a) << "\n";
    std::cout << "\n";

    std::vector<int> arr{ -1, 4, 8 };
    std::cout << "[IN]: ";
    for (auto i : arr) {
        std::cout << i << " ";
    }

    std::cout << "\n";
    std::cout << "[OUT]: ";
    squ(arr);
    for (auto i : arr) {
        std::cout << i << " ";
    }
}
