#include <vector>
#include "data.cpp"

using namespace std;

vector<Job> operator+(const vector<Job>& a, const Job& b) {
    vector<Job> c = a;
    c.push_back(b);
    return c;
}
