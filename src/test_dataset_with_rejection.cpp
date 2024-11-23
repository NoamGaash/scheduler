#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "utils/data.h"
#include "utils/readCSV.h"
#include "algo/dp_solution.h"
#include "utils/timing.h"
#include "utils/stddev.h"
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;
using namespace std::filesystem;

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        argv[1] = "data_rejection";
        argc = 2;
    }
    const std::filesystem::path data{argv[1]};
    vector<double> times;

    for (auto const &dir_entry : directory_iterator{data})
    {
        string input = dir_entry.path().string() + "/input.csv";
        string output = dir_entry.path().string() + "/output.txt";
        auto d = RejectableJobCollection(readCSV(input));
        int result = 0;
        auto time = time_measure([&d, &result]()
                                 { result = dp_solution(d); });
        times.push_back(time);
        auto output_file = ifstream(output);
        int expected_result;
        output_file >> expected_result;
        if(result != expected_result)
        {
            cout << "On file " << input << endl;
            cout << "ERROR: result != expected_result" << endl;
            cout << "Expected result: " << expected_result << endl;
            cout << "Result: " << result << endl;
            return 1;
        }
    }
    cout << "All tests passed!" << endl;
    cout << "Average time: " << accumulate(times.begin(), times.end(), 0.0) / times.size() << " seconds" << endl;
    cout << "stddev: " << stddev(times.begin(), times.end()) << endl;
    return 0;
}
