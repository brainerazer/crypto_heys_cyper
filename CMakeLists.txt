cmake_minimum_required(VERSION 3.7)
project(Lab1yak)

set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

include_directories("/usr/local/opt/llvm/include")
link_directories("/usr/local/opt/llvm/lib")

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES src/io.h src/io.cpp src/common.h src/heys.cpp src/heys.h src/byte_utils.cpp src/byte_utils.h)
set(TEST_SOURCES tests/catch_main.cpp tests/test_io.cpp tests/test_byte_utils.cpp tests/test_heys.cpp tests/integration_test_hays.cpp)

add_library(Lab1yak ${SOURCE_FILES})

add_executable(Lab1yak_exec src/main.cpp)
target_link_libraries(Lab1yak_exec Lab1yak)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE libs/catch)

add_executable(Lab1yak_test ${TEST_SOURCES})
target_link_libraries(Lab1yak_test Catch)
target_link_libraries(Lab1yak_test Lab1yak)
