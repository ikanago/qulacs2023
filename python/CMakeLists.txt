cmake_minimum_required(VERSION 3.0)

pybind11_add_module(qulacs SHARED EXCLUDE_FROM_ALL binding.cpp)
target_link_libraries(qulacs PUBLIC core)
target_link_libraries(qulacs PUBLIC cpusim)
