cmake_minimum_required(VERSION 3.12...3.24)

project(
    AdventOfCode
    VERSION 1.0.0
    DESCRIPTION "2022 Solutions for Advent of Code."
    LANGUAGES C CXX)

include(FetchContent)

# fmt library
FetchContent_Declare(
    fmtlib
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.0.0)
FetchContent_MakeAvailable(fmtlib)

configure_file (
    "${PROJECT_SOURCE_DIR}/include/paths.h.in"
    "${PROJECT_BINARY_DIR}/include/paths.h"
)

add_subdirectory(src/utils)

add_subdirectory(src/day1)
add_subdirectory(src/day2)
add_subdirectory(src/day3)
add_subdirectory(src/day4)
add_subdirectory(src/day5)
add_subdirectory(src/day6)
add_subdirectory(src/day7)
add_subdirectory(src/day8)
add_subdirectory(src/day9)
add_subdirectory(src/day10)
add_subdirectory(src/day11)
add_subdirectory(src/day12)
add_subdirectory(src/day13)
add_subdirectory(src/day14)
add_subdirectory(src/day15)
add_subdirectory(src/day16)
add_subdirectory(src/day17)
add_subdirectory(src/day18)
add_subdirectory(src/day19)
add_subdirectory(src/day20)
add_subdirectory(src/day21)
add_subdirectory(src/day22)
add_subdirectory(src/day23)
add_subdirectory(src/day24)
add_subdirectory(src/day25)
