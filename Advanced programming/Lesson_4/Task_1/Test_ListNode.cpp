#pragma once
#include <iostream>
#include <exception>
#include "ListNode.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>


TEST_CASE("test Empty", "[Empty]") {
	INFO("Проверка Empty");
	List TestList;
	CHECK(TestList.Empty() == true);
}

TEST_CASE("test Size", "[Size]") {
	INFO("Проверка Size");
	List TestList;
	TestList.PushFront(5);
	TestList.PushFront(10);
	TestList.PushBack(3);
	CHECK(TestList.Size() == 3);
}

TEST_CASE("test Clear", "[Clear]") {
	INFO("Проверка Clear");
	List TestList;
	TestList.PushFront(5);
	TestList.PushFront(10);
	TestList.PushBack(3);
	TestList.Clear();
	CHECK(TestList.Empty() == true);
}

int main(int argc, char* argv[]) {
	
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	
	return Catch::Session().run(argc, argv);
}