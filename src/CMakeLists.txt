cmake_minimum_required(VERSION 3.5)
project(area51)

set(HEADER_FILES algorithm.hpp
        containers.hpp
        explode_tuple.cpp
        iterator.hpp
        random_int_generator.hpp
        sliding_window.hpp
        typelist.cpp
        benchmark.hpp
        custom_mpl.hpp
        explode_tuple.hpp
        member_callback.hpp
        random_selector.hpp
        string_manip.hpp
        typelist.hpp
        benchmark_streamer.hpp
        deduce_first_parameter.hpp
        fast_find.hpp
        numerical.cpp
        regular_callable.hpp
        timing_session.hpp
        utilities.hpp
        benchmark_v2.hpp
        deduce_single_parameter.cpp
        formatted_read.hpp
        numerical.hpp
        scope_exit.hpp
        transform_iterator.cpp
        circular_buffer.hpp
        deduce_single_parameter.hpp
        input_digit_iterator.hpp
        prime_numbers.hpp
        sliding_window.cpp
        transform_iterator.hpp)

install(FILES ${HEADER_FILES} DESTINATION ~/area51/)