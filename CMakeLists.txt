# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    VscodeCmakeHello
    VERSION 0.1
    DESCRIPTION "Small CMake example built with VSCode")

add_subdirectory(Vapor)
add_subdirectory(Game)
add_subdirectory(Data)