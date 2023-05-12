#pragma once
#include <iostream>
#include <exception>
#include "ListNode.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>


TEST_CASE("test PushBack", "[PushBack]") {
	INFO("Проверка PushBack");
	SECTION("number of inserted members") {
		List TestList;
		TestList.PushBack(2);
		TestList.PushBack(3);
		TestList.PushBack(5);
		CHECK(TestList.Size() == 3);
	}
}

TEST_CASE("test PushFront", "[PushFront]") {
	INFO("Проверка PushFront");
	SECTION("number of inserted members") {
		List TestList;
		TestList.PushFront(2);
		TestList.PushFront(3);
		TestList.PushFront(5);
		TestList.PushFront(0);
		CHECK(TestList.Size() == 4);
	}
}

TEST_CASE("test PopBack", "[PopBack]") {
	INFO("Проверка PopBack");
	SECTION("checking for deletion and an exception when the list is empty") {
		List TestList;
		TestList.PushFront(2);
		TestList.PushFront(3);
		TestList.PushFront(5);
		TestList.PushFront(0);
		int x = TestList.PopBack();
		CHECK(x == 2);
		INFO("Проверка x=2");
		CHECK(TestList.Size() == 3);
		INFO("Проверка size=3");
		TestList.PopBack();
		CHECK(TestList.Size() == 2);
		INFO("Проверка size=2");
		try {
			TestList.PopBack();
			TestList.PopBack();
			CHECK(TestList.Size() == 0);
			TestList.PopBack();
		}
		catch (const std::exception& ex) {
			std::cout << "\n" << ex.what() << std::endl;
		}
	}
}

TEST_CASE("test PopFront", "[PopFront]") {
	INFO("Проверка PopFront");
	SECTION("checking for deletion and an exception when the list is empty") {
		List TestList;
		TestList.PushFront(2);
		TestList.PushFront(3);
		TestList.PushFront(5);
		TestList.PushFront(0);
		int x = TestList.PopFront();
		CHECK(x == 0);
		INFO("Проверка x=0");
		CHECK(TestList.Size() == 3);
		INFO("Проверка size=3");
		TestList.PopFront();
		CHECK(TestList.Size() == 2);
		INFO("Проверка size=2");
		try {
			TestList.PopFront();
			TestList.PopFront();
			CHECK(TestList.Size() == 0);
			TestList.PopFront();
		}
		catch (const std::exception& ex) {
			std::cout << "\n" << ex.what() << std::endl;
		}
	}
}


TEST_CASE("test various", "[Clear]") {
	INFO("Проверка разных функций класса");
	List TestList;
	TestList.PushFront(5);
	TestList.PushBack(3);
	int x = TestList.PopFront();
	CHECK(x == 5);
	CHECK(TestList.Size() == 1);
	TestList.PushFront(15);
	TestList.PushBack(30);
	x = TestList.PopBack();
	CHECK(x == 30);
	CHECK(TestList.Size() == 2);
	TestList.Clear();
	CHECK(TestList.Empty() == true);
}

int main(int argc, char* argv[]) {
	
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	
	return Catch::Session().run(argc, argv);
}