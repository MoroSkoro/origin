// Task_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");

    enum months {
        январь =  1,
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
        case months::январь:
                std::cout << "январь \n";
                break;
            case months::февраль:
                std::cout << "февраль \n";
                break;
            case months::март:
                std::cout << "март \n";
                break;
            case months::апрель:
                std::cout << "апрель \n";
                break;
            case months::май:
                std::cout << "май \n";
                break;
            case months::июнь:
                std::cout << "июнь \n";
                break;
            case months::июль:
                std::cout << "июль \n";
                break;
            case months::август:
                std::cout << "август \n";
                break;
            case months::сентябрь:
                std::cout << "сентябрь \n";
                break;
            case months::октябрь:
                std::cout << "октябрь \n";
                break;
            case months::ноябрь:
                std::cout << "ноябрь \n";
                break;
            case months::декабрь:
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
