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
    cout << *this;
}

ostream &operator<<(ostream &os, const RejectableJob &job)
{
    os << "(id=" << job.id << " p=" << job.processing_time << ", d=" << job.due_to
       << ", r=" << job.rejection_cost << ")";
    return os;
}
