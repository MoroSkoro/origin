#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <memory>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <conio.h>

using namespace std::chrono_literals;

static std::atomic<bool> flg(false);
static std::atomic<int> task(0);
std::mutex m;

void func1() {
    std::this_thread::sleep_for(200ms);
    std::lock_guard l(m);
    std::cout << "Working funcion: " << __FUNCTION__ << "\n";
}

void func2() {
    std::this_thread::sleep_for(200ms);
    std::lock_guard l(m);
    std::cout << "Working funcion: " << __FUNCTION__ << "\n";
}

void func_sleep() {
    std::this_thread::sleep_for(500ms);
}

class safe_queue {

    std::queue<std::function<void()>> task_que;
    std::mutex _m;
    std::mutex _m1;

public:
    friend class thread_pool;

    safe_queue() {}
    ~safe_queue(){}

private:

    void push(std::function<void()> f) {
       _m.lock();
       task_que.push(f);
       _m.unlock();
    }

    std::function<void()> pop() {
        std::function<void()> elem;
        _m1.lock();
        if (!task_que.empty()) {
            elem = task_que.front();
            task_que.pop();
            task++;
        }
        else elem = func_sleep;
        _m1.unlock();
        return elem;
    }

};

class thread_pool {

    std::mutex _m;
    std::vector<std::thread> th_v;
    size_t _n;

public:

    thread_pool(size_t& num_cores, safe_queue& que, size_t& n): _n(n) {
        for (int i = 0; i < num_cores; i++) {
            th_v.push_back(std::thread(&thread_pool::work, this, std::ref(que)));
        }
    }
    ~thread_pool(){
        for (auto& th : th_v){
            if (th.joinable()) th.join();
        }
    }

private:

    void work(safe_queue& que) {
        _m.lock();
        std::cout << "work id: " << std::this_thread::get_id() << std::endl;
        _m.unlock();
        std::function<void()> f;
        while (!flg) {
            f = que.pop();
            f();
            if (task == 2 * _n) flg = true;
        }
        
    }

public:
    void submit(safe_queue& que, std::function<void()> f) {
        que.push(f);
    }
};

void addF1(size_t& n, safe_queue& que, thread_pool& thr) {
    for (int i = 0; i < n; i++) {
         std::this_thread::sleep_for(1s);
         thr.submit(que, func1);
    }
}
    
void addF2(size_t& n, safe_queue& que, thread_pool& thr) {
    for (int i = 0; i < n; i++) {
         std::this_thread::sleep_for(1s);
         thr.submit(que, func2);
    }
 }

int main(){

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru-RU.1251");

    size_t num_cores = std::thread::hardware_concurrency();
    std::cout << "Количество аппартных ядер - " << num_cores << "\n\n";
    size_t n{ 7 };
    safe_queue que;
    thread_pool thr(num_cores, que, n);

    std::thread th1(addF1, std::ref(n), std::ref(que), std::ref(thr));
    std::thread th2(addF2, std::ref(n), std::ref(que), std::ref(thr));
    if (th1.joinable()) th1.join();
    if (th2.joinable()) th2.join();

    _getch();
    
    return 0;
}