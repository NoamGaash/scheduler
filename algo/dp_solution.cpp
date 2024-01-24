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

int dp_solution(RejectableData &data, bool verbose = false)
{
    data.sort_by_descending_due_to();
    int n = data.jobs.size();
    int P = 0;
    for (const auto &job : data.jobs)
    {
        P += job.processing_time;
    }

    int dp_rows = n + 1, dp_cols = P+1, dp_depth =n+1;

    // initialize dp table
    int ***f = new int **[dp_depth];
    for (int i = 0; i < dp_depth; i++)
    {
        f[i] = new int *[dp_rows];
        for (int j = 0; j < dp_rows; j++)
        {
            f[i][j] = new int[dp_cols];
            for (int k = 0; k <= P; k++)
            {
                f[i][j][k] = 0;
            }
        }
    }

    for(int layer = n-1; layer >= 0; layer--)
    {
        for (int j = n - 2; j >= -1; j--)
        {
            const auto &p = data.jobs[j].processing_time;
            const auto &d = data.jobs[j].due_to;
            const auto &r = data.jobs[j].recection_cost;
            for (int l = P-p; l >= 0; l--)
            {
                if (d >= P - l)
                {
                    f[layer][j + 1][l] = p + f[layer+1][j + 2][l];
                }
                else
                {
                    const auto &s = (P - l - p); // start time of job j+1 if it added to the late jobs
                    f[layer][j + 1][l] = min(
                        // first option - don't reject job j+2 (same as in the non-rejectable case)
                        min(
                            p + f[layer][j + 2][l],
                            min(max(0, d - s), p) + f[layer][j + 2][l + p]
                        ),
                        // second option - reject job j+2
                        f[layer+1][j + 2][l] + data.jobs[j+2].recection_cost
                    );
                }
            }
        }
    }

    // print dp table
    if (verbose)
    {
        for(int layer = n-1; layer >= 0; layer--)
        {
            cout << "Layer " << layer << endl;
            for (int i = 0; i < dp_rows; i++)
            {
                for (int j = 0; j < dp_cols; j++)
                {
                    cout << f[layer][i][j] << "\t";
                }
                cout << endl;
            }
        }
    }

    const auto result = f[0][0][0];
    for(int layer = n-1; layer >= 0; layer--)
    {
        for (int i = 0; i < dp_rows; i++)
        {
            delete[] f[layer][i];
        }
        delete[] f[layer];
    }
    delete[] f;

    return result;
}

