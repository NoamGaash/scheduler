#include <iostream>
#include <algorithm>
#include <vector>
#include "../utils/data.h"
#include "dp_solution.h"

using namespace std;


// vector to string
ostream &operator<<(ostream &os, const vector<int> &v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}


vector<int> *backtrack(int **f, vector<Job> &jobs, int P)
{
    int n = jobs.size();
    int l = 0;
    int j = 0;
    vector<int> early_jobs;
    vector<int> late_jobs;
    while (j < n)
    {
        const auto &job = jobs[j];
        const auto &p = job.processing_time;
        const auto &d = job.due_to;
        if (d >= P - l)
        {
            early_jobs.push_back(job.id);
        }
        else
        {
            const auto &s = (P - l - p); 
            if(f[j][l] == p + f[j+1][l])
            {
                early_jobs.push_back(job.id);
            }
            else
            {
                late_jobs.insert(late_jobs.begin(), job.id);
                l += p;
            }
        }
        j++;
    }
    early_jobs.insert(early_jobs.end(), late_jobs.begin(), late_jobs.end());
    return new vector<int>[2]{early_jobs, late_jobs};
}

int dp_backtrack_solution(JobCollection &data, bool verbose = false)
{
    return dp_solution(data, verbose, [](int **f, vector<Job> jobs, int P)
    {
        auto result = backtrack(f, jobs, P);
        auto early_jobs = result[0];
        auto late_jobs = result[1];
        cout << "Early jobs: " << early_jobs << endl;
        cout << "Late jobs: " << late_jobs << endl;
    });
}
