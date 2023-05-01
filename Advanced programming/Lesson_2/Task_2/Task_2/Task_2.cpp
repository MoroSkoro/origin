#include <iostream>
using namespace std; // не ошибка, но некорректно, так как все равно используется std::


void print_point(int x);

int main()
{
	int i;

	cin >> a; // неопределена переменная а. нужно объявить ее тип, например int a;
	int a = 5;
	int arr[5]{ 1, 2, 3, 4, 5, };
	cout << "arr = ";
	for (i = 0; i <= a; i++) { // семантическая ошибка, выход за пределы массива, знак = не нужен.
		cout << arr[i] << " ";
	}
	cout << "\n";
	print_point(3);
	return 0;
}

void print_point(char x) { // ошибка линковки. разные типы в объявлении и реализации функции. нужно тип int
	std::cout << "x:" << x << std::endl;
}