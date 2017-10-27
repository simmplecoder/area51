cmake_minimum_required(VERSION 3.5)
project(area51)

include_directories(../src/)

#tests
add_executable(sliding_window_tests sliding_window_tests.cpp)
add_executable(first_parameter_extraction_tests first_parameter_extraction_tests.cpp)
add_executable(transform_iterator_tests transform_iterator_tests.cpp)
add_executable(deduce_single_parameter_tests deduce_single_parameter_tests.cpp)
add_executable(numerical_tests numerical_tests.cpp)
add_executable(scope_exit_tests scope_exit_tests.cpp)
add_executable(stumbled_iterator_tests stumbled_iterators_test.cpp)
add_executable(circular_buffer_tests circular_buffer_tests.cpp)
add_executable(benchmark_tests benchmark_tests.cpp)
add_executable(regular_callable_tests regular_callable_tests.cpp)
add_executable(most_frequent_tests most_frequent_tests.cpp)
add_executable(tuple_exploder tuple_exploder_tests.cpp)
add_executable(merge_sort_tests merge_sort_tests.cpp)
target_include_directories(merge_sort_tests PUBLIC ../src)

add_executable(merge_tests merge_tests.cpp)
target_include_directories(merge_tests PUBLIC ../src)

add_executable(benchmark_v2_tests benchmark_v2_tests.cpp)
target_link_libraries(benchmark_v2_tests c++experimental c++abi)

add_executable(comb_sort_tests comb_sort_tests.cpp)
add_executable(result_cache_tests result_cache_tests.cpp)
add_executable(utilities_tests utilities_tests.cpp)
add_executable(geniune_apply_tests geniune_apply_tests.cpp)

add_executable(benchmark_rewrite_test benchmark_rewrite_test.cpp)
target_link_libraries(benchmark_rewrite_test c++experimental c++abi)

add_executable(quick_sort_tests quick_sort_tests.cpp)

add_test(circular-buffer-tests circular_buffer_tests)
add_test(most-frequent-tests most_frequent_tests)
add_test(numerical-tests numerical_tests)
add_test(regular-callable-tests regular_callable_tests)
add_test(scope-exit-tests scope_exit_tests)
add_test(sliding-window-tests sliding_window_tests)
add_test(stumbled-iterator-tests stumbled_iterator_tests)
add_test(transform-iterator-tests transform_iterator_tests)
add_test(result-cache-tests result_cache_tests)
add_test(utilities-test utilities_tests)
add_test(quick-sort-tests quick_sort_tests)