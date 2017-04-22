cmake_minimum_required(VERSION 3.6)
project(area51)

enable_testing()

set(SOURCE_FILES
        src/timing_session.hpp
        src/fast_find.hpp
        src/random_int_generator.hpp
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

#tests
add_executable(sliding_window_tests tests/sliding_window_tests.cpp)
add_executable(first_parameter_extraction_tests tests/first_parameter_extraction_tests.cpp)
add_executable(transform_iterator_tests tests/transform_iterator_tests.cpp)
add_executable(deduce_single_parameter_tests tests/deduce_single_parameter_tests.cpp)
add_executable(numerical_tests tests/numerical_tests.cpp)
add_executable(scope_exit_tests tests/scope_exit_tests.cpp)
add_executable(stumbled_iterator_tests tests/stumbled_iterators_test.cpp)
add_executable(circular_buffer_tests tests/circular_buffer_tests.cpp)
add_executable(benchmark_tests tests/benchmark_tests.cpp)
add_executable(regular_callable_tests tests/regular_callable_tests.cpp)
add_executable(most_frequent_tests tests/most_frequent_tests.cpp)
add_executable(tuple_exploder tests/tuple_exploder_tests.cpp)
add_executable(benchmark_v2_tests tests/benchmark_v2_tests.cpp)

#demos
add_executable(random_int_generator_demo demos/random_int_generator_demo.cpp)
add_executable(random_selector_demo demos/random_selector_demo.cpp)
add_executable(bubble_sort_demo demos/bubble_sort_demo.cpp)
add_executable(insertion_sort_demo demos/insertion_sort_demo.cpp)
add_executable(selection_sort_demo demos/selection_sort_demo.cpp)
add_executable(shaker_sort_demo demos/shaker_sort_demo.cpp)
add_executable(comb_sort_demo demos/comb_sort_demo.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem /usr/local/include/c++/v1 -stdlib=libc++ -lc++abi -Wall -Wextra -pedantic-errors -std=c++1z")

add_test(circular-buffer-tests circular_buffer_tests)
add_test(most-frequent-tests most_frequent_tests)
add_test(numerical-tests numerical_tests)
add_test(regular-callable-tests regular_callable_tests)
add_test(scope-exit-tests scope_exit_tests)
add_test(sliding-window-tests sliding_window_tests)
add_test(stumbled-iterator-tests stumbled_iterator_tests)
add_test(transform-iterator-tests transform_iterator_tests)
