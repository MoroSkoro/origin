#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <memory>

using namespace std::chrono_literals;

static std::atomic<bool> stop(false);

void clients(std::atomic_int& count,  std::atomic_int& max_count) {
    
    auto count_ptr = &count;
    auto max_count_ptr = &max_count;

    /*Подскажите, пожалуйста, как работает atomic_compare_exchange_weak? В мануалах написано, что нужно передавать
        указатели на сравниваемые значения. А запустить удалось только через shared_ptr/
        И не понятно, что с чем сравнивается?
    std::shared_ptr<std::atomic_int> count_shptr{count_ptr};
    std::shared_ptr<std::atomic_int> max_count_shptr{max_count_ptr};
    std::atomic_compare_exchange_weak(&count_shptr, &count_shptr, count_shptr);*/
     
     while (count.load(std::memory_order_relaxed) < max_count){   // можно использовать обычные операторы сравнения для атомических объектов?
        //std::this_thread::sleep_for(1000ms);
        std::atomic_fetch_add_explicit(count_ptr, 1, std::memory_order_seq_cst);
        std::cout << "В очереди клиент: " << count << std::endl;
        if (count.load(std::memory_order_relaxed) == max_count) stop.store(true);
     } 
}

void cashier(std::atomic_int& count) {
    auto count_ptr = &count;

    while (!stop.load()) {
        //std::this_thread::sleep_for(2000ms);
        if (count.load(std::memory_order_relaxed) != 0)
            std:atomic_fetch_sub_explicit(count_ptr, 1, std::memory_order_seq_cst); //Почему не работают такие конструкции: count.atomic_fetch_sub( 1, std::memory_order_relaxed);
        std::cout << "\t В очереди: " << count << std::endl;
    }

    do {
       // std::this_thread::sleep_for(2000ms);
        if (count.load(std::memory_order_relaxed) != 0) std::atomic_fetch_sub(count_ptr, 1);
        std::cout << "Прием окончен! Осталось в очереди: " << count << std::endl;
    } while (count.load(std::memory_order_relaxed) != 0);
}

//size_t count = 0; //Можно сделать эту переменную глобальной для лучшего обращения потоков или все равно?

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru-RU.1251");

    std::atomic_int count;
    count.store(0);
    std::atomic_int max_count;
    max_count.store(5);

    std::thread t1(clients, std::ref(count), std::ref(max_count));
    std::thread t2(cashier, std::ref(count));

    t1.join();
    t2.join();

    

    return 0;
}
