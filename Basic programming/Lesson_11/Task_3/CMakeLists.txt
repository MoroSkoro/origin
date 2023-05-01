cmake_minimum_required(VERSION 3.22.0)
project(CMake_Task_3)

add_library(LeaveDll SHARED LeaverDll.h LeaverDll.cpp)
add_executable(Task_3 LeaverExe.cpp)
target_link_libraries(Task_3 PUBLIC LeaveDll)

