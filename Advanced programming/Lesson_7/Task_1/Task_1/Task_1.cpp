#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(){
	std::vector<int> vec{1, 1, 2, 5, 6, 1, 2, 4 };
	std::cout << "[IN]: ";
	for_each(vec.begin(), vec.end(), [](const int& n) {std::cout << n << " "; });
	std::cout << "\n";
	
	sort(vec.begin(), vec.end());
	std::vector<int>::iterator it;
	it = std::unique(vec.begin(), vec.end());
	vec.erase(it, vec.end());
	std::cout << "[OUT]: ";
	//copy(vec.begin(), vec.end(), std::ostream_iterator(std::cout, " "));
	for_each(vec.begin(), vec.end(), [](const int& n) {std::cout << n << " "; });
	
	std::cout << "\n\n";
	system("pause");
}