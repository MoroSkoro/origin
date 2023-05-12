cmake_minimum_required(VERSION 3.22.0)
project(Task_1 VERSION 1.0.0.0)

#add_executable(Task_1 ListNode_main.cpp)

add_subdirectory(lib/Catch2)
add_executable(Test_1 Test_ListNode.cpp)
target_link_libraries(Test_1 PRIVATE Catch2::Catch2)
