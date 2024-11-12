#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include "MyList.h"

int main()
{
    char* p;
    const char delim[] = " .!?,;:\"/0123456789@#$%^&*()<>{}[]~+-\_=\\";
    char* next_token;
    std::string line;
    std::string all_text;
    MyList Lst;

    std::ofstream log("Logfile.txt", std::ios::app);

    try {
        //log.exceptions(ifstream::eofbit);
        if (log.is_open()) {} else throw std::exception("Неудалось открыть файл Logfile.txt!");;
        std::ifstream in("WordsList.txt");
        if (in.is_open())
        {
            std::string input;
            while (getline(in, input))
            {
                all_text += (" " + input);
            }
        }
        else throw std::exception("Неудалось открыть файл WordsList.txt!");
        in.close();

        {
            auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            char str[50];
            ctime_s(str, sizeof(str), &timenow);
            log << std::endl << "\n * ****************************************************\n";
            log << str << std::endl;
            log << "Успешно открыт файл WordsList.txt.\nТекст считан успешно.\n";
        }

        std::string low_all_text;
        for (auto c : all_text) { low_all_text += std::tolower(c); }
        std::pair<std::string, size_t> para = { "1", 1 };
        p = strtok_s(const_cast<char*>(low_all_text.c_str()), delim, &next_token);
        while (p != 0) {

            para.first = p;
            Lst.push(para);
            p = strtok_s(NULL, delim, &next_token);
        }

        Lst.removeDuplicates();
        Lst.quickSort();
        Lst.quickSort_by_first();
        Lst.printList();

        std::ofstream out("ResultPairs.txt");
        if (out.is_open())
        {
            Lst.printListInFile(out);
        }
        else throw std::exception("Неудалось записать файл ResultPairs.txt!");
        out.close();
        {
            auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            char str[50];
            ctime_s(str, sizeof(str), &timenow);
            log << "Файл ResultPairs.txt успешно записан.\n";
            log << str << std::endl;
            log << " * ****************************************************\n";
        }
        
    }
    catch (std::exception const& e) {
        std::cout << "There was an error: " << e.what() << std::endl;
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        char str[50];
        ctime_s(str, sizeof(str), &timenow);
        log << "Неудача.\nПроизошла ошибка: " << e.what() << std::endl;
        log << str << std::endl;
        log << " * ****************************************************\n";

    }
    log.close();
}