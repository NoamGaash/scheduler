#include "utils/readCSV.cpp"
#include "utils/data.cpp"
# include <vector>
# include <numeric>

using namespace std;

// operator overloading
vector<Job> operator+(const vector<Job>& a, const Job& b) {
    vector<Job> c = a;
    c.push_back(b);
    return c;
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

int main() {
    string filename = "input.csv";
    Data d(readCSV(filename));

    d.sort_by_descending_due_to();
    d.display();

    d.jobs = badSolution(d, d.jobs.size());
    d.display();

    return 0;
}
