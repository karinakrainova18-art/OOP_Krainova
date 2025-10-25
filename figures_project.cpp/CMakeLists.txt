cmake_minimum_required(VERSION 3.10)
project(FiguresProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Rectangle.cpp
    src/Trapeze.cpp
    src/Rhombus.cpp
)

set(TEST_SOURCES
    tests/test_figures.cpp
    src/Rectangle.cpp
    src/Trapeze.cpp
    src/Rhombus.cpp
)

add_executable(figures ${SOURCES})
add_executable(test_figures ${TEST_SOURCES})

target_link_libraries(test_figures GTest::gtest_main)

target_compile_options(figures PRIVATE -Wall -Wextra -pedantic)
target_compile_options(test_figures PRIVATE -Wall -Wextra -pedantic)

enable_testing()

include(GoogleTest)
gtest_discover_tests(test_figures
    EXTRA_ARGS "--gtest_output=xml:test_results.xml"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_test(NAME FiguresTest_Detailed COMMAND test_figures --gtest_color=yes)
add_test(NAME FiguresTest_Brief COMMAND test_figures --gtest_brief=1)

install(TARGETS figures DESTINATION bin)