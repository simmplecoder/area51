cmake_minimum_required(VERSION 3.5)
project(area51)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -lc++abi -Wall -Wextra -pedantic-errors -std=c++1z")

add_subdirectory(tests)
add_subdirectory(demos)
add_subdirectory(src)