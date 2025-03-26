#ifndef READ_LOCATIONS_H
#define READ_LOCATIONS_H



#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>

struct location {
    std::string location;
    int Id;
    std::string CODE;
    bool parking;
};

std::vector<location> readLocations(const std::string &filename) {
        
    std::vector<location> data; 
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error Opening :" << filename << "\n";
        return data;
    }

    std::string line;
    std::getline(file, line);

    while(std::getline(file, line)) {
        std::stringstream stream(line);
        location row;
        
        std::getline(stream, row.location, ',');
        stream >> row.Id;
        stream.ignore();
        std::getline(stream, row.CODE, ',');
        stream >> row.parking;
     
        data.push_back(row);
    }

    file.close();
    return data;   
}



#endif // READ_LOCATIONS_H
