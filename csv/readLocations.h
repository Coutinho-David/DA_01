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

/**
* @brief Reads locations data from a CSV file.
*
* This function parses a CSV file containing locations information and
* stores it in a vector of `location` structures. Each row
* in the file represents a locations along with their name, id and parking information.
*
* @param filename The name of the CSV file to read.
*
* @return A vector of `location` structures containing parsed locations information.
*/
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
