# Tests use executables linked with the library
add_executable(test_vector test_vector.cpp "test_matrix.cpp")
target_link_libraries(test_vector PRIVATE mymath)

add_test(NAME TestVector COMMAND test_vector)