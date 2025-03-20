#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>

using namespace std;

void cl_points(string &source, string &destination); //Source and destination selection
void cl_mode(int &mode, string source, string destination); //Mode of transportation selection
void cl_max_walk(int &maxWalkTime);
void cl_avoid_nodes(string &avoidNodesType, string start_point, string destination);
void cl_avoid_routes(string &avoidSegmentsType, string start_point, string destination);
void fileHandler(int &mode, string &source, string &destination, int &maxWalkTime, vector<int> &avoidNodesFile, vector<pair<int, int>> &avoidSegmentsFile);

void init(int &input,
    int &mode,
    string &source,
    string &destination,
    string &avoidNodesType,
    string &avoidSegmentsType,
    int &maxWalkTime,
    vector<int> &avoidNodesFile,
    vector<pair<int, int>> &avoidSegmentsFile) {
    cout << "Welcome to the individual route planning tool!\n" << endl;
    cout << "Would you like to submit a file or type your preferences?\n1 - \"File\"\n2 - \"Type\"" << endl << "Option: ";
    cin >> input;

    if (!(input == 1 || input == 2)) {
        cout << "Wrong input!" << endl;
        init(input, mode, source, destination, avoidNodesType, avoidSegmentsType, maxWalkTime, avoidNodesFile, avoidSegmentsFile);
    }

    if (input == 1) fileHandler(mode, source, destination, maxWalkTime, avoidNodesFile, avoidSegmentsFile);

    else {
        cl_points(source, destination);
        cl_mode(mode, source, destination);
        if (mode == 3) cl_max_walk(maxWalkTime);
        cl_avoid_nodes(avoidNodesType, source, destination);
        cl_avoid_routes(avoidSegmentsType, source, destination);
    }
}


void cl_points(string &source, string &destination) {
    cout << "Where are you starting your trip?" << endl << "Location: ";
    cin >> source;
    cout << "Where would you like to go?" << endl << "Location: ";
    cin >>  destination;

    transform(source.begin(), source.end(), source.begin(),[](unsigned char c){
      return toupper(c);
    });
    transform(destination.begin(), destination.end(), destination.begin(),[](unsigned char c){
      return toupper(c);
    });

    if (source == destination) {
        cout << "Start and end point must not be the same!\n" << endl;
        cl_points(source, destination);
    }
}

void cl_mode(int &mode, string source, string destination) {
    cout << "How would you like to go from " << source << " to " << destination << "?" << endl;
    cout << "We recommend choosing one of the sustained modes!" << endl;
    cout << "Please pick one of the options bellow: \n 1 - Driving; \n 2 - Walking; \n 3 - Both." << endl << "Option: ";
    cin >> mode;
    if (!(mode == 1 || mode == 2 || mode == 3)) {
        cout << "Invalid mode!" << endl;
        cl_mode(mode, source, destination);
    }
}

void cl_max_walk(int &maxWalkTime) {
    cout << "What is the maximum acceptable walking time in minutes?" << endl;
    cin >> maxWalkTime;
}

void cl_avoid_nodes(string &avoidNodesType,string source, string destination) {
    cin.ignore();
    cout << "Is there any places you would like to avoid?" << endl << "Separate them with spaces." << endl << "(Press enter to finish): ";
    getline(cin,avoidNodesType);
    transform(avoidNodesType.begin(), avoidNodesType.end(), avoidNodesType.begin(),[](unsigned char c){
        return toupper(c);});
    if (avoidNodesType.find(source) != string::npos || avoidNodesType.find(destination) != string::npos) {
        cout << "Can not avoid source nor destination." << endl;
        avoidNodesType = "";
    }
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
}


void fileHandler(int &mode, string &source, string &destination, int &maxWalkTime, vector<int> &avoidNodesFile, vector<pair<int,int>> &avoidSegmentsFile) {
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
        if (var == "Mode") {
            if (value == "driving") {mode = 1;}
            else if (value == "walking") {mode = 2;}
            else if (value == "driving-walking") {mode = 3;}
        }
        if (var == "Source") source = value;
        if (var == "Destination") destination = value;
        if (var == "MaxWalkTime") maxWalkTime = stoi(value);
        if (var == "AvoidNodes") {
            value += ',';
            stringstream ss(value);
            while (getline(ss, split, ',')) {
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
