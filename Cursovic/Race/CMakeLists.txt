cmake_minimum_required(VERSION 3.22.0)
project(Cursovic VERSION 1.0.0.0)

set(SOURCES Transport.cpp Camel.cpp Krahotabl.cpp CamelFast.cpp Boots_AllTerrain.cpp Broom.cpp
Eagle.cpp Magic_carpet.cpp Functions.cpp)
set(HEADERS Transport.h Camel.h Krahotabl.h CamelFast.h Boots_AllTerrain.h Broom.h Eagle.h
Magic_carpet.h Functions.h)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(RaceDll SHARED ${SOURCES} ${HEADERS})
add_executable(Cursovic Race.cpp )
target_link_libraries(Cursovic RaceDll)
