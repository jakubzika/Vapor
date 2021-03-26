cmake_minimum_required(VERSION 3.11-3.18)

project(main)

link_directories($ENV{PGR_FRAMEWORK_ROOT}lib)

add_executable(main main.cpp)

include_directories($ENV{PGR_FRAMEWORK_ROOT}include)
include_directories("../Vapor")

target_link_libraries(main Vapor)
target_link_libraries(main "pgrd.lib")

target_compile_features(main PUBLIC cxx_std_20)