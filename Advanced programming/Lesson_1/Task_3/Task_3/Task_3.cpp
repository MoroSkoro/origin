
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <string>


int main()
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	const double pi = 3.1415926;
	std::vector<double> angles{30*pi/180, 60*pi/180, 90*pi/180};
	std::cout << "[Входные данные]: ";
	auto iter = angles.begin();
	for (const auto& angle : angles) {
		if ((iter+1) != angles.end()){
			std::cout << angle << ", ";
			iter++;
		}
		else { std::cout << angle << ".\n\n"; }
	}

	std::function<void(double)> func1;
	auto sinus = [](double angle) {std::cout << " sin: " << sin(angle)  << ",";};
	func1 = sinus;
	std::function<void(double)> func2;
	auto cosinus = [](double angle) {std::cout << " cos: " << cos(angle) << ","; };
	func2 = cosinus;
	std::function<void(double)> func3;
	auto tgens = [](double angle) {std::cout << " tg: " << tan(angle) << ""; };
	func3 = tgens;
	std::vector<std::function<void(double)>> functions{ func1, func2, func3};

	std::cout << "[Выходные данные]:\n";
	for (const auto& angle : angles) {
		std::cout << angle << ": ";
		for (const auto& function : functions)
			function(angle);
		std::cout << std::endl;
	}
}