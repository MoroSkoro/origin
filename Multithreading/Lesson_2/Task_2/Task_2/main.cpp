#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>


using namespace std::chrono_literals;

std::mutex m;

void fProgressBar(size_t i, size_t barWidth) {
    auto start = std::chrono::steady_clock::now();

    size_t x = 10;
    const size_t y = (i+1)*3;
    size_t j = 0;
        

    //Порядковый номер потока
    m.lock();
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(0), static_cast<SHORT>(y) });

      std::cout << "Поток " << i + 1;
    m.unlock();

    //id потока
    m.lock();
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(0), static_cast<SHORT>(y+1) });

      std::cout << "id потока: " << std::this_thread::get_id()<<".";
    m.unlock();
    
    //Начало пргрессбар
    m.lock();
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(x), static_cast<SHORT>(y) });

      std::cout << "[";
    m.unlock();
    
    while (j < barWidth) {
        ++x;
        std::this_thread::sleep_for(100ms);
        m.lock();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
            { static_cast<SHORT>(x), static_cast<SHORT>(y) });

        std::cout << "=";
        m.unlock();
        j++;
    }

    //Конец прогрессбар
    m.lock();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(x+1), static_cast<SHORT>(y) });

    std::cout << "] End";
    m.unlock();
    
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    double t1 = elapsed_seconds.count();
    
    //Затраченное время
    m.lock();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(18), static_cast<SHORT>(y+1) });

    std::cout << "Затраченное время: " << t1;
    m.unlock();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU.1251");

    size_t n = 5;
    size_t calculation_length = 40;
    std::vector<std::thread> vec(n);
        
    for (size_t i = 0; i < n; i++) {
        vec[i] = std::thread(fProgressBar, i, calculation_length);
    }
    for (auto& v : vec) {
        v.join();
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | 15));
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(0), static_cast<SHORT>(n*3+2) });
    std::cout << "\n";
    return 0;
}