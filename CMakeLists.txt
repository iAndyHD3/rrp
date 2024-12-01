cmake_minimum_required(VERSION 3.5)

project(rrp)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(rrp STATIC src/rrp.cpp)

target_include_directories(rrp PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(rrp PUBLIC cxx_std_20)


if(PROJECT_IS_TOP_LEVEL)

add_subdirectory(test)
endif()


include(FetchContent)
FetchContent_Declare(
  PEGTL
  GIT_SHALLOW    TRUE
  GIT_REPOSITORY https://github.com/taocpp/PEGTL
  GIT_TAG        d7b821b1e5ed6ab321625f50427c4ae0b78909d5
)
FetchContent_MakeAvailable(PEGTL)

target_link_libraries(rrp PUBLIC pegtl)