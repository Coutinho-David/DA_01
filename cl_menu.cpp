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
void cl_avoid_nodes(string &avoidNodes, string start_point, string destination);
void cl_avoid_routes(string &avoidSegments, string start_point, string destination);
void fileHandler(string &mode, string &source, string &destination, int &maxWalkTime, string &avoidNodes, string &avoidSegments);

int main() {
    //all possbile inputs
    string mode = "";
    string source = "";
    string destination = "";
    int maxWalkTime = 0;
    string avoidNodes = "";
    string avoidSegments = "";

    string input = "";
    cout << "Welcome to the individual route planning tool!\n" << endl;
    cout << "Would you like to submit a file or type your preferences?\nPlease answear with either \"File\" or \"Type\"" << endl;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(),[](unsigned char c){
      return tolower(c);
    });
    if (!(input == "file" || input == "type")) {
        cout << "Wrong input!" << endl;
        main();
    }
    if (input == "file") fileHandler(mode, source, destination, maxWalkTime, avoidNodes, avoidSegments);
    else {
        cl_points(source, destination);
        cl_mode(mode, source, destination);
        if (mode == "both") cl_max_walk(maxWalkTime);
        cl_avoid_nodes(avoidNodes, source, destination);
        cl_avoid_routes(avoidSegments, source, destination);
        }
    return 0;
}

void cl_points(string &source, string &destination) {

    cout << "Where are you starting your trip?" << endl;
    cin >> source;
    cout << "Where would you like to go?" << endl;
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
    cout << "Please pick one of the options bellow: \n Car; \n Walking; \n Both." << endl;
    cin >> mode;
    transform(mode.begin(), mode.end(), mode.begin(),[](unsigned char c){
      return tolower(c);
    });
    if (!all_of(mode.begin(), mode.end(), ::isalpha) || (mode != "car" && mode != "walking" && mode != "both")) {
        cout << "Invalid mode!" << endl;
        cl_mode(mode, source, destination);
    }
}

void cl_max_walk(int &maxWalkTime) {
    string input = "";
    cout << "What is the maximum acceptable walking time?" << endl;
    cin >> input;
    maxWalkTime = stoi(input);
}

void cl_avoid_nodes(string &avoidNodes,string source, string destination) {
    bool control = 1;
    cin.ignore();
    while (control) {
        cout << "Is there any places you would like to avoid?" << endl << "Separate them with spaces." << endl << "(Press enter to finish): ";
        getline(cin,avoidNodes);
        transform(avoidNodes.begin(), avoidNodes.end(), avoidNodes.begin(),[](unsigned char c){
            return toupper(c);});
        if (avoidNodes.find(source) != string::npos || avoidNodes.find(destination) != string::npos) {
            cout << "Can not avoid source nor destination." << endl;
            avoidNodes = "";
        }
        else {
            control = 0;
        }
    }

    cout << avoidNodes << endl;
}

void cl_avoid_routes(string &avoidSegments, string source, string destination) {
    cout << "Is there any routes you would like to avoid?" << endl << "Submit the pairs of locations separated by spaces and the routes by commas." << endl << "(Press enter to finish) : ";
    getline(cin,avoidSegments);
    if (avoidSegments.empty()) return;
    avoidSegments += ",";
    transform(avoidSegments.begin(), avoidSegments.end(), avoidSegments.begin(),[](unsigned char c){
        return toupper(c);});
    if (avoidSegments.find(source) != string::npos || avoidSegments.find(destination) != string::npos) {
        cout << "Can not avoid source nor destination" << endl;
        cl_avoid_routes(avoidSegments, source, destination);
    }
    cout << avoidSegments << endl;
}


void fileHandler(string &mode, string &source, string &destination, int &maxWalkTime, string &avoidNodes, string &avoidSegments) {
    string file_name;
    cout << "Please submit the name of the file" << endl;
    cin >> file_name;
    ifstream file(file_name);
    if (!file) {
        cerr << "File does not exist" << endl;
    }
}
