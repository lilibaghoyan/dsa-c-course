add_executable(test_add test_add.c)
target_link_libraries(test_add PRIVATE dsalib)

add_test(NAME test_add COMMAND test_add)
