#pragma once

class Counter {
private:
    int count;
public:
    Counter();
    Counter(int count);
    void increase();
    void decrease();
    void set_count(int count);
    int get_count();
    ~Counter() {};
};
