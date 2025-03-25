#include "populateGraph.h"
#include "cl_menu.h"
#include "dijkstra.h"

using namespace std;


int run();

int main() {
    if (run()) cout << "Successful run" << endl;
    return 0;
}

int run() {
    Graph<int> graph = populate();
    std::cout << bestDrivingRoute(&graph, 2 , 420) << std::endl;
    int input;
    int mode;
    int source;
    int destination;
    int maxWalkTime = 0;
    vector<int> avoidNodes = {};
    vector<pair<int, int>> avoidSegments = {};
    cout << "Calling init" << endl;
    init(input, mode, source, destination, maxWalkTime, avoidNodes, avoidSegments);
    cout << "creating graph" << endl;
    return 1;
}
