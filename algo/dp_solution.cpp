#include <iostream>
#include <algorithm>
#include <vector>
#include "../utils/data.cpp"
#include "../utils/arrays.cpp"

int dp_solution(Data &data, bool verbose = false)
{
    data.sort_by_ascending_due_to();
    int n = data.jobs.size();
    int P = data.P();

    int dp_rows = n + 1, dp_cols = P+1;

    // initialize dp table
    int **f = zeroes(dp_rows, dp_cols);

    for (int j = 0; j < n; j++)
    {
        // we have scheduled job 0 to j (1-indexed), now we should schedule job j+1
        const auto &p = data.jobs[j].processing_time;
        const auto &d = data.jobs[j].due_to;
        for (int l = 0; l <= P-p; l++)
        {
            // f_j(l) is the optimal early work can be achived by scheduling jobs 1...j
            // given that the rest of the n-j jobs have been scheduled and the total p of scheduled late jobs is l
            const auto &s = P - l - p; // start time of job j+1 if it added to the late jobs
            f[j+1][l] = min(
                p + f[j][l],
                min(max(0, d - s), p) + f[j][l + p]
            );
        }
    }

    // print dp table
    if (verbose)
    {
        print_array(f, dp_rows, dp_cols);
    }

    const auto result = f[n][0];
    delete_array(f, dp_rows);
    return result;
}

/**
 * In this function every job now has a new property, e, which represents the cost of rejecting the job.
 * This function introduces a third state variable, r, that represents the total processing time of the regected jobs.
 * 
 * 
 * calculate the minimal sum cost of total early work (for accepted jobs) and total rejection cost (for rejected jobs)
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

    int ***f = zeroes(dp_rows, dp_cols, dp_depth * 2);

    for (int j = 0; j < n; j++)
    {
        const auto &p = data.jobs[j].processing_time;
        const auto &d = data.jobs[j].due_to;
        const auto &e = data.jobs[j].recection_cost;

        for(int r = 0; r <= P-p; r++)
        {
            /**
             * for each job, f[r][j][l] is the minimum cost of processing the jobs j, j+1, ..., n-1
             * under the assumption that the sum of all late jobs' processing times in the range [1, j] is l
             * and the total processing time of the rejected jobs in the range [1, j] is r
            */
            for (int l = 0; l <= P-p-r; l++) // the `-p` is because the current job isn't yet added to the set of late jobs
            {
                const auto &s = (P - l - r - p); // start time of job j+1 if it added to the late jobs
                f[j + 1][l][r] = min(
                    p + f[j][l][r], // fully early
                    min(
                        min(max(0, d - s), p) + f[j][l + p][r], // partially late
                        e + f[j][l][r + p] // reject
                    )
                );
            }
        }
    }

    if (verbose)
    {
        print_array(f, dp_rows, dp_cols, dp_depth);
        print_array(f[0], dp_cols, dp_depth);
    }

    const auto result = f[n][0][0];
    cout << "!!! " << result << endl;
    delete_array(f, dp_rows, dp_depth);
    return result;
}

