#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;

void clients(size_t& count, const size_t& max_count) {
    do{
        std::this_thread::sleep_for(1000ms);
        ++count;
        std::cout << "В очереди клиент: " << count << std::endl;
    }
    while (count <= max_count);

}

void cashier(size_t& count, const size_t& max_count) {
    do {
        std::this_thread::sleep_for(2000ms);
        if (count != 0) count--;
        std::cout << "\t В очереди: " << count << std::endl;
    } while (count!=max_count);

    do {
        std::this_thread::sleep_for(2000ms);
        if (count != 0) count--;
        std::cout << "В очереди: " << count << std::endl;
    } while (count != 0);
}

//size_t count = 0; //Можно сделать эту переменную глобальной для лучшего обращения потоков или все равно?

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);  
    setlocale(LC_ALL, "ru-RU.1251");

    size_t count = 0;
    size_t max_count = 5;

    std::thread t1(clients, std::ref(count), std::ref(max_count));
    std::thread t2(cashier, std::ref(count), std::ref(max_count));

        t1.join();
        t2.join();

    return 0;
}
