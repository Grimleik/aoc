cmake_minimum_required(VERSION 3.10.0)
project(aoc VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB DAY_SOURCES "d*.cpp")
# add_executable(aoc main.cpp aoc.cpp ${DAY_SOURCES} ...)
# Add executable and enable precompiled headers
add_executable(aoc main.cpp aoc.cpp d1.cpp d2.cpp d3.cpp d4.cpp d5.cpp)
target_precompile_headers(aoc PRIVATE pch.h)
# target_link_libraries(aoc crypto)


