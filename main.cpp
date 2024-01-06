#include "utils/readCSV.cpp"
#include "utils/data.cpp"

int main() {
    std::string filename = "input.csv";
    Data d(readCSV(filename));

    d.sort_by_descending_due_to();
    d.display();

    return 0;
}
