cmake_minimum_required(VERSION 3.20)
project(forth VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable(forth main.cpp commands_namespace.cpp commands.cpp interpreter.cpp)

add_executable(forth_test commands_namespace.cpp forth_test.cpp commands.cpp interpreter.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

SET(WARN_FLAGS "-Wall -Wpedantic -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}")

enable_testing()

target_link_libraries(
        forth_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(forth_test)