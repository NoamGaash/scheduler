cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find Google Test
find_package(GTest REQUIRED)

# Add your source files
add_executable(my_project main.cpp)

# Add test executable
add_executable(test_exe tests/hello_world_test.cpp)

# Link gtest to the test executable
target_link_libraries(test_exe GTest::GTest GTest::Main pthread)
