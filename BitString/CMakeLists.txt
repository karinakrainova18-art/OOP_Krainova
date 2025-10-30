cmake_minimum_required(VERSION 3.16)
project(BitStringProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(bitstring_cpp STATIC
  src/BitString.cpp
)

target_include_directories(bitstring_cpp PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(GTest REQUIRED)

enable_testing()
add_executable(bitstring_cpp_tests
  tests/bitstring_tests.cpp
)

target_include_directories(bitstring_cpp_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(bitstring_cpp_tests PRIVATE
  bitstring_cpp
  GTest::gtest
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(bitstring_cpp_tests)