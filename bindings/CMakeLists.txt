cmake_minimum_required(VERSION 3.15...3.30)
project(gdrp LANGUAGES CXX)

include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)
CPMAddPackage("gh:pybind/pybind11#a2e59f0")

set(PYBIND11_FINDPYTHON ON)


pybind11_add_module(gdrp MODULE src/rrp_bindings.cpp)
target_link_libraries(gdrp PUBLIC rrp)

install(TARGETS gdrp LIBRARY DESTINATION .)
