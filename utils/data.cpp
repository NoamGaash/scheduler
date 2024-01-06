#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Job {
    public:
        int id;
        int processing_time;
        int due_to;

        Job(int id, int processing_time, int due_to) {
            this->id = id;
            this->processing_time = processing_time;
            this->due_to = due_to;
        }

        void display() const {
            std::cout << "(id=" << id << " p=" << processing_time << ", d=" << due_to << ")";
        }

        int cost(int start) const {
            return min(processing_time, max(0, due_to - start));
        }
};

class Data {
    public:
        std::vector<Job> jobs;

        Data(std::vector<std::vector<int>> data) {
            for (const auto& row : data) {
                jobs.push_back(Job(row[0], row[1], row[2]));
            }
        }

        void display() const {
            std::cout << "Jobs: ";
            for (const auto& job : jobs) {
                job.display();
                std::cout << " ";
            }
            std::cout << std::endl;
        }

        void sort_by_descending_due_to() {
            std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
                return a.due_to > b.due_to;
            });
        }
};
