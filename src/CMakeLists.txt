# Add all source files
add_library(scheduler_lib
    algo/dp_backtracking_solution.cpp
    algo/dp_solution.cpp
    algo/naive_solution.cpp
    utils/arrays.cpp
    utils/data.cpp
    utils/operators.cpp
    utils/readCSV.cpp
    utils/stddev.cpp
    utils/timing.cpp
    utils/write_csv.cpp
    utils/model/Job.cpp
    utils/model/JobCollection.cpp
    utils/model/RejectableJob.cpp
    utils/model/RejectableJobCollection.cpp
)

# Include headers
target_include_directories(scheduler_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add the main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE scheduler_lib)

# Add other executables for testing or performance
add_executable(test_dataset test_dataset.cpp)
target_link_libraries(test_dataset PRIVATE scheduler_lib)

add_executable(test_dataset_with_rejection test_dataset_with_rejection.cpp)
target_link_libraries(test_dataset_with_rejection PRIVATE scheduler_lib)

add_executable(test_performance test_performance.cpp)
target_link_libraries(test_performance PRIVATE scheduler_lib)
