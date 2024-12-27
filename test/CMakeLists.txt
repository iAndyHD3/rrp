
# Add an executable with the above sources
add_executable(rrp_test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
# link the new hello_library target with the hello_binary target
target_link_libraries(rrp_test PRIVATE rrp)