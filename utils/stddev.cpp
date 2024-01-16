#include <numeric>
#include <cmath>
#include <vector>

using namespace std;

double stddev(vector<double>::iterator begin, vector<double>::iterator end)
{
    double sum = 0;
    double mean = accumulate(begin, end, 0.0) / (end - begin);
    for (auto it = begin; it != end; it++)
    {
        sum += (*it - mean) * (*it - mean);
    }
    return sqrt(sum / (end - begin));
}