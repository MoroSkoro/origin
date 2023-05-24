#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <stdarg.h>

template<typename T>
void print_container(T& a) {
	for (auto i : a) std::cout << i << " ";
	std::cout << "\n";
}

int main() {
	
	std::set<std::string> test_set = { "one", "two", "three", "four" };
	print_container(test_set);

	std::list<std::string> test_list = { "one", "two", "three", "four" };
	print_container(test_list);

	std::vector<std::string> test_vector = { "one", "two", "three", "four" };
	print_container(test_vector);
	
	std::cout << "\n\n";
	system("pause");
}