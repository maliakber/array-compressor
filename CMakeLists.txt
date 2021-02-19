cmake_minimum_required(VERSION 3.5)

project(data-compressor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} \
    -fopenmp \
    -march=native \
    -mavx \
    -Wall"
)
set( CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} \
    -fprofile-arcs -ftest-coverage \
    -g \
    -O0"
)
set( CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE} \
    -Ofast"
)

add_subdirectory(src)
