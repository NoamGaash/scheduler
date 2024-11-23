#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include "utils/data.h"
#include "utils/timing.h"
#include "utils/stddev.h"
#include "algo/dp_solution.h"

int main()
{
    const bool withoutRejection = false;
    const bool withRejection = true;

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
                        JobCollection d(n, p_max, alpha);
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
                            RejectableJobCollection d(n, p_max, alpha, beta);
                            int result;
                            double time = time_measure([&d, &result]()
                                                        { result = dp_solution(d); });
                            times.push_back(time);
                            
                            // make sure the result is smaller than the result without rejection
                            JobCollection no_rejection(d);
                            if(!result) {
                                cout << "Error: result is 0" << endl;
                            }
                            if (result > dp_solution(no_rejection, false))
                            {
                                cout << "Error: " << result << " > " << dp_solution(no_rejection, false) << endl;
                            }
                        }
                        cout << n << "," << p_max << "," << alpha << "," << beta << "," << *max_element(times.begin(), times.end()) << "," << accumulate(times.begin(), times.end(), 0.0) / times.size() << "," << stddev(times.begin(), times.end()) << endl;
                    }
                }
            }
        }
    }
    return 0;
}
