
#include <iostream>
#include <vector>
#include <variant>
#include <string>

std::variant<int, std::string, std::vector<int>> get_variant() {
	std::srand(std::time(nullptr));
	int random_variable = std::rand() % 3;

	std::variant<int, std::string, std::vector<int>> result;
	switch (random_variable)
	{
	case 0:
		result = 5;
		break;
	case 1:
		result = "string";
		break;
	case 2:
		result = std::vector<int>{ 1, 2, 3, 4, 5 };
		break;
	default:
		break;
	}
	return result;
}


int main()
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	auto s = get_variant();
	//std::holds_alternative<std::string>(get_variant());
	std::cout << "Сейчас значением функции get_variant() является:" << "\n";
	if (std::holds_alternative<int>(s)) {
		auto s_int = std::get<int>(s);
		std::cout << s_int*2 << "\n";
	}

	if (std::holds_alternative<std::string>(s)) {
		auto s_string = std::get<std::string>(s);
		std::cout << s_string << "\n";
	}

	if (std::holds_alternative<std::vector<int>>(s)) {
		auto s_vector = std::get<std::vector<int>>(s);
		for (auto var : s_vector) {
			std::cout << var << " ";
		}
	}
}
