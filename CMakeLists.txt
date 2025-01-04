cmake_minimum_required(VERSION 3.5)

project(rrp)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(rrp STATIC src/rrp.cpp)

target_include_directories(rrp PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(rrp PUBLIC cxx_std_23)






if(RRP_ENABLE_MATJSON)
include(${CMAKE_SOURCE_DIR}/CPM.cmake)
CPMAddPackage("gh:geode-sdk/json#82b1552")
target_link_libraries(rrp PUBLIC mat-json)

endif()

if(PROJECT_IS_TOP_LEVEL)

add_subdirectory(test)

endif()