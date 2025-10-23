find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(bracket_validator_tests
    test_bracket_validator.cpp
)

target_link_libraries(bracket_validator_tests
    GTest::gtest
    GTest::gtest_main
    bracket_validator_lib
)

add_test(NAME BracketValidatorTests COMMAND bracket_validator_tests)