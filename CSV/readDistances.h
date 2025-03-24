#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <climits>

struct distance {
    std::string CODE1;
    std::string CODE2;
    int Driving;
    int Walking;
};


std::vector<distance> readDistances(const std::string &filename) {
        
    std::vector<distance> data; 
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error Opening :" << filename << "\n";
        return data;
    }

    std::string line;
    std::getline(file, line);

    while(std::getline(file, line)) {
        std::stringstream stream(line);
        distance row;
        
        std::getline(stream, row.CODE1, ',');
        std::getline(stream, row.CODE2, ',');
        std::string driving;
        std::getline(stream, driving, ',');
        if (isdigit(driving[0])) row.Driving = std::stoi(driving);
        else row.Driving = INT_MAX;
        stream >> row.Walking;
    
        data.push_back(row);
    }

    file.close();
    return data;   
}
