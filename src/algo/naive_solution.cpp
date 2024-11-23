#include <vector>
#include <numeric>
#include <functional>
#include "../utils/data.h"

using namespace std;

vector<Job> naive_solution(JobCollection& d, int j, vector<Job> start = {}, vector<Job> end = {}) {
    return d.jobs;
    // if(j == 0) {
    //     // concatenate start and end
    //     vector<Job> solution = start;
    //     solution.insert(solution.end(), end.begin(), end.end());
    //     return solution;
    // }

    // vector<Job> solution1 = naive_solution(d, j-1, start + d.jobs[j-1], end);
    // vector<Job> solution2 = naive_solution(d, j-1, start, end + d.jobs[j-1]);

    // int solution1_cost = 0, time = 0;
    // for(const auto& job : solution1) {
    //     solution1_cost += job.cost(time);
    //     time += job.processing_time;
    // }

    // int solution2_cost = 0;
    // time = 0;
    // for(const auto& job : solution2) {
    //     solution2_cost += job.cost(time);
    //     time += job.processing_time;
    // }

    // return solution1_cost > solution2_cost ? solution2 : solution1;
}

