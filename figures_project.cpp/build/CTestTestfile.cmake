# CMake generated Testfile for 
# Source directory: /home/karin/figures_project.cpp
# Build directory: /home/karin/figures_project.cpp/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/karin/figures_project.cpp/build/test_figures[1]_include.cmake")
add_test(FiguresTest_Detailed "/home/karin/figures_project.cpp/build/test_figures" "--gtest_color=yes")
set_tests_properties(FiguresTest_Detailed PROPERTIES  _BACKTRACE_TRIPLES "/home/karin/figures_project.cpp/CMakeLists.txt;41;add_test;/home/karin/figures_project.cpp/CMakeLists.txt;0;")
add_test(FiguresTest_Brief "/home/karin/figures_project.cpp/build/test_figures" "--gtest_brief=1")
set_tests_properties(FiguresTest_Brief PROPERTIES  _BACKTRACE_TRIPLES "/home/karin/figures_project.cpp/CMakeLists.txt;42;add_test;/home/karin/figures_project.cpp/CMakeLists.txt;0;")
