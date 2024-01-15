#include "utils/readCSV.cpp"
#include "utils/data.cpp"
#include "utils/operators.cpp"
#include "utils/timing.cpp"
#include "algo/naive_solution.cpp"
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

int dp_solution(Data& data) {
    int n = data.jobs.size();
    int P = 0;
    for(const auto& job : data.jobs) {
        P += job.processing_time;
    }

    // initialize dp table
    int** f = new int*[n+1];
    for(int i = 0; i <= n; i++) {
        f[i] = new int[P+1];
        for(int j = 0; j <= P; j++) {
            f[i][j] = 0;
        }
    }

    for(int j=n-2; j>=-1; j--) {
        for(int l=P; l>=0; l--) {
            const auto& p = data.jobs[j+1].processing_time;
            const auto& d = data.jobs[j+1].due_to;

            if(d >= P - l) {
                f[j+1][l] = p + f[j+2][l];
            } else {
                const auto &s = (P - l - p); // start time of job j+1 if it added to the late jobs
                f[j+1][l] = min(
                    p + f[j+2][l],
                    min(
                        max(0, d - s),
                        p
                    ) + f[j+2][l+p]
                );
            }
        }
    }

    // print dp table
    for(int i = 0; i < n+1; i++) {
        for(int j = 0; j <= P; j++) {
            cout << f[i][j] << "\t";
        }
        cout << endl;
    }

    const auto result = f[0][0];
    for(int i = 0; i < n+1; i++) {
        delete[] f[i];
    }
    delete[] f;

    return result;
}

void process_example_file() {
    string filename = "input.csv";
    Data d(readCSV(filename));

    d.sort_by_descending_due_to();
    cout << "Cost before algo: " << d.cost(d.jobs) << endl;
    double result = 0;
    double time = time_measure([&d, &result]() {
        // d.jobs = naive_solution(d, d.jobs.size());
        result = dp_solution(d);
    });

    cout << "Time: " << time << endl;
    cout << "Cost after algo: " << result << endl;
    cout << d << endl;
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
    // process_generated_data();

    return 0;
}
