#include "utils/data.cpp"
#include "utils/operators.cpp"
#include "utils/timing.cpp"
#include "utils/write_csv.cpp"
#include "algo/naive_solution.cpp"
#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main()
{
    int n = 20, pmax = 50;
    double alpha = 0.7;
    
    cout << "n = " << n << ", pmax = " << pmax << ", alpha = " << alpha << endl;
    for(int i = 0; i < 100; i++)
    {
        string path = to_string(n) + "-" + to_string(pmax) + "-" + to_string(alpha) + "-" + to_string(i) + "/";
        if (!exists("./data/" + path + "output.txt"))
        {
            Data d(n, pmax, alpha);
            write_csv(d, "./data/" + path + "input.csv");
            d.sort_by_descending_due_to();
            double time = time_measure([&d]()
                                    { d.jobs = naive_solution(d, d.jobs.size()); });
            const auto result = d.cost(d.jobs);
            ofstream file("./data/" + path + "output.txt");
            file << result;
            file.close();
        }
    }
}