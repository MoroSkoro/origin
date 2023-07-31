#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <list>
#include <future>
#include <iterator>

std::list<int>::iterator ThreadFunc (std::list<int>& c1, std::list<int>::iterator& it_start, int& min,
    std::list<int>::iterator& it_min) {
    std::list<int>::iterator iter;
    for (iter = it_start; iter != c1.end(); iter++) {
        if (min >= *iter) {
            min = *iter;
            it_min = iter;
        }
    }
    return it_min;
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU.1251");
    
    std::list<int> c1{5, 3, -1, 7, 8, 89, 0};

    std::list<int>::iterator it_start, it1, iter, it_min;
    it_start = c1.begin();
    int min = *it_start;
    int size = c1.size();

    std::cout << "До сортировки: " << std::endl;
    for (auto c : c1) {
        std::cout << c << "  ";
    }
    std::cout << std::endl;

    for (int i = 0; i < size; i++) {
        int min = *it_start;

        auto ft = std::async(std::launch::async, ThreadFunc, std::ref(c1), std::ref(it_start),
            std::ref(min), std::ref(it_min));

        ft.wait();
        it_min = ft.get();
       
        if (it_start != it_min) {
            *it_min = *it_start;
            *it_start = min;
        }
        ++it_start;
    }

    std::cout <<"После сортировки: "<<std::endl;
    for (auto c : c1) {
        std::cout << c << "  ";

    }
    std::cout << std::endl;
    return 0;
}