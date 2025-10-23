include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(bracket_validator_lib
    bracket_validator.cpp
)

add_executable(bracket_validator_app
    main.cpp
)

target_link_libraries(bracket_validator_app bracket_validator_lib)