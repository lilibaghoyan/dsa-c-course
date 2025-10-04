# test_add
add_executable(test_add test_add.c)
target_link_libraries(test_add PRIVATE dsalib)
add_test(NAME test_add COMMAND test_add)

# test_linear_search
add_executable(test_linear_search test_linear_search.c)
target_link_libraries(test_linear_search PRIVATE dsalib)
add_test(NAME test_linear_search COMMAND test_linear_search)

# test_binary_search
add_executable(test_binary_search test_binary_search.c)
target_link_libraries(test_binary_search PRIVATE dsalib)
add_test(NAME test_binary_search COMMAND test_binary_search)
