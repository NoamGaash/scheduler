#include "RejectableJobCollection.h"

RejectableJobCollection::RejectableJobCollection(std::vector<std::vector<int>> data)
{
    for (const auto &row : data)
    {
        jobs.emplace_back(row[0], row[1], row[2], row[3]);
    }
}

RejectableJobCollection::RejectableJobCollection(int njobs, int p_max, float alpha, float beta)
{
    std::vector<int> p(njobs);
    int P = 0;

    for (int i = 0; i < njobs; ++i)
    {
        p[i] = rand() % p_max + 1;
        P += p[i];
    }

    for (int i = 0; i < njobs; ++i)
    {
        int d = rand() % static_cast<int>(alpha * P) + 1;
        int r = rand() % static_cast<int>(beta * P) + 1;
        jobs.emplace_back(i + 1, p[i], d, r);
    }
}

int RejectableJobCollection::P() const
{
    int P = 0;
    for (const auto &job : jobs)
    {
        P += job.processing_time;
    }
    return P;
}

int RejectableJobCollection::R() const
{
    int sum = 0;
    int p = this->P();
    for (const auto &job : jobs)
    {
        sum += job.rejection_cost;
    }
    return std::min(sum, p);
}

void RejectableJobCollection::sort_by_descending_due_to()
{
    std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
              { return a.due_to > b.due_to; });
}

void RejectableJobCollection::sort_by_ascending_due_to()
{
    std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
              { return a.due_to < b.due_to; });
}

int RejectableJobCollection::cost() const
{
    int cost = 0, time = 0;

    for (const auto &job : jobs)
    {
        cost += job.cost(time);
        time += job.processing_time;
    }

    return cost;
}

int RejectableJobCollection::cost(const std::vector<bool> &isRejected) const
{
    int cost = 0, time = 0;

    for (std::size_t i = 0; i < jobs.size(); ++i)
    {
        if (isRejected[i])
        {
            cost += jobs[i].rejection_cost;
        }
        else
        {
            cost += jobs[i].cost(time);
            time += jobs[i].processing_time;
        }
    }

    return cost;
}

std::ostream &operator<<(std::ostream &os, const RejectableJobCollection &d)
{
    os << "Jobs: ";
    for (const auto &job : d.jobs)
    {
        job.display();
        os << " ";
    }
    return os;
}
