#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> result;
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return result;
    }

    std::string line, cell;
    // Ignore the header row
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream lineStream(line);
        
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(std::stoi(cell));
        }
        
        result.push_back(row);
    }

    file.close();
    return result;
}
