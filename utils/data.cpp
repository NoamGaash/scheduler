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
    {
        this->id = id;
        this->processing_time = processing_time;
        this->due_to = due_to;
    }

    void display() const
    {
        std::cout << "(id=" << id << " p=" << processing_time << ", d=" << due_to << ")";
    }

    int cost(int start) const
    {
        return min(processing_time, max(0, due_to - start));
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
        os << endl;
        return os;
    }
};
