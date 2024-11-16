#ifndef JOB_H
#define JOB_H

#include <iostream>
using namespace std;

class Job
{
public:
    int id;
    int processing_time;
    int due_to;

    Job(int id, int processing_time, int due_to);
    virtual ~Job() = default;

    virtual int cost(int start) const;
    virtual void display() const;
};

#endif // JOB_H
