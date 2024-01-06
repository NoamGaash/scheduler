#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "utils/readCSV.cpp"

int main() {
    std::string filename = "input.csv";
    std::vector<std::vector<int>> data = readCSV(filename);

    // Displaying the data for verification
    for (const auto& row : data) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
