cmake_minimum_required(VERSION 3.18)

project(
    SearchEngine
    VERSION ${VER_FILE_CONTENT}
    LANGUAGES CXX
)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 20)
endif()

#target_compile_features(Test_libpqxx16 PRIVATE cxx_std_20)

#add_subdirectory(F:\\libpqxx-7.7.5 libpqxx-build)

add_executable(SearchEngine SearchEngine.cpp)

add_subdirectory(libpqxx Build16)
target_link_libraries(SearchEngine pqxx)

