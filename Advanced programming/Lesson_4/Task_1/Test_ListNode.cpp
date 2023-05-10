#pragma once
#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

unsigned int Factorial(unsigned int number) {
	if (number == 0 || number == 1)
		return 1;
	else
		return Factorial(number - 1) * number;
}
TEST_CASE("test factorial", "[factorial]") {
	CHECK(Factorial(0) == 1);
	SECTION("positive numbers") {
		CHECK(Factorial(1) == 1);
		CHECK(Factorial(5) == 120);
		CHECK(Factorial(10) == 3628800);
	}
}
int main(int argc, char* argv[]) {
	return Catch::Session().run(argc, argv);
}