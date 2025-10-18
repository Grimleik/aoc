cmake_minimum_required(VERSION 3.10.0)
project(aoc VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
find_package(OpenSSL REQUIRED)
file(GLOB DAY_SOURCES "d*.cpp")
# add_executable(aoc main.cpp aoc.cpp ${DAY_SOURCES} ...)
# Add executable and enable precompiled headers
add_executable(aoc main.cpp aoc.cpp
    d1.cpp d2.cpp d3.cpp d4.cpp d5.cpp
    d6.cpp d7.cpp d8.cpp d9.cpp d10.cpp
    d11.cpp d12.cpp d13.cpp d14.cpp d15.cpp
    d16.cpp d17.cpp d18.cpp
)
target_precompile_headers(aoc PRIVATE pch.h)
target_link_libraries(aoc PRIVATE OpenSSL::Crypto)


