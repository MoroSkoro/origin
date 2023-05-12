#pragma once
#include <iostream>
#include <exception>
#include "ListNode.h"

int main() {
	std::cout << "Hello!";

	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	try {
		
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}