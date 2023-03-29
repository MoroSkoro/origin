
#include <iostream>
#include <string>
#include <windows.h>
#include "Transport.h"
#include "Camel.h"
#include "CamelFast.h"
#include "Centaur.h"
#include "Boots_AllTerrain.h"

//template <typename T >
template < class T > 
void check(std::string arr[], int& number_of_participants, T& transport) {
    if (number_of_participants < 7) {
        bool is_present = false;
        for (int i = 0; i <= number_of_participants; i++) {
            if (arr[i] == transport.get_name()) {
                is_present = true;
                break;
            }
        }
        if (is_present) {
            std::cout << transport.get_name() << " уже зарегистрирован!\n";
        }
        else {
            arr[number_of_participants] = transport.get_name();
            number_of_participants++;
            std::cout << arr[number_of_participants] << " успешно зарегистрированы!\n";
        }
    }
    else { std::cout << "Максимально возможное число участников зарегестрированы!"; }
}


void registration(double d, std::string &tRace, int typeRace) {
    int exit = 1;
    int reg;
    std::string arr[6];
    int number_of_participants = 0;
    while (exit != 0) {
        std::cout << tRace << " Расстояние: " << d << std::endl;
        std::cout << "1. Ботинки-вездеходы\n";
        std::cout << "2. Метла\n";
        std::cout << "3. Верблюд\n";
        std::cout << "4. Кентавр\n";
        std::cout << "5. Орел\n";
        std::cout << "6. Верблюд-быстроход\n";
        std::cout << "7. Ковер самолет\n";
        std::cout << "0. Закончить регистрацию\n";
        std::cout << "Выберите транспорт или 0 для окончания процесса регистрации: ";
        std::cin >> reg;
        switch (reg) {
        case 1:
            if (typeRace == 2) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                Boots_AllTerrain boots(d);
                check(arr, number_of_participants, boots);
            }
            break;
        case 2:
            if (typeRace == 1) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                //Boots_AllTerrain boots(d);
                //arr[number_of_participants] = boots.get_name();
                //number_of_participants++;
                //std::cout << arr[number_of_participants] << " успешно зарегистрированы!\n";
            }
            break;
        case 3:
            if (typeRace == 2) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                Camel camel(d);
                check(arr, number_of_participants, camel);
                /*arr[number_of_participants] = camel.get_name();
                number_of_participants++;
                std::cout << arr[number_of_participants] << " успешно зарегистрирован!\n";*/
            }
            break;
        case 4:
            if (typeRace == 2) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                Сentaur centaur(d);
                check(arr, number_of_participants, centaur);
                
            }
            break;
        case 5:
            if (typeRace == 1) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                /* eagle eagle(d);
                 arr[number_of_participants] = eagle.get_name();
                 number_of_participants++;
                 std::cout << arr[number_of_participants] << " успешно зарегистрирован!\n";*/
            }
            break;
        case 6:
            if (typeRace == 2) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                CamelFast сamelFast(d);
                check(arr, number_of_participants, сamelFast);
                /*arr[number_of_participants] = сamelFast.get_name();
                number_of_participants++;
                std::cout << arr[number_of_participants] << " успешно зарегистрирован!\n";*/
            }
            break;
        case 7:
            if (typeRace == 1) {
                std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
            }
            else {
                /*Carpet_plane Carpet_plane(d);
                arr[number_of_participants] = Carpet_plane.get_name();
                number_of_participants++;
                std::cout << arr[number_of_participants] << " успешно зарегистрирован!\n";*/
            }
            break;
        case 0:
            exit = reg;
            break;
        }
    }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    
    int typeRace, d, option;
      int  reg =0;
    int exit = 1;
    std::string tRace;
    std::string arr[6];
    int number_of_participants = 0;

    do {
        std::cout << "Добро пожаловать в гоночный симулятор!\n";
        std::cout << "1. Гонка для наземного транспорта\n";
        std::cout << "2. Гонка для воздушного транспорта\n";
        std::cout << "3. Гонка для наземного и воздушного транспорта\n";
        std::cout << "Выберите тип гонки: ";
        std::cin >> typeRace;

        switch (typeRace) {
        case 1:
            tRace = "Гонка для наземного транспорта";
            break;
        case 2:
            tRace = "Гонка для воздушного транспорта";
            break;
        case 3:
            tRace = "Гонка для наземного и воздушного транспорта";
            break;
        }

        std::cout << "Укажите длину дистанции (должна быть положительна): \n";
        std::cin >> d;
        std::cout << "Должно быть зарегестрировано хотябы 2 транспортных средства\n";
        std::cout << "1. Зарегистрировать транспорт\n";
        std::cout << "2. Выбрать тип гонки\n";
        std::cout << "0. Выйти из игры\n";
        std::cout << "Выберите действие: ";
        std::cin >> option;

        switch (option) {
        case 1:
            registration(d, tRace, typeRace);
            break;
        case 2:
            break;
        case 0:
            exit = 0;
            break;
        }

    } while (exit!=0);
}
