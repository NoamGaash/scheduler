#include "utils/readCSV.cpp"
#include "utils/data.cpp"
#include "utils/operators.cpp"
#include "utils/timing.cpp"
#include "algo/naive_solution.cpp"
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

int dp_solution(Data& d) {
    int n = d.jobs.size();
    int P = 0;
    for(const auto& job : d.jobs) {
        P += job.processing_time;
    }

    // initialize dp table
    int** dp = new int*[n+1];
    for(int i = 0; i <= n; i++) {
        dp[i] = new int[P+1];
        for(int j = 0; j <= P; j++) {
            dp[i][j] = 0;
        }
    }

    // fill dp table - TODO

    return dp[n][P];
}

void process_example_file() {
    string filename = "input.csv";
    Data d(readCSV(filename));

    d.sort_by_descending_due_to();
    cout << "Cost before algo: " << d.cost(d.jobs) << endl;

    time_measure([&d]() {
        d.jobs = naive_solution(d, d.jobs.size());
    });

    cout << "Cost after algo: " << d.cost(d.jobs) << endl;
}

void process_generated_data() {
    int njobs = 7;
    int p_max = 10;
    float alpha = 1;
    Data d(njobs, p_max, alpha);

    d.sort_by_descending_due_to();
    cout << "Cost before algo: " << d.cost(d.jobs) << endl;

    time_measure([&d]() {
        d.jobs = naive_solution(d, d.jobs.size());
    });

    cout << "Cost after algo: " << d.cost(d.jobs) << endl;
}

int main() {
    process_example_file();
    process_generated_data();

    return 0;
}
