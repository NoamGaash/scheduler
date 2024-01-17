#include <iostream>
#include <algorithm>
#include <vector>
#include "../utils/data.cpp"

int dp_solution(Data &data, bool verbose = false)
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

    // print dp table
    if (verbose)
    {
        for (int i = 0; i < dp_rows; i++)
        {
            for (int j = 0; j < dp_cols; j++)
            {
                cout << f[i][j] << "\t";
            }
            cout << endl;
        }
    }

    const auto result = f[0][0];
    for (int i = 0; i < dp_rows; i++)
    {
        delete[] f[i];
    }
    delete[] f;

    return result;
}
