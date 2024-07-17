cmake_minimum_required(VERSION 3.20)

project(
    SearchEngine
    VERSION ${VER_FILE_CONTENT}
    LANGUAGES CXX
)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 20)
endif()

INCLUDE_DIRECTORIES(
 #E:/dev/vcpkg/installed/x64-windows/include
 Resurs/include
)

LINK_DIRECTORIES(
   #E:/dev/vcpkg/installed/x64-windows/lib
   Resurs/lib
)

#set (cpr_DIR "E:/libcpr/cpr")

add_executable(SearchEngine SearchEngine.cpp  "Resurs/include/sch_engine/processing_functions.h" "Resurs/src/sch_engine/processing_functions.cpp")
target_compile_features(SearchEngine PRIVATE cxx_std_20)

target_include_directories(SearchEngine PUBLIC Resurs/include/sch_engine/ Resurs/src/sch_engine/)

add_subdirectory(Resurs/libpqxx Build16)
target_link_libraries(SearchEngine PRIVATE pqxx)

#find_package(cpr CONFIG REQUIRED)
#find_package(cpr REQUIRED)
add_subdirectory(Resurs/cpr BuildCPR)
target_link_libraries(SearchEngine PRIVATE cpr::cpr)

find_package(LibXml2 REQUIRED)
target_link_libraries(SearchEngine PRIVATE LibXml2::LibXml2)



