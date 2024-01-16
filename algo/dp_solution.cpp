
int dp_solution(Data &data, bool verbose = false)
{
    data.sort_by_descending_due_to();
    int n = data.jobs.size();
    int P = 0;
    for (const auto &job : data.jobs)
    {
        P += job.processing_time;
    }

    // initialize dp table
    int **f = new int *[n + 1];
    for (int i = 0; i <= n; i++)
    {
        f[i] = new int[P + 1];
        for (int j = 0; j <= P; j++)
        {
            f[i][j] = 0;
        }
    }

    for (int j = n - 2; j >= -1; j--)
    {
        for (int l = P; l >= 0; l--)
        {
            const auto &p = data.jobs[j + 1].processing_time;
            const auto &d = data.jobs[j + 1].due_to;

            if (d >= P - l)
            {
                f[j + 1][l] = p + f[j + 2][l];
            }
            else
            {
                const auto &s = (P - l - p); // start time of job j+1 if it added to the late jobs
                f[j + 1][l] = min(
                    p + f[j + 2][l],
                    min(
                        max(0, d - s),
                        p) +
                        f[j + 2][l + p]);
            }
        }
    }

    // print dp table
    if (verbose)
    {
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j <= P; j++)
            {
                cout << f[i][j] << "\t";
            }
            cout << endl;
        }
    }

    const auto result = f[0][0];
    for (int i = 0; i < n + 1; i++)
    {
        delete[] f[i];
    }
    delete[] f;

    return result;
}
