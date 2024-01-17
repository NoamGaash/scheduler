#include <iostream>
#include <algorithm>
#include <vector>
#include "../utils/data.cpp"

using namespace std;

vector<Job> backtrack(int **f, vector<Job> jobs, int P)
{
    int n = jobs.size();
    int l = 0;
    int j = 0;
    vector<Job> early_jobs;
    vector<Job> late_jobs;
    while (j < n)
    {
        const auto &job = jobs[j];
        const auto &p = job.processing_time;
        const auto &d = job.due_to;
        if (d >= P - l)
        {
            early_jobs.push_back(job);
        }
        else
        {
            const auto &s = (P - l - p); 
            if(f[j][l] == p + f[j+1][l])
            {
                early_jobs.push_back(job);
            }
            else
            {
                late_jobs.insert(late_jobs.begin(), job);
                l += p;
            }
        }
        j++;
    }
    early_jobs.insert(early_jobs.end(), late_jobs.begin(), late_jobs.end());
    return early_jobs;
}

int dp_backtrack_solution(Data &data, bool verbose = false)
{
    data.sort_by_descending_due_to();
    int n = data.jobs.size();
    int P = 0;
    for (const auto &job : data.jobs)
    {
        P += job.processing_time;
    }

    int dp_rows = n + 1, dp_cols = P+1;

    // initialize dp table
    int **f = new int *[dp_rows];
    for (int i = 0; i < dp_rows; i++)
    {
        f[i] = new int[dp_cols];
        for (int j = 0; j <= P; j++)
        {
            f[i][j] = 0;
        }
    }

    for (int j = n - 2; j >= -1; j--)
    {
        const auto &p = data.jobs[j + 1].processing_time;
        const auto &d = data.jobs[j + 1].due_to;
        for (int l = P-p; l >= 0; l--)
        {

            if (d >= P - l)
            {
                f[j + 1][l] = p + f[j + 2][l];
            }
            else
            {
                const auto &s = (P - l - p); // start time of job j+1 if it added to the late jobs
                f[j + 1][l] = min(
                    p + f[j + 2][l],
                    min(max(0, d - s), p) + f[j + 2][l + p]
                );
            }
        }
    }

    data.jobs = backtrack(f, data.jobs, P);

    const auto result = f[0][0];
    for (int i = 0; i < dp_rows; i++)
    {
        delete[] f[i];
    }
    delete[] f;

    return result;
}
