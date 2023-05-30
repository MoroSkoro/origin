#include <iostream>

using namespace std;

template<typename T>
class unique_potr {
private:
    using type = remove_extent_t<T>;

protected:
    type* ptr = nullptr;

public:
    unique_potr() {};

    explicit unique_potr(T* ptr) {
        this->ptr = ptr;
        ptr = nullptr;
    }

    unique_potr(unique_potr<T>&& other) noexcept
        : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    T& operator*() const {
        return *unique_potr<T>::ptr;
    }

    unique_potr(const unique_potr& other) = delete;
    unique_potr& operator=(const unique_potr& other) = delete;

    type* release() {
        type* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset() {
        if (ptr != nullptr) {
            if (is_array_v<T>)
                delete[] ptr;
            else
                delete ptr;
            ptr = nullptr;
        }
    }

    void reset(type* item) noexcept {
        reset();
        ptr = item;
    }

    void swap(unique_potr<T>& other) noexcept {
        type* tmp = ptr;
        ptr = other.ptr;
        other.ptr = tmp;
    }

    operator bool() {
        return ptr;
    }

    type* get() {
        return ptr;
    }

    ~unique_potr() { reset();}
};

int main() {
    unique_potr<int> a(new int(1));
    cout << "a = " << *a << endl;
    cout << "a = nulptr " << bool(a) << endl;

    unique_potr<int> b;

    b.swap(a);
    cout << "b = " << *b << endl;

    b.reset();
    cout << "b = nulptr " << bool(b) << endl;

    a.release();
    cout << "a = nulptr " << bool(a) << endl;

    return 0;
}