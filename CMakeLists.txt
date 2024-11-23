cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find Google Test
find_package(GTest REQUIRED)

# Collect all test files
file(GLOB TEST_FILES tests/*.cpp)

# Add executable for tests
add_executable(test_exe ${TEST_FILES})

# Link gtest to the test executable
target_link_libraries(test_exe GTest::GTest GTest::Main pthread)
