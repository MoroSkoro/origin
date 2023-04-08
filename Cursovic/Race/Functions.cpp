#include "Functions.h"


bool check(double& d, std::vector < std::string >& v_check, int& number_of_participants, int& reg) {
    bool good_reg = false;
    std::string target = "null";
    if (number_of_participants <= 7) {
        switch (reg) {
        case 1:
            target = "Ботинки-вездеходы";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\nБотинки-вездеходы уже зарегистрированы! Введите другое транспортное средство\n";
            }
            else {
                v_check.push_back("Ботинки-вездеходы");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 2:
            target = "Метла";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\nМетла уже зарегистрирована! Введите другое транспортное средство\n";
            }
            else {
                v_check.push_back("Метла");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 3:
            target = "Верблюд";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\nВерблюд уже зарегистрирован! Введите другое транспортное средство\n";
            }
            else {
                v_check.push_back("Верблюд");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 4:
            target = "Кентавр";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\nКентавр уже зарегистрирован! Введите другое транспортное средство\n";
            }
            else {
                v_check.push_back("Кентавр");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 5:
            target = "Орел";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\nОрел уже зарегистрирован! Введите другое транспортное средство\n";
            }
            else {
                v_check.push_back("Орел");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 6:
            target = "Верблюд-быстроход";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\nВерблюд-быстроход уже зарегистрирован! Введите другое транспортное средство\n";
            }
            else {
                v_check.push_back("Верблюд-быстроход");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 7:
            target = "Ковер самолет";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\nКовер самолет уже зарегистрирован! Введите другое транспортное средство\n";
            }
            else {
                v_check.push_back("Ковер самолет");
                number_of_participants++;
                good_reg = true;
            }
            break;
        }
    }
    else { std::cout << "\n" << "Максимально возможное число участников зарегестрированы! Начните гонку!\n"; }
    return good_reg;
}
//проверка

void print_check(double& d, std::vector < std::string >& v_check, int& number_of_participants, int& reg) {
    if (check(d, v_check, number_of_participants, reg)) {
        for (std::vector<std::string>::iterator iter = v_check.begin(); iter != v_check.end(); iter++)
        {
            if (iter != (v_check.end() - 1)) {
                std::cout << (*iter) << ", ";
            }
            else { std::cout << (*iter) << " - "; }
        }
        std::cout << "успешно зарегистрированны!" << std::endl;
        std::cout << std::endl;
    }
}
//распечатка

void registration(double& d, std::string& tRace, int typeRace, std::vector < std::string >& v_check, int& number_of_participants) {
    int exit = 1;
    int reg;
    while (exit != 0) {
        std::cout << "\n" << tRace << " Расстояние: " << d << std::endl;
        std::cout << "1. Ботинки-вездеходы\n";
        std::cout << "2. Метла\n";
        std::cout << "3. Верблюд\n";
        std::cout << "4. Кентавр\n";
        std::cout << "5. Орел\n";
        std::cout << "6. Верблюд-быстроход\n";
        std::cout << "7. Ковер самолет\n";
        std::cout << "0. Закончить регистрацию\n";
        std::cout << "\nВыберите транспорт или 0 для окончания процесса регистрации: ";
        std::cin >> reg;
        switch (reg) {
        case 1:
            if (typeRace == 2) {
                std::cout << "\nПопытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 2:
            if (typeRace == 1) {
                std::cout << "\nПопытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {

                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 3:
            if (typeRace == 2) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 4:
            if (typeRace == 2) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 5:
            if (typeRace == 1) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 6:
            if (typeRace == 2) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 7:
            if (typeRace == 1) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 0:
            if (number_of_participants < 2) {
                std::cout << "\nДолжно быть зарегестрировано хотябы 2 транспортных средства." << std::endl;
                std::cout << "Зарегистрируйте не менее 2 транспортных средства." << std::endl;
            }
            else { exit = 0; }
        }
    }
}


bool sortBy_t(Transport l_t, Transport r_t) {
    return (l_t.get_t() < r_t.get_t());
}


void gonka ( std::vector<std::string> &v_check, double& d){

    std::vector<Transport> v1;
    std::string target = "null";
    for (std::vector<std::string>::iterator iter = v_check.begin(); iter != v_check.end(); iter++)
    {
        target = *iter;
        if (target == "Ботинки-вездеходы") {
            Boots_AllTerrain boots(d);
            v1.push_back(boots);
            
        }
        if (target == "Метла") {
            Broom broom(d);
            v1.push_back(broom);
        }
        if (target == "Верблюд") {
            Camel camel(d);
            v1.push_back(camel);
        }
        if (target == "Кентавр") {
            Krahotabl krahotabl(d);
            v1.push_back(krahotabl);
        }
        if (target == "Орел") {
            Eagle eagle(d);
            v1.push_back(eagle);
        }
        if (target == "Верблюд-быстроход") {
            CamelFast camelFast(d);
            v1.push_back(camelFast);
        }
        if (target == "Ковер самолет") {
            Magic_carpet magic_carpet(d);
            v1.push_back(magic_carpet);
        }
        
    }

    std::sort(v1.begin(), v1.end(), sortBy_t);
    int i = 1;
    for (std::vector<Transport>::iterator iter1 = v1.begin(); iter1 != v1.end(); iter1++)
    {
        std::cout << i << ". " << iter1->get_name() << ". Время: " << iter1->get_t() << "\n";
        std::cout << std::endl;
        i++;
    }
}