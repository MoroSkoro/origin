cmake_minimum_required(VERSION 3.22.0)
project(Task_5 VERSION 1.0.0.0)

set(SOURCES Figure.cpp Triangle.cpp Right_triangle.cpp Equilateral_triangle.cpp Isosceles_triangle.cpp
Quadrangle.cpp Rectangle.cpp Parallelogram.cpp Phomb.cpp Square.cpp)
set(HEADERS Figure.h Triangle.h Right_triangle.h Equilateral_triangle.h Isosceles_triangle.h Quadrangle.h
Rectangle.h Parallelogram.h Phomb.h Square.h)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(FigureDll SHARED ${SOURCES} ${HEADERS})
add_executable(Task_5 FigureExe.cpp)
target_link_libraries(Task_5 FigureDll)
