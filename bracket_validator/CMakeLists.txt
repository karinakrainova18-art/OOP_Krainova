set(CMAKE_C_COMPILER gcc-14)
cmake_minimum_required(VERSION 3.10)
project(BracketValidator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)