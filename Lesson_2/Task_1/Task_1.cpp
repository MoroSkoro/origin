// Task_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");

    enum months {
        январь = 1,
        февраль,
        март,
        апрель,
        май,
        июнь,
        июль,
        август,
        сентябрь,
        октябрь,
        ноябрь,
        декабрь
    };
    months month_true;
    int month;
    
    do {
        std::cout << "Введите номер месяца: ";
        std::cin >> month;
        month_true = static_cast<months> (month);
        switch (month_true) {
            case 1:
                std::cout << "январь \n";
                break;
            case 2:
                std::cout << "февраль \n";
                break;
            case 3:
                std::cout << "март \n";
                break;
            case 4:
                std::cout << "апрель \n";
                break;
            case 5:
                std::cout << "май \n";
                break;
            case 6:
                std::cout << "июнь \n";
                break;
            case 7:
                std::cout << "июль \n";
                break;
            case 8:
                std::cout << "август \n";
                break;
            case 9:
                std::cout << "сентябрь \n";
                break;
            case 10:
                std::cout << "октябрь \n";
                break;
            case 11:
                std::cout << "ноябрь \n";
                break;
            case 12:
                std::cout << "декабрь \n";
                break;
            default:
                if (month != 0) {
                    std::cout << "Неправильный номер месяца! \n";
                }
                break;
        }
    }
    while (month != 0);
    std::cout << "До свидания!";
}
