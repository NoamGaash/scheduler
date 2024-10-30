#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Job
{
public:
    int id;
    int processing_time;
    int due_to;

    Job(int id, int processing_time, int due_to)
        : id(id), processing_time(processing_time), due_to(due_to) {}
    virtual ~Job() = default;

    virtual int cost(int start) const
    {
        return min(processing_time, max(0, due_to - start));
    }

    virtual void display() const
    {
        cout << "(id=" << id << " p=" << processing_time << ", d=" << due_to << ")";
    }
};

class RejectableJob : public Job
{
public:
    int rejection_cost;

    RejectableJob(int id, int processing_time, int due_to, int rejection_cost)
        : Job(id, processing_time, due_to), rejection_cost(rejection_cost) {}

    int cost(int start) const override
    {
        return Job::cost(start) + rejection_cost;
    }

    void display() const override
    {
        std::cout << "(id=" << id << " p=" << processing_time << ", d=" << due_to
                  << ", r=" << rejection_cost << ")";
    }
};

class Data
{
public:
    std::vector<Job> jobs;

    Data(std::vector<std::vector<int>> data)
    {
        for (const auto &row : data)
        {
            jobs.push_back(Job(row[0], row[1], row[2]));
        }
    }

    Data(int njobs, int p_max, float alpha)
    {
        int *p = new int[njobs];
        int P = 0;
        for (int i = 0; i < njobs; i++)
        {
            p[i] = rand() % p_max + 1;
            P += p[i];
        }
        for (int i = 0; i < njobs; i++)
        {
            int d = rand() % (int)(alpha * P) + 1;
            jobs.push_back(Job(i + 1, p[i], d));
        }
        delete[] p;
    }

    int P() const
    {
        int P = 0;
        for (const auto &job : jobs)
        {
            P += job.processing_time;
        }
        return P;
    }

    void display() const
    {
        std::cout << this;
    }

    void sort_by_descending_due_to()
    {
        std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
                  { return a.due_to > b.due_to; });
    }

    void sort_by_ascending_due_to()
    {
        std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
                  { return a.due_to < b.due_to; });
    }

    int cost(const std::vector<Job> &solution) const
    {
        int cost = 0, time = 0;
        for (const auto &job : solution)
        {
            cost += job.cost(time);
            time += job.processing_time;
        }
        return cost;
    }
    // cout
    friend ostream &operator<<(ostream &os, const Data &d)
    {
        os << "Jobs: ";
        for (const auto &job : d.jobs)
        {
            job.display();
            os << " ";
        }
        return os;
    }
};

class RejectableData : public Data
{
public:
    std::vector<RejectableJob> jobs;

    RejectableData(std::vector<std::vector<int>> data): Data(data)
    {
        for (const auto &row : data)
        {
            jobs.push_back(RejectableJob(row[0], row[1], row[2], row[3]));
        }
    }

    RejectableData(int njobs, int p_max, float alpha, float beta) : Data(njobs, p_max, alpha)
    {
        for (int i = 0; i < njobs; i++)
        {
            jobs[i].rejection_cost = rand() % ((int)(beta * jobs[i].processing_time) + 1);
        }
    }

    int R() const
    {
        int R = 0;
        for (const auto &job : jobs)
        {
            R += job.rejection_cost;
        }
        return R;
    }
    void sort_by_descending_due_to()
    {
        std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
                  { return a.due_to > b.due_to; });
    }

    void sort_by_ascending_due_to()
    {
        std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
                  { return a.due_to < b.due_to; });
    }

    int cost() const
    {
        int cost = 0, time = 0;
        for (const auto &job : jobs)
        {
            cost += job.cost(time);
            time += job.processing_time;
        }
        return cost;
    }

    int cost(const std::vector<bool> &isRejected) const
    {
        int cost = 0, time = 0;
        for (int i = 0; i < jobs.size(); i++)
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

    // cout
    friend ostream &operator<<(ostream &os, const RejectableData &d)
    {
        os << "Jobs: ";
        for (const auto &job : d.jobs)
        {
            job.display();
            os << " ";
        }
        return os;
    }
};
