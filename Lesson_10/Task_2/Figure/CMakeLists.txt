cmake_minimum_required(VERSION 3.22.0)
add_library(Figure Figure.cpp)
add_library(FigureException FigureException.cpp)
target_include_directories(Figure
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )