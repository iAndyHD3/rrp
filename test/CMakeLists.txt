
# Add an executable with the above sources
add_executable(rrp_test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
# link the new hello_library target with the hello_binary target
target_compile_features(rrp_test PRIVATE cxx_std_23)

target_link_libraries(rrp_test PRIVATE rrp)

target_compile_definitions(rrp_test PRIVATE RRP_TEST_SOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}")