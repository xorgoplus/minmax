cmake_minimum_required(VERSION 3.14)
project(minmax C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(core_lib STATIC
        src/cpu.c
        src/simd.c
)

target_include_directories(core_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_options(core_lib PRIVATE -mavx2)

add_executable(minmax
        src/main.c
)
target_link_libraries(minmax PRIVATE core_lib)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(unit_tests
        tests/test_cpu.cpp
)

target_include_directories(unit_tests PRIVATE
        ${googletest_SOURCE_DIR}/googletest/include
)

target_link_libraries(unit_tests PRIVATE
        core_lib
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)