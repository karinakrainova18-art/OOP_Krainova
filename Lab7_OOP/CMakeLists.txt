cmake_minimum_required(VERSION 3.10)
project(lab_07 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_07_run 
    main.cpp 
    src/simulation.cpp 
    src/battle_logic.cpp
)

add_executable(lab_07_tests 
    tests/battle_tests.cpp 
    src/simulation.cpp 
    src/battle_logic.cpp
)

find_package(GTest REQUIRED)
if(TARGET GTest::gtest_main)
    target_link_libraries(lab_07_tests PRIVATE GTest::gtest_main)
else()
    target_link_libraries(lab_07_tests PRIVATE ${GTEST_LIBRARIES})
    target_include_directories(lab_07_tests PRIVATE ${GTEST_INCLUDE_DIRS})
endif()

find_package(Threads REQUIRED)
target_link_libraries(lab_07_run PRIVATE Threads::Threads)
target_link_libraries(lab_07_tests PRIVATE Threads::Threads)


