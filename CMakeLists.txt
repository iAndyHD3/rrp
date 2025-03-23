cmake_minimum_required(VERSION 3.5)

project(rrp)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources

add_library(rrp STATIC src/rrp.cpp)
target_include_directories(rrp PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(rrp PRIVATE cxx_std_23)

if(PROJECT_IS_TOP_LEVEL)
set(RRP_ENABLE_MATJSON TRUE)
set(RRP_TEST TRUE)
endif()


if(RRP_ENABLE_MATJSON)
include(cmake/CPM.cmake)
CPMAddPackage("gh:geode-sdk/json#82b1552")
target_link_libraries(rrp PUBLIC mat-json)

endif()

if(RRP_TEST)

add_subdirectory(test)

endif()

if(RRP_PYTHON)

add_subdirectory(bindings)

endif()



