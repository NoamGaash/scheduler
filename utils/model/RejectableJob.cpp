#include "RejectableJob.h"
#include <iostream>
#include <algorithm>
using namespace std;

RejectableJob::RejectableJob(int id, int processing_time, int due_to, int rejection_cost)
    : Job(id, processing_time, due_to), rejection_cost(rejection_cost) {}

int RejectableJob::cost(int start) const
{
    return std::min(rejection_cost, Job::cost(start));
}

void RejectableJob::display() const
{
    cout << "(id=" << id << " p=" << processing_time << ", d=" << due_to
         << ", r=" << rejection_cost << ")";
}
