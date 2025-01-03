cmake_minimum_required(VERSION 3.5)

project(rrp)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(rrp STATIC src/rrp.cpp include/rrp/rrp.hpp include/rrp/rrp_glaze.hpp)

target_include_directories(rrp PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(rrp PUBLIC cxx_std_23)


if(PROJECT_IS_TOP_LEVEL)

add_subdirectory(test)

endif()

if(RRP_ENABLE_GLAZE)
include(CPM.cmake)
CPMAddPackage("gh:stephenberry/glaze#e652b11")
target_link_libraries(rrp PUBLIC glaze::glaze)


endif()