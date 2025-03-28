#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iostream>

using namespace std;

void outputGen(int source, int destination, string res) {
    cout << "Source:" << source << endl;
    cout << "Destination:" << destination << endl;
    cout << res << endl;
    ofstream outputFile("output.txt", std::ios::trunc);
    outputFile << "Source:" << source << endl;
    outputFile << "Destination:" << destination << endl;
    outputFile << res << endl;
    outputFile.close();
}
