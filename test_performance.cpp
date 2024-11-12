#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include "utils/data.cpp"
#include "utils/timing.cpp"
#include "utils/stddev.cpp"
#include "algo/dp_solution.cpp"

int main()
{
    const bool withRejection = false;
    const bool withoutRejection = true;

    if(withoutRejection) {
        cout << "w/o rejection:" << endl;
        cout << "n,p_max,alpha,max_time,avg_time,stddev" << endl;
        for (int p_max = 50; p_max <= 100; p_max += 50)
        {
            for (int n = 20; n <= 200; n += 20)
            {
                for (float alpha = 0.7; alpha <= 1; alpha += 0.3)
                {
                    vector<double> times;
                    for (int instance = 0; instance < 25; instance++)
                    {
                        Data d(n, p_max, alpha);
                        double time = time_measure([&d]()
                                                    { dp_solution(d); });
                        times.push_back(time);

                    }
                    cout << n << "," << p_max << "," << alpha << "," << *max_element(times.begin(), times.end()) << "," << accumulate(times.begin(), times.end(), 0.0) / times.size() << "," << stddev(times.begin(), times.end()) << endl;
                }
            }
        }
    }
    if(withRejection) {
        cout << "with rejection:" << endl;
        cout << "n,p_max,alpha,beta,max_time,avg_time,stddev" << endl;
        for (int p_max = 50; p_max <= 100; p_max += 50)
        {
            for (int n = 20; n <= 200; n += 20)
            {
                for (float alpha = 0.7; alpha <= 1; alpha += 0.3)
                {
                    for (float beta = 0.7; beta <= 1; beta += 0.3)
                    {
                        vector<double> times;
                        for (int instance = 0; instance < 25; instance++)
                        {
                            RejectableData d(n, p_max, alpha, beta);
                            double time = time_measure([&d]()
                                                        { dp_solution(d); });
                            times.push_back(time);

                        }
                        cout << n << "," << p_max << "," << alpha << "," << beta << "," << *max_element(times.begin(), times.end()) << "," << accumulate(times.begin(), times.end(), 0.0) / times.size() << "," << stddev(times.begin(), times.end()) << endl;
                    }
                }
            }
        }
    }
    return 0;
}
