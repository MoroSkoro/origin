#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <iterator>

#include "Transport.h"
#include "Camel.h"
#include "CamelFast.h"
#include "Krahotabl.h"
#include "Boots_AllTerrain.h"
#include "Broom.h"
#include "Eagle.h"
#include "Magic_carpet.h"
#include "Functions.h"




int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    
    int typeRace, option;
    int  reg =0;
    int exit = 1;
    double d = 0;
    std::string tRace;
    int number_of_participants = 0;
    std::vector < std::string > v_check;

    do {
        std::cout << "Добро пожаловать в гоночный симулятор!\n";
        std::cout << "1. Гонка для наземного транспорта\n";
        std::cout << "2. Гонка для воздушного транспорта\n";
        std::cout << "3. Гонка для наземного и воздушного транспорта\n";
        std::cout << "0. Выйти из игры\n";
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
        case 0:
            exit;
        }

        std::cout << "\nУкажите длину дистанции (должна быть положительна): ";
        std::cin >> d;
        std::cout << "\nДолжно быть зарегестрировано хотябы 2 транспортных средства\n";
        std::cout << "1. Зарегистрировать транспорт\n";
        std::cout << "2. Выбрать тип гонки\n";
        std::cout << "0. Новая игра\n";
        std::cout << "Выберите действие: ";
        std::cin >> option;
        int exit1 = 1;
        switch (option) {
        case 1:
            do {
                registration(d, tRace, typeRace, v_check, number_of_participants);
                std::cout << "\n1. Зарегистрировать транспорт\n";
                std::cout << "2. Начать гонку\n";
                std::cout << "Выберите действие: ";
                std::cin >> option;
                switch (option) {
                case 1:
                    break;
                case 2:
                    std::cout << "\nРезультаты гонки:\n";
                    std::cout << std::endl;

                    gonka(v_check, d);

                    exit1 = 0;
                    break;
                }

            } while (exit1);
            break;
        case 2:
            break;
        case 0:
            exit = 0;
            break;
        }

        std::cout << "\n1. Провести еще одну гонку\n";
        std::cout << "2. Выйти из игры\n";
        std::cout << "Выберите действие: ";
        std::cin >> option;
        switch (option) {
        case 1:
            //v1.clear();
            v_check.clear();
            number_of_participants = 0;
            break;
        case 2:
            exit = 0;
            break;
        }

    } while (exit!=0);
}
