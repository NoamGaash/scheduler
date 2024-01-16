#include "utils/readCSV.cpp"
#include "utils/data.cpp"
#include "utils/operators.cpp"
#include "utils/timing.cpp"
#include "algo/naive_solution.cpp"
#include "algo/dp_solution.cpp"
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

void process_example_file()
{
    string filename = "input.csv";
    Data d(readCSV(filename));

    cout << "Cost before algo: " << d.cost(d.jobs) << endl;
    d.sort_by_descending_due_to();
    double result = 0;
    double time = time_measure([&d, &result]()
                               {
        // d.jobs = naive_solution(d, d.jobs.size());
        result = dp_solution(d); });

    cout << "Time: " << time << endl;
    cout << "Cost after algo: " << result << endl;
    // cout << d << endl;
}

void process_generated_data()
{
    int njobs = 200;
    int p_max = 100;
    float alpha = 1;
    Data d(njobs, p_max, alpha);
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
    process_generated_data();

    return 0;
}
