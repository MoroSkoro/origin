﻿#include <iostream>
#include <exception>
#include <cstdio>

class smart_array {
	size_t size;
	size_t actual_size = 0;
	int* arr;
public:
	smart_array(size_t size) {
		this->size = size;
		arr = new int [size] {0};
	}

	smart_array(const smart_array&a) {
		size = a.size;
		arr = new int[size];
		for (size_t i = 0; i < size; i++)
			arr[i] = a.arr[i];
		actual_size = a.actual_size;
	}

	smart_array& operator=(const smart_array& other){
		if (size > 0) // освободить предварительно выделенную память
			delete[] arr;

		size = other.size;
		arr = new int[size];
		for (size_t i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
		actual_size = other.actual_size;
		return *this;
	}

	~smart_array() { delete[] arr; };

	void add_element(int value) {
		if (value > 2000000) {
			throw std::exception("Превышено максимальное значение элемента массива!");
		}
		if (actual_size < size) {
			arr[actual_size] = value;
			++actual_size;
		}
		else {
			if (2 * size > 2640) {
				throw std::length_error("Превышено максимальное значение элементов в массиве!");
			}
			int* tmp = new int[2 * size]{ 0 };
			for (size_t i = 0; i < size; i++) {
				tmp[i] = arr[i];
			}
			tmp[actual_size] = value;
			++actual_size;
			size = 2 * size;
			delete[] arr;
			arr = tmp;
		}
	};
	int get_element(int n) {
		if ((n < size) && (n >= 0)) { return arr[n]; }
		else {
			throw std::exception("Не верный индекс");
			return 0;
		}
	};
};


int main()
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	smart_array arr(5);
	arr.add_element(1);
	arr.add_element(4);
	arr.add_element(155);

	smart_array new_array(2);
	new_array.add_element(44);
	new_array.add_element(34);

	arr = new_array;
}