cmake_minimum_required(VERSION 3.11)

enable_testing()

add_executable(cpusim_test EXCLUDE_FROM_ALL
    state_vector_test.cpp
)

target_link_libraries(cpusim_test PRIVATE
    cpusim
    GTest::gtest_main
)
target_include_directories(cpusim_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
