#include <iostream>
#include <windows.h>
#include <string>

struct address {
    std::string country;
    std::string city;
    std::string street;
    int house_number;
    int apartment;
    int index;
};

void operation(address& recipient) {
    static int id = 1;
    std::cout << std::endl;
    std::cout << "Получатель: " << id << std::endl;
    std::cout << "Страна: " << recipient.country << std::endl;
    std::cout << "Город: " << recipient.city << std::endl;
    std::cout << "Улица: " << recipient.street << std::endl;
    std::cout << "Номер дома: " << recipient.house_number << std::endl;
    std::cout << "Номер квартиры: " << recipient.apartment << std::endl;
    std::cout << "Индекс: " << recipient.index << std::endl;
    std::cout << std::endl;
    id++;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    address* recipients = new address[10];
    
    /*for (int id = 0; id < 2; id++) {
        std::cout << "Введите страну проживания: ";
        std::cin >> recipients[id].country;
        std::cout << "Введите город: ";
        std::cin.ignore();
        getline(std::cin, recipients[id].city);
        std::cout << "Введите улицу: ";
        getline(std::cin, recipients[id].street);
        std::cout << "Введите номер дома: ";
        std::cin >> recipients[id].house_number;
        std::cout << "Введите номер квартиры: ";
        std::cin >> recipients[id].apartment;
        std::cout << "Введите индекс: ";
        std::cin >> recipients[id].index;
        std::cout << std::endl;
    }*/

    recipients[0] = {"Россия", "Москва", "Бульвар Рокосовского", 3746, 237, 777777};
    recipients[1] = { "США", "Нью-Йорк", "Уолт Стрит", 5678, 432, 666666};
    recipients[2] = { "Никарагуа", "Манагуа", "Чегевары", 546, 390, 333333};
    for (int id = 0; id < 3; id++) {
        operation(recipients[id]);
    }
    delete[] recipients;
}