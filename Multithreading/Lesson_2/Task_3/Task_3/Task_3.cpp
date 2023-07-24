#include <iostream>
#include <windows.h>
#include <thread>
#include <mutex>


class Data {
public:
    std::mutex m;
    int a;
    std::string b;
    //std::atomic_flag flag = ATOMIC_FLAG_INIT;

    Data(int a, std::string b) :a{ a }, b{b} {};
    Data() {
        a = 0;
        b = "nul";
    }

};

void swap1(Data& x, Data& y) {
    Data middle;
    {std::lock(x.m, middle.m);
    std::lock_guard<std::mutex> lk1(x.m, std::adopt_lock);
    std::lock_guard<std::mutex> lk2(middle.m, std::adopt_lock);
    middle.a = x.a;
    middle.b = x.b;
    }

    {std::lock(y.m, x.m);
    std::lock_guard<std::mutex> lk1(x.m, std::adopt_lock);
    std::lock_guard<std::mutex> lk2(y.m, std::adopt_lock);
    x.a = y.a;
    x.b = y.b;
    }

    {std::lock(y.m, middle.m);
    std::lock_guard<std::mutex> lk1(middle.m, std::adopt_lock);
    std::lock_guard<std::mutex> lk2(y.m, std::adopt_lock);
    y.a = middle.a;
    y.b = middle.b;
    }
    
}

void swap2(Data& x, Data& y) {
    Data middle;
    std::lock(x.m, y.m, middle.m);
    std::lock_guard<std::mutex> lk1(x.m, std::adopt_lock);
    std::lock_guard<std::mutex> lk2(y.m, std::adopt_lock);
    std::lock_guard<std::mutex> lk3(middle.m, std::adopt_lock);
    
    middle.a = x.a;
    middle.b = x.b;
    
    x.a = y.a;
    x.b = y.b;
    
    y.a = middle.a;
    y.b = middle.b;

    std::cout << "\nЗначения после обмена:\n";
    std::cout << "a.a = " << x.a << ", a.b = " << x.b << std::endl;
    std::cout << "b.a = " << y.a << ", b.b = " << y.b << std::endl;
}

void swap3(Data& x, Data& y) {
    Data middle;
    
    std::unique_lock<std::mutex> lk1(x.m, std::defer_lock);
    std::unique_lock<std::mutex> lk2(y.m, std::defer_lock);
    std::unique_lock<std::mutex> lk3(middle.m, std::defer_lock);
    std::lock(lk1, lk2, lk3);
    
    middle.a = x.a;
    middle.b = x.b;

    x.a = y.a;
    x.b = y.b;

    y.a = middle.a;
    y.b = middle.b;

    std::cout << "\nЗначения после обмена:\n";
    std::cout << "a.a = " << x.a << ", a.b = " << x.b << std::endl;
    std::cout << "b.a = " << y.a << ", b.b = " << y.b << std::endl;

}

void swap4(Data& x, Data& y) {
    Data middle;

    std::scoped_lock lk(x.m, y.m, middle.m);
    
    middle.a = x.a;
    middle.b = x.b;

    x.a = y.a;
    x.b = y.b;

    y.a = middle.a;
    y.b = middle.b;

    std::cout << "\nЗначения после обмена:\n";
    std::cout << "a.a = " << x.a << ", a.b = " << x.b << std::endl;
    std::cout << "b.a = " << y.a << ", b.b = " << y.b << std::endl;

}




int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU.1251");

    size_t count = std::thread::hardware_concurrency();
    std::cout << "Количество аппартных ядер - " << count << "\n\n";

    Data a;
    Data b(3, "once");

    std::cout << "Исходные значения:\n";
    std::cout << "a.a = " << a.a << ", a.b = " << a.b << std::endl;
    std::cout << "b.a = " << b.a << ", b.b = " << b.b << std::endl;
    
    std::thread th1_1(swap1, std::ref(a), std::ref(b));
    std::thread th2_1(swap1, std::ref(a), std::ref(b));
    th1_1.join();
    th2_1.join();
    std::cout << "\nЗначения после обмена:\n";
    std::cout << "a.a = " << a.a << ", a.b = " << a.b << std::endl;
    std::cout << "b.a = " << b.a << ", b.b = " << b.b << std::endl;

    std::thread th1_2(swap2, std::ref(a), std::ref(b));
    std::thread th2_2(swap2, std::ref(a), std::ref(b));
    th1_2.join();
    th2_2.join();
    /*std::cout << "\nЗначения после обмена:\n";
    std::cout << "a.a = " << a.a << ", a.b = " << a.b << std::endl;
    std::cout << "b.a = " << b.a << ", b.b = " << b.b << std::endl;*/

    std::thread th1_3(swap3, std::ref(a), std::ref(b));
    std::thread th2_3(swap3, std::ref(a), std::ref(b));
    th1_3.join();
    th2_3.join();

    std::thread th1_4(swap4, std::ref(a), std::ref(b));
    std::thread th2_4(swap4, std::ref(a), std::ref(b));
    th1_4.join();
    th2_4.join();
   
    return 0;
}
