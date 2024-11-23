#ifndef DATA_H
#define DATA_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Job.h"
#include "RejectableData.h"

class Data
{
public:
    std::vector<Job> jobs;

    Data(std::vector<std::vector<int>> data);
    Data(int njobs, int p_max, float alpha);
    Data(RejectableData rd);

    int P() const;
    void display() const;

    void sort_by_descending_due_to();
    void sort_by_ascending_due_to();

    int cost(const std::vector<Job> &solution) const;

    friend std::ostream &operator<<(std::ostream &os, const Data &d);
};

#endif // DATA_H
