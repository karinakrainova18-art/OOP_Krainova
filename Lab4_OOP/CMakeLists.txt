cmake_minimum_required(VERSION 3.16)
project(FiguresTemplateProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(figures_main
  src/main.cpp
)

target_include_directories(figures_main PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(GTest QUIET)

if(GTest_FOUND)
  enable_testing()
  
  add_executable(figures_tests
    tests/figures_tests.cpp
  )
  
  target_include_directories(figures_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  
  target_link_libraries(figures_tests PRIVATE
    GTest::gtest
    GTest::gtest_main
  )
  
  include(GoogleTest)
  gtest_discover_tests(figures_tests)
else()
  message(WARNING "Google Test not found. Tests will not be built.")
endif()
