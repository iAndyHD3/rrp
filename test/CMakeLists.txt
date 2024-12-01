
# Add an executable with the above sources
add_executable(rrp_test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
# link the new hello_library target with the hello_binary target
target_link_libraries(rrp_test PRIVATE rrp)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(rrp_test PRIVATE Catch2::Catch2WithMain)
