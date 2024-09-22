#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "work_with_BMP.h"

int main(int argc, char* argv[])
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF8");

    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    std::string path;
    std::string er{ "Error" };
    Work_with_BMP picture;

    if (argc==1) {
        std::cout << "Вы не указали путь к файлу изображения. Введите пожалуйста полный путь к файлу." << std::endl;
        std::getline(std::cin, path);
    }
    else {
        path = argv[1];
    }

    try {
        picture.openBMP(path);
        picture.displayBMP();
        picture.closeBMP();
    }
    catch (std::string error_message){
        std::cout << error_message << std::endl;
    }

    return 0;
}