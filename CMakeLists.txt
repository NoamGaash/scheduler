cmake_minimum_required(VERSION 3.10)

# Project name
project(Scheduler VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for source and tests
add_subdirectory(src)
add_subdirectory(tests)
enable_testing()
