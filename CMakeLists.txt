cmake_minimum_required(VERSION 3.5)
project(area51)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -lc++abi -Wall -Wextra -pedantic-errors -std=c++1z")

add_subdirectory(src)

option(BUILD_TESTS "Enabling option will build tests" ON)
option(BUILD_DEMOS "Enabling option will build demos" ON)

if (${BUILD_TESTS})
    add_subdirectory(tests)
endif()

if (${BUILD_DEMOS})
    add_subdirectory(demos)
endif()
