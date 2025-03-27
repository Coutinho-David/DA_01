#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>

using namespace std;

void cl_points(int &source, int &destination); //Source and destination selection
void cl_mode(int &mode); //Mode of transportation selection
void cl_max_walk(int &maxWalkTime);
void cl_avoid_nodes(vector<int> &avoidNodes, int start_point, int destination);
void cl_avoid_routes(vector<pair<int,int>> &avoidSegments, int source, int destination);
void cl_include_node(int &includeNode, int source, int destination);
void file_handler(int &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes, vector<pair<int, int>> &avoidSegments, int &includeNode);

void init(int &input, int &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes, vector<pair<int, int>> &avoidSegments, int &includeNode) {
    cout << "Welcome to the individual route planning tool!\n" << endl;
    cout << "Would you like to submit a file or type your preferences?\n1 - \"File\"\n2 - \"Type\"" << endl << "Option: ";
    cin >> input;

    if (!(input == 1 || input == 2)) {
        cout << "Wrong input!" << endl;
        init(input, mode, source, destination, maxWalkTime, avoidNodes, avoidSegments, includeNode);
    }

    if (input == 1) file_handler(mode, source, destination, maxWalkTime, avoidNodes, avoidSegments, includeNode);

    else {
        cl_points(source, destination);
        cl_mode(mode);
        if (mode == 3) cl_max_walk(maxWalkTime);
        cl_avoid_nodes(avoidNodes, source, destination);
        cl_avoid_routes(avoidSegments, source, destination);
        cl_include_node(includeNode, source, destination);
        return;
    }
}


void cl_points(int &source, int &destination) {
    cout << "Where are you starting your trip?" << endl << "Location: ";
    cin >> source;
    cout << "Where would you like to go?" << endl << "Location: ";
    cin >>  destination;

    if (source == destination) {
        cout << "Start and end point must not be the same!\n" << endl;
        cl_points(source, destination);
    }
}

void cl_mode(int &mode) {
    cout << "How would you like to get there?" << endl;
    cout << "We recommend choosing one of the sustained modes!" << endl;
    cout << "Please pick one of the options bellow: \n 1 - Driving; \n 2 - Walking; \n 3 - Both." << endl << "Option: ";
    cin >> mode;
    if (!(mode == 1 || mode == 2 || mode == 3)) {
        cout << "Invalid mode!" << endl;
        cl_mode(mode);
    }
}

void cl_max_walk(int &maxWalkTime) {
    cout << "What is the maximum acceptable walking time in minutes?" << endl;
    cin >> maxWalkTime;
}

void cl_avoid_nodes(vector<int> &avoidNodes,int source, int destination) {
    string input;
    int flag = 1;
    cout << "Is there any places you would like to avoid?" << endl << "Input them one by one." << endl << "(Press enter to finish): " << endl;
    cin.ignore();
    while (flag) {
        input = "";
        cout << "Place: ";
        getline(cin, input);
        if (input == "") {
            flag = 0;
        }
        else if (stoi(input) == source || stoi(input) == destination) {
            cout << "Can not avoid source nor destination." << endl;
        }
        else avoidNodes.push_back(stoi(input));
    }
}

void cl_avoid_routes(vector<pair<int,int>> &avoidSegments, int source, int destination) {
    string input;
    string _first;
    string _second;
    pair<int,int> avoidSegment;
    int control = 1;
    int flag = 1;
    cout << "Is there any routes you would like to avoid?" << endl << "Submit the pair of locations comma separated, one by one." << endl << "(Press enter on a new pair to finish)." << endl;
    while (1) {
        cout << " > ";
        getline(cin, input);
        if (input == "") break;
        stringstream ss(input);
        getline(ss,_first,',');
        getline(ss, _second);
        avoidSegment.first = stoi(_first);
        avoidSegment.second = stoi(_second);
        avoidSegments.push_back(avoidSegment);
    }
}

void cl_include_node(int &includeNode, int source, int destination) {
        string input = "";
        cout << "Is there any stop you need to make?" << endl << "(Press enter to skip.)" << endl << "Place: ";
        getline(cin, input);
        if (input != "") {
            includeNode = stoi(input);
        }
    }

void file_handler(int &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes, vector<pair<int,int>> &avoidSegments, int &includeNode) {
    string file_name;
    string parse;
    cout << "Please submit the name of the file" << endl;
    cin >> file_name;
    ifstream file(file_name);
    if (!file) {
        cerr << "File does not exist" << endl;
        file_handler(mode, source, destination, maxWalkTime, avoidNodes, avoidSegments, includeNode);
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
        if (var == "Source") source = stoi(value);
        if (var == "Destination") destination = stoi(value);
        if (var == "MaxWalkTime") maxWalkTime = stoi(value);
        if (var == "AvoidNodes") {
            value += ',';
            stringstream ss(value);
            while (getline(ss, split, ',')) {
                avoidNodes.push_back(stoi(split));
            }
        }
        if (var == "AvoidSegments") {
            stringstream ss(value);
            while (getline(ss, split, ')')) {
                avoidSegments.push_back({stoi(split.substr(1, split.find(","))),stoi(split.substr(split.find(",")+1))});
            }
        }
        if (var == "IncludeNode") {
                includeNode = stoi(value);
        }
    }
}
