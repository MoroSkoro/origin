cmake_minimum_required(VERSION 3.20)

project(
    SearchEngine
    VERSION ${VER_FILE_CONTENT}
    LANGUAGES CXX
)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 20)
endif()

add_executable(SearchEngine SearchEngine.cpp 
    Resurs/include/sch_engine/processing_functions.h
    Resurs/src/sch_engine/processing_functions.cpp)
target_compile_features(SearchEngine PRIVATE cxx_std_20)
target_include_directories(SearchEngine PUBLIC Resurs/include/sch_engine/ Resurs/src/sch_engine/)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git)
                         #GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(pqxx GIT_REPOSITORY https://github.com/jtv/libpqxx.git)
FetchContent_MakeAvailable(pqxx)

target_link_libraries(SearchEngine PRIVATE cpr::cpr)
target_link_libraries(SearchEngine PRIVATE pqxx)





