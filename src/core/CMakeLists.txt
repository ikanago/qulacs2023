cmake_minimum_required(VERSION 3.0)

set(SOURCE_FILES
    ops.cpp
)

add_library(core STATIC ${SOURCE_FILES})
target_include_directories(core PRIVATE ${PROJECT_SOURCE_DIR}/src/core)
