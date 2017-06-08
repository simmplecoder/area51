cmake_minimum_required(VERSION 3.5)
project(area51)

set(HEADER_FILES algorithm.hpp
        algorithm.hpp
        benchmark-formatters/def_formatter.hpp
        benchmark.hpp
        benchmark_streamer.hpp
        benchmark_v2.hpp
        circular_buffer.hpp
        containers.hpp
        custom_mpl.hpp
        deduce_first_parameter.hpp
        deduce_single_parameter.cpp
        deduce_single_parameter.hpp
        explode_tuple.cpp
        explode_tuple.hpp
        fast_find.hpp
        formatted_read.hpp
        generators/int_vector_generator.hpp
        input_digit_iterator.hpp
        iterator.hpp
        member_callback.hpp
        numerical.cpp
        numerical.hpp
        prime_numbers.hpp
        random_int_generator.hpp
        random_selector.hpp
        regular_callable.hpp
        result_cache.hpp
        scope_exit.hpp
        sliding_window.cpp
        sliding_window.hpp
        sort.hpp
        string_manip.hpp
        timing_session.hpp
        transform_iterator.cpp
        transform_iterator.hpp
        typelist.cpp
        typelist.hpp
        utilities.hpp)

install(FILES ${HEADER_FILES} DESTINATION ~/area51/)