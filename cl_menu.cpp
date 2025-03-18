//
// Created by andre on 3/13/25.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>

using namespace std;

void cl_points(string &source, string &destination); //Source and destination selection
void cl_mode(string &mode, string source, string destination); //Mode of transportation selection
void cl_max_walk(int &maxWalkTime);
void cl_avoid_nodes(string &avoidNodesType, string start_point, string destination);
void cl_avoid_routes(string &avoidSegmentsType, string start_point, string destination);
void fileHandler(string &mode, string &source, string &destination, int &maxWalkTime, vector<int> &avoidNodesFile, vector<pair<int, int>> &avoidSegmentsFile);

int main() {
    //all possbile inputs
    string mode = "";
    string source = "";
    string destination = "";
    int maxWalkTime = 0;
    string avoidNodesType = "";
    string avoidSegmentsType = "";
    vector<int> avoidNodesFile = {};
    vector<pair<int, int>> avoidSegmentsFile = {};

    string input = "";
    cout << "Welcome to the individual route planning tool!\n" << endl;
    cout << "Would you like to submit a file or type your preferences?\n1 - \"File\"\n2 - \"Type\"" << endl << "Option: ";
    cin >> input;
    transform(input.begin(), input.end(), input.begin(),[](unsigned char c){
      return tolower(c);
    });
    if (!(input == "1" || input == "2")) {
        cout << "Wrong input!" << endl;
        main();
    }
    if (input == "file") fileHandler(mode, source, destination, maxWalkTime, avoidNodesFile, avoidSegmentsFile);
    else {
        cl_points(source, destination);
        cl_mode(mode, source, destination);
        if (mode == "driving-walking") cl_max_walk(maxWalkTime);
        cl_avoid_nodes(avoidNodesType, source, destination);
        cl_avoid_routes(avoidSegmentsType, source, destination);
        }
    return 0;
}

void cl_points(string &source, string &destination) {
    cout << "Where are you starting your trip?" << endl << "Location: ";
    cin >> source;
    cout << "Where would you like to go?" << endl << "Location: ";
    cin >>  destination;
    if (source == destination) {
        cout << "Start and end point must not be the same!\n" << endl;
        cl_points(source, destination);
    }
    transform(source.begin(), source.end(), source.begin(),[](unsigned char c){
      return toupper(c);
    });
    transform(destination.begin(), destination.end(), destination.begin(),[](unsigned char c){
      return toupper(c);
    });
}

void cl_mode(string &mode, string source, string destination) {
    cout << "How would you like to go from " << source << " to " << destination << "?" << endl;
    cout << "We recommend choosing one of the sustained modes!" << endl;
    cout << "Please pick one of the options bellow: \n 1 - Driving; \n 2 - Walking; \n 3 - Both." << endl << "Option: ";
    cin >> mode;
    if (!(mode == "1" || mode == "2" || mode == "3")) {
        cout << "Invalid mode!" << endl;
        cl_mode(mode, source, destination);
    }
    switch (stoi(mode)) {
        case '1': mode = "driving"; break;
        case '2': mode = "walking"; break;
        case '3': mode = "driving-walking"; break;
    }
}

void cl_max_walk(int &maxWalkTime) {
    string input = "";
    cout << "What is the maximum acceptable walking time?" << endl;
    cin >> input;
    maxWalkTime = stoi(input);
}

void cl_avoid_nodes(string &avoidNodesType,string source, string destination) {
    bool control = 1;
    cin.ignore();
    while (control) {
        cout << "Is there any places you would like to avoid?" << endl << "Separate them with spaces." << endl << "(Press enter to finish): ";
        getline(cin,avoidNodesType);
        transform(avoidNodesType.begin(), avoidNodesType.end(), avoidNodesType.begin(),[](unsigned char c){
            return toupper(c);});
        if (avoidNodesType.find(source) != string::npos || avoidNodesType.find(destination) != string::npos) {
            cout << "Can not avoid source nor destination." << endl;
            avoidNodesType = "";
        }
        else {
            control = 0;
        }
    }
    cout << avoidNodesType << endl;
}

void cl_avoid_routes(string &avoidSegmentsType, string source, string destination) {
    cout << "Is there any routes you would like to avoid?" << endl << "Submit the pairs of locations separated by spaces and the routes by commas." << endl << "(Press enter to finish) : ";
    getline(cin,avoidSegmentsType);
    if (avoidSegmentsType.empty()) return;
    avoidSegmentsType += ",";
    transform(avoidSegmentsType.begin(), avoidSegmentsType.end(), avoidSegmentsType.begin(),[](unsigned char c){
        return toupper(c);});
    if (avoidSegmentsType.find(source) != string::npos || avoidSegmentsType.find(destination) != string::npos) {
        cout << "Can not avoid source nor destination" << endl;
        cl_avoid_routes(avoidSegmentsType, source, destination);
    }
    cout << avoidSegmentsType << endl;
}


void fileHandler(string &mode, string &source, string &destination, int &maxWalkTime, vector<int> &avoidNodesFile, vector<pair<int,int>> &avoidSegmentsFile) {
    string file_name;
    string parse;
    cout << "Please submit the name of the file" << endl;
    cin >> file_name;
    ifstream file(file_name);
    if (!file) {
        cerr << "File does not exist" << endl;
    }
    while (getline(file, parse)) {
        string split = "";
        string var = parse.substr(0, parse.find(":"));
        string value = parse.substr(parse.find(":")+1);
        cout << var << " " << value << endl;
        if (var == "Mode") mode = value;
        if (var == "Source") source = value;
        if (var == "Destination") destination = value;
        if (var == "MaxWalkTime") maxWalkTime = stoi(value);
        if (var == "AvoidNodes") {
            value += ',';
            stringstream ss(value);
            while (getline(ss, split, ',')) {
                cout << split << endl;
                avoidNodesFile.push_back(stoi(split));
            }
        }
        if (var == "AvoidSegments") {
            stringstream ss(value);
            while (getline(ss, split, ')')) {
                avoidSegmentsFile.push_back({stoi(split.substr(1, split.find(","))),stoi(split.substr(split.find(",")+1))});
            }
        }
    }
}
