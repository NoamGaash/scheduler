#ifndef REJECTABLE_JOB_H
#define REJECTABLE_JOB_H

#include "Job.h"
#include <iostream>

class RejectableJob : public Job
{
public:
    int rejection_cost;

    RejectableJob(int id, int processing_time, int due_to, int rejection_cost);

    int cost(int start) const override;

    void display() const override;

    friend ostream &operator<<(ostream &os, const RejectableJob &job);
};

#endif // REJECTABLE_JOB_H
