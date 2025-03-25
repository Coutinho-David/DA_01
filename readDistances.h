#ifndef READ_DISTANCES_H
#define READ_DISTANCES_H

#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <climits>

struct DistanceData {
    std::string CODE1;
    std::string CODE2;
    int Driving;
    int Walking;
};


std::vector<DistanceData> readDistances(const std::string &filename) {
        
    std::vector<DistanceData> data; 
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error Opening :" << filename << "\n";
        return data;
    }

    std::string line;
    std::getline(file, line);

    while(std::getline(file, line)) {
        std::stringstream stream(line);
        DistanceData row;
        
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

#endif // READ_DISTANCES_H
    