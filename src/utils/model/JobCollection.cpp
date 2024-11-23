#include "JobCollection.h"

JobCollection::JobCollection(std::vector<std::vector<int>> data)
{
    for (const auto &row : data)
    {
        jobs.emplace_back(row[0], row[1], row[2]);
    }
}

JobCollection::JobCollection(int njobs, int p_max, float alpha)
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
        jobs.emplace_back(i + 1, p[i], d);
    }
}

JobCollection::JobCollection(RejectableJobCollection rd)
{
    for (const auto &job : rd.jobs)
    {
        jobs.emplace_back(job.id, job.processing_time, job.due_to);
    }
}

int JobCollection::P() const
{
    int P = 0;
    for (const auto &job : jobs)
    {
        P += job.processing_time;
    }
    return P;
}

void JobCollection::display() const
{
    std::cout << *this;
}

void JobCollection::sort_by_descending_due_to()
{
    std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
              { return a.due_to > b.due_to; });
}

void JobCollection::sort_by_ascending_due_to()
{
    std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
              { return a.due_to < b.due_to; });
}

int JobCollection::cost(const std::vector<Job> &solution) const
{
    int cost = 0, time = 0;

    for (const auto &job : solution)
    {
        cost += job.cost(time);
        time += job.processing_time;
    }

    return cost;
}

std::ostream &operator<<(std::ostream &os, const JobCollection &d)
{
    os << "Jobs: ";
    for (const auto &job : d.jobs)
    {
        job.display();
        os << " ";
    }
    return os;
}
