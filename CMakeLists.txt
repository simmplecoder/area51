cmake_minimum_required(VERSION 3.6)
project(custom_library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES
        timing_session.hpp
        fast_find.hpp
        main.cpp
        random_engine.hpp
        scope_exit.hpp custom_mpl.hpp typelist.hpp string_manip.hpp numerical.hpp prime_numbers.hpp containers.hpp circular_buffer.hpp iterator.hpp)

add_executable(custom_library ${SOURCE_FILES})