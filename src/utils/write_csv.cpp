#include <fstream>
#include "data.h"
#include <sys/stat.h>
#include <vector>

using namespace std;

void createDirIfNeeded(string filePath) {
    size_t pos = 0;
    string token;
    string delimiter = "/";
    string dir = "";
    while ((pos = filePath.find(delimiter)) != string::npos) {
        token = filePath.substr(0, pos);
        dir += token + "/";
        mkdir(dir.c_str(), 0777);
        filePath.erase(0, pos + delimiter.length());
    }

}

void write_csv(const RejectableJobCollection &data, const string &filename)
{
    createDirIfNeeded(filename);
    ofstream file(filename);
    file << "Job,Pj,dj" << endl;
    for (const auto &job : data.jobs)
    {
        file << job.id << "," << job.processing_time << "," << job.due_to << endl;
    }
    file.close();
}