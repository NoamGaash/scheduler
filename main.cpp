#include "utils/readCSV.cpp"
#include "utils/data.cpp"
# include <vector>
# include <numeric>
#include <functional>

using namespace std;

// operator overloading
vector<Job> operator+(const vector<Job>& a, const Job& b) {
    vector<Job> c = a;
    c.push_back(b);
    return c;
}

void time_measure(const std::function<void()>& f) {
    clock_t start = clock();
    f();
    clock_t end = clock();
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC * 1000  << "ms" << endl;
}

vector<Job> badSolution(Data& d, int j, vector<Job> start = {}, vector<Job> end = {}) {
    if(j == 0) {
        // concatenate start and end
        vector<Job> solution = start;
        solution.insert(solution.end(), end.begin(), end.end());
        return solution;
    }

    vector<Job> solution1 = badSolution(d, j-1, start + d.jobs[j-1], end);
    vector<Job> solution2 = badSolution(d, j-1, start, end + d.jobs[j-1]);

    int solution1_cost = 0, time = 0;
    for(const auto& job : solution1) {
        solution1_cost += job.cost(time);
        time += job.processing_time;
    }

    int solution2_cost = 0;
    time = 0;
    for(const auto& job : solution2) {
        solution2_cost += job.cost(time);
        time += job.processing_time;
    }

    return solution1_cost > solution2_cost ? solution2 : solution1;
}

void process_example_file() {
    string filename = "input.csv";
    Data d(readCSV(filename));

    d.sort_by_descending_due_to();
    // d.display();
    cout << "Cost before algo: " << d.cost(d.jobs) << endl;

    time_measure([&d]() {
        d.jobs = badSolution(d, d.jobs.size());
    });

    // d.display();
    cout << "Cost after algo: " << d.cost(d.jobs) << endl;
}

int main() {
    process_example_file();

    return 0;
}
