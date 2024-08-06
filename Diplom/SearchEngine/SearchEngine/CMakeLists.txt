cmake_minimum_required(VERSION 3.20)

project(
    SearchEngine
    VERSION ${VER_FILE_CONTENT}
    LANGUAGES CXX
)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 20)
endif()

#include_directories(/Resurs/include/)
#link_directories(${CMAKE_SOURCE_DIR}/Resurs/lib/cpr/)

add_executable(SearchEngine SearchEngine.cpp 
    Resurs/include/sch_engine/processing_functions.h
    Resurs/src/sch_engine/processing_functions.cpp)
target_compile_features(SearchEngine PRIVATE cxx_std_20)
target_include_directories(SearchEngine PUBLIC Resurs/include/sch_engine/ Resurs/src/sch_engine/)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#CMAKE_SYSTEM_NAME MATCHES "Windows"

   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
include(FetchContent)
FetchContent_Declare(cpr SOURCE_DIR "${CMAKE_SOURCE_DIR}/Resurs/cpr/")
#FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
    #GIT_TAG 1.10.5)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(pqxx SOURCE_DIR "${CMAKE_SOURCE_DIR}/Resurs/libpqxx/")
FetchContent_MakeAvailable(pqxx)

target_link_libraries(SearchEngine PRIVATE cpr::cpr)
target_link_libraries(SearchEngine PRIVATE pqxx)
target_link_directories(SearchEngine PUBLIC ${CMAKE_SOURCE_DIR}/Resurs/libxml2/lib/
     ${CMAKE_SOURCE_DIR}/Resurs/iconv/lib/)
target_link_libraries(SearchEngine PRIVATE libxml2 iconv) #libxml2d
target_include_directories(SearchEngine PUBLIC ${CMAKE_SOURCE_DIR}/Resurs/libxml2/include/
     ${CMAKE_SOURCE_DIR}/Resurs/iconv/include/)

