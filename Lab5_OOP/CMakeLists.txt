cmake_minimum_required(VERSION 3.15)
project(Lab05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main src/main.cpp)
add_executable(tests tests/test.cpp)

target_link_libraries(main)
target_link_libraries(tests)