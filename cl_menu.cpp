//
// Created by andre on 3/13/25.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void cl_points(); //Source and destination selection
void cl_method(string start_point, string end_point); //Method of transportation selection

int main() {

    cout << "Welcome to the individual rout planning tool!\n" << endl;
    cl_points();
    return 0;
}

void cl_points() {
    string start_point = "";
    string end_point = "";
    cout << "Where are you starting your trip?" << endl;
    cin >> start_point;
    cout << "Where would you like to go?" << endl;
    cin >>  end_point;
    if (start_point == end_point) {
        cout << "Start and end point must not be the same!\n" << endl;
        cl_points();
    }
    cl_method(start_point, end_point);
}

void cl_method(string start_point, string end_point) {
    string method = "";
    cout << "How would you like to go from " << start_point << " to " << end_point << "?" << endl;
    cout << "We recommend choosing one of the sustained methods!" << endl;
    cout << "Please pick one of the options bellow: \n Car; \n Walking; \n Both." << endl;
    cin >> method;
    transform(method.begin(), method.end(), method.begin(),[](unsigned char c){
      return tolower(c);
    });
    if (!all_of(method.begin(), method.end(), ::isalpha) || (method != "car" && method != "walking" && method != "both")) {
        cout << "Invalid method!" << endl;
        cl_method(start_point, end_point);
    }
}
