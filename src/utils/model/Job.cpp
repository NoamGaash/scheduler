#include "Job.h"
#include <algorithm>
using namespace std;

Job::Job(int id, int processing_time, int due_to)
    : id(id), processing_time(processing_time), due_to(due_to) {}

int Job::cost(int start) const
{
    return min(processing_time, max(0, due_to - start));
}

void Job::display() const
{
    cout << *this;
}

ostream &operator<<(ostream &os, const Job &job)
{
    os << "(id=" << job.id << " p=" << job.processing_time << ", d=" << job.due_to << ")";
    return os;
}
