cmake_minimum_required(VERSION 3.6)
project(area51)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -std=c++1z")

set(SOURCE_FILES
        src/timing_session.hpp
        src/fast_find.hpp
        src/main.cpp
        src/random_engine.hpp
        src/scope_exit.hpp
        src/custom_mpl.hpp
        src/typelist.hpp
        src/string_manip.hpp
        src/numerical.hpp
        src/prime_numbers.hpp
        src/containers.hpp
        src/circular_buffer.hpp
        src/iterator.hpp
        src/formatted_read.hpp
        src/sliding_window.hpp
        src/transform_iterator.hpp
        src/deduce_first_parameter.hpp
        src/transform_iterator.cpp
        src/numerical.cpp
        src/typelist.cpp
        src/deduce_single_parameter.hpp
        src/deduce_single_parameter.cpp
        src/sliding_window.cpp
        src/member_callback.hpp)

add_executable(area51 ${SOURCE_FILES})
add_executable(sliding_window_tests tests/sliding_window_tests.cpp src/sliding_window.hpp)
add_executable(first_parameter_extraction_tests tests/first_parameter_extraction_tests.cpp)
add_executable(transform_iterator_tests tests/transform_iterator_tests.cpp)
add_executable(deduce_single_parameter_tests tests/deduce_single_parameter_tests.cpp)
add_executable(numerical_tests tests/numerical_tests.cpp)
add_executable(scope_exit_tests tests/scope_exit_tests.cpp)