cmake_minimum_required(VERSION 3.10.0)
project(aoc25 VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
# find_package(OpenSSL REQUIRED)

if(CMAKE_CONFIGURATION_TYPES)
    set(RUNTIME_OUT_DIR "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
else()
    set(RUNTIME_OUT_DIR "${CMAKE_BINARY_DIR}/bin")
endif()
# add_executable(aoc main.cpp aoc.cpp ${DAY_SOURCES} ...)
# Add executable and enable precompiled headers
add_executable(aoc25 main.cpp aoc.cpp
    d1.cpp d2.cpp d3.cpp d4.cpp d5.cpp
    d6.cpp d7.cpp d8.cpp d9.cpp d10.cpp
    d11.cpp d12.cpp
)
target_precompile_headers(aoc25 PRIVATE pch.h)
# target_link_libraries(aoc25 PRIVATE OpenSSL::Crypto)

set_target_properties(aoc25 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_OUT_DIR}"
)

set(SOURCE_DATA_DIR "${CMAKE_SOURCE_DIR}/2025/input")
set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${GENERATED_DIR}")

# configure into GENERATED_DIR (input from this CMakeLists folder)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/data_dir.h.in" "${GENERATED_DIR}/data_dir.h" @ONLY)

target_include_directories(aoc25 PRIVATE "${GENERATED_DIR}")
