# Find GoogleTest (requires it to be installed)
find_package(GTest REQUIRED)

# Create test executables and link libraries
add_executable(job_test job_test.cpp)
target_link_libraries(job_test PRIVATE scheduler_lib GTest::GTest GTest::Main)

add_executable(test_JobCollection test_JobCollection.cpp)
target_link_libraries(test_JobCollection PRIVATE scheduler_lib GTest::GTest GTest::Main)

add_executable(test_RejectableJobCollection test_RejectableJobCollection.cpp)
target_link_libraries(test_RejectableJobCollection PRIVATE scheduler_lib GTest::GTest GTest::Main)

add_executable(test_RejectableJob test_RejectableJob.cpp)
target_link_libraries(test_RejectableJob PRIVATE scheduler_lib GTest::GTest GTest::Main)

# Enable testing and register tests
enable_testing()
add_test(NAME job_test COMMAND job_test)
add_test(NAME test_JobCollection COMMAND test_JobCollection)
add_test(NAME test_RejectableJobCollection COMMAND test_RejectableJobCollection)
add_test(NAME test_RejectableJob COMMAND test_RejectableJob)
