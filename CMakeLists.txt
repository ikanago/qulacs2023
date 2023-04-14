cmake_minimum_required(VERSION 3.0)

project(qulacs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(ExternalProject)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_script/FetchContent.cmake)

### Define variables ###
if(NOT DEFINED USE_PYTHON)
    set(USE_PYTHON No)
endif(NOT DEFINED USE_PYTHON)

message(STATUS "USE_PYTHON = ${USE_PYTHON}")

### Fetch dependencies ###
# pybind11
if(USE_PYTHON)
    FetchContent_Declare(
        pybind11_fetch
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG v2.10.0
    )
    FetchContent_GetProperties(pybind11_fetch)
    if(NOT pybind11_fetch_POPULATED)
        message(STATUS "Fetch pybind11 for python-binding")
        FetchContent_Populate(pybind11_fetch)
        add_subdirectory(${pybind11_fetch_SOURCE_DIR})
    endif(NOT pybind11_fetch_POPULATED)
endif(USE_PYTHON)

add_subdirectory(python)
add_subdirectory(src)
