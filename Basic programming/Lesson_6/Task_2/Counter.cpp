#include "Counter.h"

Counter::Counter() { count = 1; };
Counter::Counter(int count) :count{ count }{}
    void Counter::increase() { ++count; }
    void Counter::decrease() { --count; }
    void Counter::set_count(int count) {
        this->count = count;
    }
    int Counter::get_count() {
        return count;
    }