#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <iterator>
#include <algorithm>


template<typename Iterator, typename Func>

void parallel_for_each(Iterator first, Iterator last, unsigned long const &min_per_thread, Func f) {

    unsigned long const length = std::distance(first, last);

    if (!length) return;

    if (length < (2 * min_per_thread)) {
        std::for_each(first, last, f);
    }
    else {

        Iterator const mid_point = first + length / 2;

        std::future<void> first_half =

            std::async(std::launch::async, &parallel_for_each<Iterator, Func>, first, mid_point, min_per_thread, f);

        parallel_for_each(mid_point, last, min_per_thread, f);

        first_half.get();
    }
}

std::mutex m;

template<typename T>
void f1(T& x) {
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    x= x* 7;
    std::unique_lock<std::mutex> guard(m);
    std::cout << x << " ";
}


int main(){
    
    unsigned long min_per_thread = 8;
    size_t size = 30;
    std::vector<double> v(size, 1);
    
    void(*poter)(double& v) = nullptr;
    poter = &f1;

    for (size_t i = 0; i < size; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    parallel_for_each(v.begin(), v.end(), min_per_thread, *poter);
    std::cout << std::endl;
}