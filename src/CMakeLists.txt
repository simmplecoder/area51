cmake_minimum_required(VERSION 3.5)
project(area51)

set(HEADER_FILES algorithm.hpp
        benchmark-formatters/def_formatter.hpp
        benchmark.hpp
        benchmark_streamer.hpp
        benchmark_v2.hpp
        circular_buffer.hpp
        containers.hpp
        custom_mpl.hpp
        deduce_first_parameter.hpp
        deduce_single_parameter.hpp
        explode_tuple.hpp
        fast_find.hpp
        formatted_read.hpp
        generators/int_vector_generator.hpp
        input_digit_iterator.hpp
        iterator.hpp
        member_callback.hpp
        numerical.hpp
        prime_numbers.hpp
        random_int_generator.hpp
        random_selector.hpp
        regular_callable.hpp
        result_cache.hpp
        scope_exit.hpp
        sliding_window.hpp
        sort.hpp
        string_manip.hpp
        timing_session.hpp
        transform_iterator.hpp
        typelist.hpp
        utilities.hpp)


install(FILES ${HEADER_FILES} DESTINATION ~/area51/)

add_library(area51 INTERFACE)
#install(TARGETS ${HEADER_FILES} DESTINATION ~/area51/ EXPORT area51-targets)
#install(EXPORT area51-targets DESTINATION~/area51)

target_include_directories(area51 INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include/area51>
        )

install(TARGETS area51 EXPORT area51-export)
install(EXPORT area51-export DESTINATION lib/cmake/area51)

set(HEADERS_PATH "")

foreach(file ${HEADER_FILES})
    set(HEADERS_PATH "${HEADERS_PATH};${CMAKE_CURRENT_SOURCE_DIR}/${file}")
endforeach()

install(FILES
        ${HEADERS_PATH}
        DESTINATION include/area51
        )