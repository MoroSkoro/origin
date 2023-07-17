#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <algorithm>
#include <ctime>



using namespace std::chrono_literals;

void sum_vec(double& t1, double& t2, double& t3, double& t4) {
    
    //Заполняем векторы 1000
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> v1(1000);
    std::generate(v1.begin(), v1.end(), std::rand);

    std::srand(unsigned(std::time(nullptr) / 2));
    std::vector<int> v2(1000);
    std::generate(v2.begin(), v2.end(), std::rand);

    //Складываем векторы
    auto start = std::chrono::steady_clock::now();
    std::transform(v1.begin(), v1.end(), v2.begin(), v1.begin(), std::plus<int>());
    
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    t1 = elapsed_seconds.count();
    
    //Заполняем векторы 10000
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> v3(10000);
    std::generate(v3.begin(), v3.end(), std::rand);

    std::srand(unsigned(std::time(nullptr) / 2));
    std::vector<int> v4(10000);
    std::generate(v4.begin(), v4.end(), std::rand);

    //Складываем векторы
    start = std::chrono::steady_clock::now();
    std::transform(v3.begin(), v3.end(), v4.begin(), v3.begin(), std::plus<int>());

    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    t2 = elapsed_seconds.count();

    //Заполняем векторы 100000
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> v5(100000);
    std::generate(v5.begin(), v5.end(), std::rand);

    std::srand(unsigned(std::time(nullptr) / 2));
    std::vector<int> v6(100000);
    std::generate(v6.begin(), v6.end(), std::rand);

    //Складываем векторы
    start = std::chrono::steady_clock::now();
    std::transform(v5.begin(), v5.end(), v6.begin(), v5.begin(), std::plus<int>());

    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    t3 = elapsed_seconds.count();

    //Заполняем векторы 1000000
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> v7(1000000);
    std::generate(v7.begin(), v7.end(), std::rand);

    std::srand(unsigned(std::time(nullptr) / 2));
    std::vector<int> v8(1000000);
    std::generate(v8.begin(), v8.end(), std::rand);

    //Складываем векторы
    start = std::chrono::steady_clock::now();
    std::transform(v7.begin(), v7.end(), v8.begin(), v7.begin(), std::plus<int>());

    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    t4 = elapsed_seconds.count();

}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU.1251");

    //std::cout.unsetf(std::ios::scientific);
    std::cout.setf(std::ios::fixed);

    size_t count = std::thread::hardware_concurrency();
    std::cout << "Количество аппартных ядер - " << count << "\n\n";

    double t1,t2,t3,t4;

    std::thread thread1(sum_vec, std::ref(t1), std::ref(t2), std::ref(t3), std::ref(t4));
    
    if (thread1.joinable()) thread1.join();

    std::cout << "\t\t 1000 \t\t\t10000 \t\t\t100000 \t\t\t1000000 \n";
    std::cout << "1 потоков\t" << t1 << " s" << "\t\t" << t2 << " s" << "\t\t"
        << t3 << " s" << "\t\t" << t4 << " s\n";

    std::vector<std::thread> vec;

    //2 потока
    for (size_t i = 0; i < 2; i++) {
        vec.push_back(std::thread(sum_vec, std::ref(t1), std::ref(t2), std::ref(t3),
            std::ref(t4)));
    }
    for (auto& v : vec) {
        v.join();
    }
    vec.clear();
    std::cout << "2 потоков\t" << t1 << " s" << "\t\t" << t2 << " s" << "\t\t"
        << t3 << " s" << "\t\t" << t4 << " s\n";

    //4 потока
    for (size_t i = 0; i < 4; i++) {
        vec.push_back (std::thread (sum_vec, std::ref(t1), std::ref(t2), std::ref(t3),
            std::ref(t4)));
    }
    for (auto& v:vec) {
         v.join();
    }
    vec.clear();
    std::cout << "4 потоков\t" << t1 << " s" << "\t\t" << t2 << " s" << "\t\t"
        << t3 << " s" << "\t\t" << t4 << " s\n";

    //8 потоков
    for (size_t i = 0; i < 8; i++) {
        vec.push_back(std::thread(sum_vec, std::ref(t1), std::ref(t2), std::ref(t3),
            std::ref(t4)));
    }
    for (auto& v : vec) {
        v.join();
    }
    vec.clear();
    std::cout << "8 потоков\t" << t1 << " s" << "\t\t" << t2 << " s" << "\t\t"
        << t3 << " s" << "\t\t" << t4 << " s\n";

    //16 потоков
    for (size_t i = 0; i < 16; i++) {
        vec.push_back(std::thread(sum_vec, std::ref(t1), std::ref(t2), std::ref(t3),
            std::ref(t4)));
    }
    for (auto& v : vec) {
        v.join();
    }
    vec.clear();
    std::cout << "16 потоков\t" << t1 << " s" << "\t\t" << t2 << " s" << "\t\t"
        << t3 << " s" << "\t\t" << t4 << " s\n";

    return 0;
}
