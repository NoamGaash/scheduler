#include <iostream>
#include <algorithm>
#include <vector>
#include "../utils/data.cpp"
#include "../utils/arrays.cpp"

int dp_solution(Data &data, bool verbose = false)
{
    data.sort_by_descending_due_to();
    int n = data.jobs.size();
    int P = data.P();

    int dp_rows = n + 1, dp_cols = P+1;

    // initialize dp table
    int **f = zeroes(dp_rows, dp_cols);

    for (int j = n - 2; j >= -1; j--)
    {
        const auto &p = data.jobs[j + 1].processing_time;
        const auto &d = data.jobs[j + 1].due_to;
        for (int l = P-p; l >= 0; l--)
        {

            if (d >= P - l)
            {
                f[j + 1][l] = p + f[j + 2][l]; // forward will be f[j - 1][l];
            }
            else
            {
                const auto &s = (P - l - p); // start time of job j+1 if it added to the late jobs
                f[j + 1][l] = min(
                    p + f[j + 2][l],
                    min(max(0, d - s), p) + f[j + 2][l + p] // forward will be f[j - 1][l - p]
                );
            }
        }
    }

    // print dp table
    if (verbose)
    {
        print_array(f, dp_rows, dp_cols);
    }

    const auto result = f[0][0];
    delete_array(f, dp_rows);
    return result;
}

/**
 * calculate the optimal cost of total early work (for accepted jobs) and rejection cost (for rejected jobs)
*/
int dp_solution(RejectableData &data, bool verbose = false)
{
    /**
     * we sort the jobs by descending due_to, because we want to process the late jobs first
    */
    data.sort_by_descending_due_to();
    int n = data.jobs.size();
    int P = data.P();
    int R = data.R();

    int dp_rows = n + 1, dp_cols = P+1, dp_depth =P+1;

    int ***f = zeroes(dp_depth, dp_cols, dp_rows);

    for(int layer = n-1; layer >= 0; layer--)
    {
        for (int j = n - 2; j >= -1; j--)
        {
            const auto &p = data.jobs[j].processing_time;
            const auto &d = data.jobs[j].due_to;
            const auto &e = data.jobs[j].recection_cost;

            /**
             * for each job, f[layer][j][l] is the minimum cost of processing the jobs j, j+1, ..., n-1
             * under the assumption that the sum of all late jobs' processing times in the range [1, j] is l
             * and the total processing time of the rejected jobs in the range [1, j] is layer
            */
            for (int l = P-p; l >= 0; l--) // the `-p` is because the current job isn't yet added to the set of late jobs
            {
                if (d >= P - l)
                {
                     // if job j ends before its due date, then it will be fully early and the entire processing time will be added to cost
                    f[layer][j + 1][l] = p + f[layer][j + 2][l];
                }
                else
                {
                    const auto &s = (P - l - p); // start time of job j+1 if it added to the late jobs
                    f[layer][j + 1][l] = min(
                            p + f[layer][j + 2][l],
                            min(max(0, d - s), p) + f[layer][j + 2][l + p]
                        );
                }
                // f[layer][j + 1][l] = min(
                //     f[layer][j + 1][l],
                //     f[layer+1][j + 2][l] + data.jobs[j+2].recection_cost
                // );
            }
        }
    }

    if (verbose)
    {
        print_array(f, dp_rows, dp_cols, dp_depth);
        print_array(f[0], dp_cols, dp_depth);
    }

    const auto result = f[0][0][0];
    cout << "!!! " << result << endl;
    delete_array(f, dp_rows, dp_cols);
    return result;
}

