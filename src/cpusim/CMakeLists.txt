cmake_minimum_required(VERSION 3.0)

set(SOURCE_FILES
    state_vector.cpp
)

add_library(cpusim STATIC ${SOURCE_FILES})
target_include_directories(cpusim PRIVATE ${PROJECT_SOURCE_DIR}/src/cpusim)
