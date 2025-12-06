cmake_minimum_required(VERSION 3.10)
project(lab_06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_06_run 
    main.cpp 
    src/npc.cpp 
    src/battle_visitor.cpp 
    src/observer.cpp 
    src/npc_factory.cpp 
    src/dungeon_editor.cpp
)

add_executable(lab_06_tests 
    tests/dungeon_tests.cpp 
    src/npc.cpp 
    src/battle_visitor.cpp 
    src/observer.cpp 
    src/npc_factory.cpp 
    src/dungeon_editor.cpp
)

find_package(GTest REQUIRED)
if(TARGET GTest::gtest_main)
    target_link_libraries(lab_06_tests PRIVATE GTest::gtest_main)
else()
    target_link_libraries(lab_06_tests PRIVATE ${GTEST_LIBRARIES})
    target_include_directories(lab_06_tests PRIVATE ${GTEST_INCLUDE_DIRS})
endif()


