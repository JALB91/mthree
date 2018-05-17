cmake_minimum_required (VERSION 2.6)
project (mthree)

set (CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
    )

add_executable(mthree ${SOURCES})
