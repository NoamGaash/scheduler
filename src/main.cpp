#include "utils/readCSV.h"
#include "utils/data.h"
#include "utils/operators.cpp"
#include "utils/timing.cpp"
#include "algo/naive_solution.cpp"
#include "algo/dp_solution.h"
#include "algo/dp_backtracking_solution.cpp"
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

void process_example_file()
{
    string filename = "datasets/input.csv";
    JobCollection d(readCSV(filename));

    cout << "Cost before algo: " << d.cost(d.jobs) << endl;
    d.sort_by_descending_due_to();
    double result = 0;
    double time = time_measure([&d, &result]()
                               {
        // d.jobs = naive_solution(d, d.jobs.size());
        result = dp_backtrack_solution(d); });
    cout << d << endl;
    cout << "Time: " << time << endl;
    cout << "Cost after algo: " << result << endl;
    // cout << d << endl;
}

void process_example_rejection_file()
{
    string filename = "datasets/input_with_rejection.csv";
    RejectableJobCollection d(readCSV(filename));

    cout << "Cost before algo: " << d.cost() << endl;
    d.sort_by_descending_due_to();
    double result = 0;
    double time = time_measure([&d, &result]()
                               {
        // d.jobs = naive_solution(d, d.jobs.size());
        result = dp_solution(d); });
    cout << d << endl;
    cout << "Time: " << time << endl;
    cout << "Cost after algo (with rejections): " << result << endl;
    // cout << d << endl;
}

void process_generated_data()
{
    int njobs = 200;
    int p_max = 100;
    float alpha = 1;
    JobCollection d(njobs, p_max, alpha);
    int result = 0;

    cout << "Cost before algo: " << d.cost(d.jobs) << endl;
    d.sort_by_descending_due_to();

    double time = time_measure([&d, &result]()
                               {
                    // d.jobs = naive_solution(d, d.jobs.size());
                    result = dp_solution(d); });

    cout << "Time: " << time << endl;
    cout << "Cost after algo: " << result << endl;
}

int main()
{
    srand(time(NULL));
    process_example_file();
    process_example_rejection_file();
    // process_generated_data();

    return 0;
}
