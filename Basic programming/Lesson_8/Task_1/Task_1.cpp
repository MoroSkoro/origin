#include <iostream>
#include <windows.h>
#include <string>
#include <exception>



int functiong(std::string str, int forbidden_length) {
	if (forbidden_length == str.length())
		throw std::exception ("Вы ввели слово запретной длины! До свидания");
	return str.length();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	int forbidden_length = 1;
	std::string str;

	std::cout << "Введите запретную длину : ";
	std::cin >> forbidden_length;
	do {
		std::cout << "Введите слово: ";
		std::cin >> str;
		try {
			std::cout << "Длина слова \"" << str << "\" равна " << functiong(str, forbidden_length) << std::endl;
		}
		catch (std::exception& bad_length) {
			std::cout << bad_length.what() << std::endl;
			break;
		}
	} while (1);
}