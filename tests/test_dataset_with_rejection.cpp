#include <gtest/gtest.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../src/utils/data.h"
#include "../src/utils/readCSV.h"
#include "../src/algo/dp_solution.h"
// #include "../src/utils/timing.h"
// #include "../src/utils/stddev.h"
// #include <vector>
// #include <numeric>
// #include <cmath>

// using namespace std;
// using namespace std::filesystem;

// class SchedulerTest : public ::testing::Test {
// protected:
//     void SetUp() override {
//         if (data.empty()) {
//             data = "data_rejection";
//         }
//     }

//     void RunTest(const std::filesystem::path& data) {
//         vector<double> times;

//         for (auto const &dir_entry : directory_iterator{data}) {
//             string input = dir_entry.path().string() + "/input.csv";
//             string output = dir_entry.path().string() + "/output.txt";
//             auto d = RejectableJobCollection(readCSV(input));
//             int result = 0;
//             auto time = time_measure([&d, &result]()
//                                      { result = dp_solution(d); });
//             times.push_back(time);
//             auto output_file = ifstream(output);
//             int expected_result;
//             output_file >> expected_result;
//             EXPECT_EQ(result, expected_result) << "On file " << input;
//         }

//         cout << "Average time: " << accumulate(times.begin(), times.end(), 0.0) / times.size() << " seconds" << endl;
//         cout << "stddev: " << stddev(times.begin(), times.end()) << endl;
//     }

//     std::filesystem::path data;
// };

// TEST_F(SchedulerTest, TestWithRejection) {
//     RunTest(data);
// }
