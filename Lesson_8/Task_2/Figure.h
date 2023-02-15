#pragma once

class Figure {
public:
    Figure(int sides_count, std::string name);
    int get_sides();
    std::string get_name();
    virtual void print();
    ~Figure() {};
private:
    int sides_count{ 0 };
    std::string name{ "Фигура" };
};