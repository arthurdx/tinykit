cmake_minimum_required(VERSION 3.16)
project(tinykit VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(tinykit
    src/strutil.cpp
    src/arg_parser.cpp
)
target_include_directories(tinykit PUBLIC include)
target_compile_options(tinykit PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)

include(CTest)
if(BUILD_TESTING)
    add_executable(tinykit_tests
        tests/main.cpp
        tests/test_strutil.cpp
        tests/test_ring_buffer.cpp
        tests/test_arg_parser.cpp
    )
    target_link_libraries(tinykit_tests PRIVATE tinykit)
    target_compile_options(tinykit_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
    add_test(NAME tinykit_tests COMMAND tinykit_tests)
endif()
