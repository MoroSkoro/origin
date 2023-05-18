#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
class simple_functor {
    size_t m_counter;
    T m_sum;
public:
    simple_functor() : m_counter{ 0 }, m_sum{ 0 } {}
        void operator()(const T& a) {
            int d = static_cast<int>(a);
            if (a - d == 0) {
                if ((d % 3) == 0) {
                    m_counter++;
                    m_sum += a;
                }
            }
        }
        T get_sum() { return m_sum; };
        size_t get_count() { return m_counter; };
};

int main(){
    std::vector<double> vec{ 4, 1, 3, 6, 25, 54 };
    simple_functor<double> sf;
    
    std::cout << "[IN]: ";
    for_each(vec.begin(), vec.end(), [](double i) {std::cout << i << " "; });
    std::cout << "\n\n";

    std::vector<double>::iterator Iter1;
    for (Iter1 = vec.begin(); Iter1 != vec.end(); Iter1++) {
        sf(*Iter1);
    };

    std::cout << "[OUT]: get_sum() = " << sf.get_sum() << "\n";
    std::cout << "[OUT]: get_count() = " << sf.get_count() << "\n";
}