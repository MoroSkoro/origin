cmake_minimum_required(VERSION 3.22.0)
project(CMake_Task_2)
add_subdirectory(Figure)
add_subdirectory(Figure/Triangle)
add_subdirectory(Figure/Quadrangle)
add_executable(Task_2 Task_2.cpp)
target_link_libraries(Task_2 PUBLIC Figure FigureException)
target_link_libraries(Task_2 PUBLIC Triangle Right_triangle Isosceles_triangle Equilateral_triangle)
target_link_libraries(Task_2 PUBLIC  Quadrangle Rectangle Parallelogram Phomb Square)
target_include_directories(Task_2 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Figure"
                          "${PROJECT_SOURCE_DIR}/Figure/Triangle"
                          "${PROJECT_SOURCE_DIR}/Figure/Quadrangle"
                          )
