cmake_minimum_required(VERSION 3.2)

project(
    ClassDataBase
    VERSION ${VER_FILE_CONTENT}
    LANGUAGES CXX
)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 17)
endif()

#target_compile_features(ClassDataBas PRIVATE cxx_std_17)

add_subdirectory(F:\\libpqxx-7.7.5 libpqxx-build)

add_executable(ClassDataBase main.cpp)
target_link_libraries(ClassDataBase pqxx)

