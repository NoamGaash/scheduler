#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "RejectableJob.h"

class RejectableJobCollection
{
public:
    std::vector<RejectableJob> jobs;

    RejectableJobCollection(std::vector<std::vector<int>> data);
    RejectableJobCollection(int njobs, int p_max, float alpha, float beta);

    int P() const;
    int R() const;

    void sort_by_descending_due_to();
    void sort_by_ascending_due_to();

    int cost() const;
    int cost(const std::vector<bool> &isRejected) const;

    friend std::ostream &operator<<(std::ostream &os, const RejectableJobCollection &d);
};
