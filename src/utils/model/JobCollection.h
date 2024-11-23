#ifndef DATA_H
#define DATA_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Job.h"
#include "RejectableJobCollection.h"

class JobCollection
{
public:
    std::vector<Job> jobs;

    JobCollection(std::vector<std::vector<int>> data);
    JobCollection(int njobs, int p_max, float alpha);
    JobCollection(RejectableJobCollection rd);

    int P() const;
    void display() const;

    void sort_by_descending_due_to();
    void sort_by_ascending_due_to();

    int cost(const std::vector<Job> &solution) const;

    friend std::ostream &operator<<(std::ostream &os, const JobCollection &d);
};

#endif // DATA_H
