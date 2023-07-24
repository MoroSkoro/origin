#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <algorithm>
#include <mutex>
#include <atomic>


void fill_vec(std::vector<int>& v1, std::vector<int>& v2, size_t& const calculation_length){
    //Заполняем векторы
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> v1_(calculation_length);
    std::generate(v1_.begin(), v1_.end(), std::rand);
    v1 = v1_;

    std::srand(unsigned(std::time(nullptr) / 2));
    std::vector<int> v2_(calculation_length);
    std::generate(v2_.begin(), v2_.end(), std::rand);
    v2 = v2_;
}

static void SetPosition(int x, int y)
{
    COORD point;
    point.X = x;
    point.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

using namespace std::chrono_literals;

std::mutex m;
static std::atomic_int num{1};
std::atomic<int>* pt(& num);


void sum_vec(std::vector<int>& v1, std::vector<int>& v2, size_t& const calculation_length, size_t& const n) {
    
    std::unique_lock<std::mutex> lk(m);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | num + 3));
    
    if (num == 1) { SetPosition(0, num * 2); }
    else { SetPosition(0, num * 6-4); };
    
    std::cout << "Поток " << std::atomic_fetch_add(pt, 1) << std::endl;
    std::cout <<"id потока "<< std::this_thread::get_id() << std::endl;
    //lk.unlock();
    auto start = std::chrono::steady_clock::now();
    size_t width_thread = calculation_length / n;
    size_t vec_begin = calculation_length - width_thread*(n-num+2);
    std::cout << "vec_begin = " << vec_begin << std::endl;

    float progress = 0.0;
    size_t j = 0;
    //std::unique_lock<std::mutex> lk1(m);
    while (j < width_thread-3) {
    //std::transform(v1.begin(), v1.end(), v2.begin(), v1.begin(), std::plus<int>());
     
        v1[vec_begin] = v1[vec_begin] + v2[vec_begin];

        int barWidth = 80;
       //std::this_thread::sleep_for(5ms);
        std::cout << "[";
        progress = (static_cast<float> (j) / width_thread);
        int pos = barWidth*progress;
        for (int i = 0; i <= barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int((static_cast<float>(pos)/80)*100+2) << " %\r";
        std::cout.flush();
        ++vec_begin;
        j++;
    }
    std::cout << std::endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    double t1 = elapsed_seconds.count();
    std::cout << "Затраченное время: " << t1 << "\n\n";
    std::cout << std::endl<< std::endl;
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

    size_t n = 8;
    size_t calculation_length = 8000;
    std::vector<int> v1, v2 (calculation_length);

    fill_vec(v1, v2, calculation_length);

    std::vector<std::thread> vec;
    
    for (size_t i = 0; i < n; i++) {
        vec.push_back(std::thread(sum_vec, std::ref(v1), std::ref(v2),
            std::ref(calculation_length), std::ref(n))); 
    }
    for (auto& v : vec) {
        v.join();
    }
    
    return 0;
}