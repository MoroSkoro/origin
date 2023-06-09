#include <iostream>
#include <windows.h>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>

#include <fstream>
#include <functional>
#include <utility>
#include <string_view>
#include "Trim.h"
#include "additional_functions.h"
#include "Pars.h"


typedef  std::map<std::string, std::string> Entries;
typedef  std::map<std::string, Entries> IniData;

int main(){

    SetConsoleCP(1251);//1251
    SetConsoleOutputCP(1251);
    //setlocale(LC_ALL, ".utf8"); //Russian .utf8
    setlocale(LC_ALL, "ru_Ru.UTF-8");
    //setlocale(LC_ALL, "ru_RU.CP866");
    //setlocale(LC_ALL, "Russian");
    //system("chcp 1251");//Установка кодовой страницы

    std::string sec_val;
    
    try{
        ini_parser parser("file.ini");
    
    std::cout << "Введите название секцие и параметра через точку без пробелов (пример: Section3.Mode):\n";
   /*
        Подскажите, пожалуйста, как настроить кодировку?
        При данной настройке -ru_Ru.UTF-8- не выводится русский текст в консоль.
        При настройке -Russian- текст в консольвыводится, но русский текст из файла выводится абракадаброй.
   */
    std::cout << "Inter sector\n";
    std::cin >> sec_val;

    auto value = parser.get_value<std::string>(sec_val);
    std::cout << sec_val << " = " << value;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}