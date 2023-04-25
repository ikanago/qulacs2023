cmake_minimum_required(VERSION 3.11)

add_library(cpusim)

target_sources(cpusim PRIVATE
    state_vector.cpp
)
target_include_directories(cpusim PRIVATE ${PROJECT_SOURCE_DIR}/src/cpusim)
