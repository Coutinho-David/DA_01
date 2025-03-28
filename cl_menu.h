#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>

using namespace std;

/**
 * @brief Selects source and destination points.
 * @param source Reference to the starting location.
 * @param destination Reference to the destination location.
 */
void cl_points(int &source, int &destination);

/**
 * @brief Selects the transportation mode.
 * @param mode Reference to the transportation method.
 */
void cl_mode(int &mode);

/**
 * @brief Selects the maximum acceptable walking time.
 * @param maxWalkTime Reference to the maximum acceptable walking time.
 */
void cl_max_walk(int &maxWalkTime);

/**
 * @brief Selects nodes that are to be avoided.
 * @param avoidNodes Reference to the vector where the nodes to be avoided must be.
 * @param source Copy of the source for verification purposes.
 * @param destination Copy of the destination for verification purposes.
 * @details This function allows the user to define a list of nodes that must be excluded
 * from the calculated route. It ensures that the path-finding algorithm avoids
 * these nodes when generating the best possible route.
 * It also ensures that the input is correct and that neither the source nor the destination is to be avoided, as that would be infeasible
 */
void cl_avoid_nodes(vector<int> &avoidNodes, int source, int destination);

/**
 * @brief Selects routes that are to be avoided.
 * @param avoidSegments Reference to the vector where the nodes to be avoided must be.
 * @param source Copy of the source for verification purposes.
 * @param destination Copy of the destination for verification purposes.
 * @details This function allows the user to define a list of segments that must be excluded
 * from the calculated route. It ensures that the path-finding algorithm avoids
 * these segments when generating the best possible route.
 * It also ensures that the input is correct and that neither the source nor the destination is to be avoided, as that would be infeasible
 */
void cl_avoid_routes(vector<pair<int,int>> &avoidSegments, int source, int destination);

/**
 * @brief Selects a node that must be included.
 * @param includeNode Reference to the node that must be included.
 * @param source Copy of the source for verification purposes.
 * @param destination Copy of the destination for verification purposes.
 * @details This function allows the user to define a node that must be included in the
the calculated route. It ensures that the path-finding algorithm goes through this node when generating the best possible route.
 * It also ensures that the input is correct and that neither the source nor the destination is a stop, as that would be irrelevant
 */
void cl_include_node(int &includeNode, int source, int destination);

/**
 * @brief Input the data via a text file.
 * @details This function allows the user to input the name of the file containing the information and stores it in the correct reference.
 * The formating of the file must be correct in order for it to be read properly.
 */
void file_handler(int &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes, vector<pair<int, int>> &avoidSegments, int &includeNode);

/**
 * @brief Starter function for the interface.
 * @details THis function receives all the parameters requiered for performing the path search and ensures that they are handled by the correct funtion depending on desired input method.
*/

void init(int &input, int &mode, int &source, int &destination, int &maxWalkTime, vector<int> &avoidNodes, vector<pair<int, int>> &avoidSegments, int &includeNode) {
    cout << "Welcome to the individual route planning tool!\n" << endl;
    cout << "Would you like to submit a file or type your preferences?\n\n 1 - \"File\"\n 2 - \"Type\"" << endl << endl << "Option: ";
    cin >> input;

    if (!(input == 1 || input == 2)) {
        cout << "Wrong input!" << endl;
        init(input, mode, source, destination, maxWalkTime, avoidNodes, avoidSegments, includeNode);
    }

    if (input == 1) file_handler(mode, source, destination, maxWalkTime, avoidNodes, avoidSegments, includeNode);

    else {
        cl_mode(mode);
        cl_points(source, destination);
        if (mode == 2) cl_max_walk(maxWalkTime);
        cl_avoid_nodes(avoidNodes, source, destination);
        cl_avoid_routes(avoidSegments, source, destination);
        cl_include_node(includeNode, source, destination);
        return;
    }
}


void cl_points(int &source, int &destination) {
    cout << endl << "-----------------------------------------------------------------------------" << endl;
    cout << endl << "Where are you starting your trip?" << endl << endl << "Location: ";
    cin >> source;
    cout << endl << "Where would you like to go?" << endl << endl << "Location: ";
    cin >>  destination;

    if (source == destination) {
        cout << "Start and end point must not be the same!\n" << endl;
        cl_points(source, destination);
    }
}

void cl_mode(int &mode) {
    cout << endl << "-----------------------------------------------------------------------------" << endl;
    cout << endl << "How would you like to get there?" << endl;
    cout << "We recommend choosing the most Environmentally-Friendly mode!" << endl;
    cout << "Please pick one of the options bellow: \n\n 1 - Driving; \n 2 - Driving and Walking." << endl << endl << "Option: ";
    cin >> mode;
    if (!(mode == 1 || mode == 2)) {
        cout << "Invalid mode!" << endl;
        cl_mode(mode);
    }
}

void cl_max_walk(int &maxWalkTime) {
    cout << endl << "-----------------------------------------------------------------------------" << endl;
    cout << "\nWhat is the maximum acceptable walking time in minutes?" << endl;
    cout << "\nTime: ";
    cin >> maxWalkTime;
}

void cl_avoid_nodes(vector<int> &avoidNodes,int source, int destination) {
    string input;
    int flag = 1;
    cout << endl << "-----------------------------------------------------------------------------" << endl;
    cout << "\nIs there any places you would like to avoid?" << endl << "Input them one by one and press enter to finish: " << endl << endl;
    cin.ignore();
    while (flag) {
        input = "";
        cout << "Place: ";
        getline(cin, input);
        if (input == "") {
            flag = 0;
        }
        else if (stoi(input) == source || stoi(input) == destination) {
            cout << " -> Can not avoid source nor destination." << endl;
        }
        else avoidNodes.push_back(stoi(input));
    }
}

void cl_avoid_routes(vector<pair<int,int>> &avoidSegments, int source, int destination) {
    string input;
    string _first;
    string _second;
    pair<int,int> avoidSegment = {};
    int control = 1;
    int flag = 1;
    cout << endl << "-----------------------------------------------------------------------------" << endl;
    cout << "\nIs there any routes you would like to avoid?" << endl << "Submit the pair of locations, comma separated, one by one." << endl << "Press enter on a new pair to finish." << endl << endl;
    while (1) {
        cout << "Pair: ";
        getline(cin, input);
        if (input == "")    {
            break;
        }else{
            stringstream ss(input);
            getline(ss,_first,',');
            getline(ss, _second);
            avoidSegment.first = stoi(_first);
            avoidSegment.second = stoi(_second);
            avoidSegments.push_back(avoidSegment);
        }
    }
}

void cl_include_node(int &includeNode, int source, int destination) {
        string input = "";
        cout << endl << "-----------------------------------------------------------------------------" << endl;
        cout << "\nIs there any stop you need to make?" << endl << "Press enter to skip." << endl << endl << "Place: ";
        getline(cin, input);
        if (input != "") {
            includeNode = stoi(input);
        }
        cout << endl << "-----------------------------------------------------------------------------" << endl << endl;
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
        if (value == "") {continue;}
        if (var == "Mode") {
            if (value == "driving") {mode = 1;}
            else {mode = 2;}
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
