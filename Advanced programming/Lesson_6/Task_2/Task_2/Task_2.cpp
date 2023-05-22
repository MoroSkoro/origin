#include <iostream>
#include <string>
#include <windows.h>
#include <map>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::string text;
    size_t count = 0;
    typedef std::pair <size_t, char> char_pair;
    std::map<char, size_t, std::less<>> char_num;
    /*std::cout << "Введите сроку\n";
    std::getline(std::cin, text);*/
    std::cout << "\n";
    text = "Hello world!!";
    for (auto& s : text) {
        count = 0;
        count = std::count(text.begin(), text.end(), s);
        char_num[s] = count;
    }

    std::multimap<size_t, char, std::greater<>> char_num1;
    for (auto& s : char_num) {
        char_num1.insert(char_pair(s.second, s.first));
    }

    std::cout << "[IN]: " << text << "\n";
    std::cout << "[OUT]: " << "\n\n";

    for (const auto& [f, s] : char_num1) {
        std::cout << s << ": " << f << "\n" << std::endl;
    }
}