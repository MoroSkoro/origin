
#include <iostream>
#include <fstream>
//#include <windows.h>
#include <string>

#define  DEF_GETSET(type, name) \
    private: type name; \
    public:  type get_##name() { return name; } \
             void set_##name(type val) { name = val; }

class Address {
    DEF_GETSET(std::string, city);
    DEF_GETSET(std::string, street);
    DEF_GETSET(int, house_number);
    DEF_GETSET(int, apartment);

public:
    Address() {
        city = "city";
        street = "street";
        house_number = 1;
        apartment = 1;
    }
    void set_address(std::string city, std::string street, int house_number, int apartment) {
        this->city = city;
        this->street = street;
        this->house_number = house_number;
        this->apartment = apartment;
    }

    std::string get_output_address() {
        return (city + ", " + street + ", " + std::to_string(house_number) + ", " + std::to_string(apartment));
    }
    ~Address() {};

};

void sort(Address* recipients, int size) {
    for (int i = 0; i < size; i++) {
        bool flag = true;
        for (int j = 0; j < size - (i + 1); j++) {
            if (recipients[j].get_city() < recipients[j + 1].get_city()) {
                flag = false;
                std::swap(recipients[j], recipients[j + 1]);
            }
        }
        if (flag) {
            break;
        }
    }
}

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::string city;
    std::string street;
    int house_number;
    int apartment;
    int N;
    
    std::ifstream fin("in.txt");
    if (!fin.is_open()) {
        std::cout << "Не получилось открыть файл in.txt" << std::endl;
        return 1;
    }
    fin >> N;
    Address* recipients = new Address[N];
    for (int i = 0; i < N; i++) {
        fin >> city;
        fin >> street;
        fin >> house_number;
        fin >> apartment;
        recipients[i].set_address(city, street, house_number, apartment);
    }
    fin.close();

    sort(recipients, N);

    std::ofstream fout("out.txt");
    if (!fout.is_open()) {
        std::cout << "Не получилось открыть файл out.txt" << std::endl;
        return 1;
    }
    fout << N << std::endl;
    for (int i = N - 1; i >= 0; i--) {
        fout << recipients[i].get_output_address() << std::endl;
    }
    fout.close();

    delete[] recipients;
}
