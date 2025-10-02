cmake_minimum_required(VERSION 3.16)
project(my_project C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create library
add_library(dsalib src/add.c)
target_include_directories(dsalib PUBLIC include)

# Enable testing
enable_testing()
add_subdirectory(tests)
