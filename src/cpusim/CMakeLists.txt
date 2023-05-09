cmake_minimum_required(VERSION 3.11)

add_library(cpusim)

target_sources(cpusim PRIVATE
    circuit.cpp
    gate.cpp
    state_vector.cpp
)
target_link_libraries(cpusim PRIVATE core)
target_include_directories(cpusim PRIVATE ${PROJECT_SOURCE_DIR}/src)
