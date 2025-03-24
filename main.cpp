#include "populateGraph.h"
#include "cl_menu.h"

using namespace std;


int run();

int main() {
    if (run()) cout << "Successful run" << endl;
    return 0;
}

int run() {
    int mode;
    int source;
    int destination;
    int maxWalkTime = 0;
    vector<int> avoidNodes = {};
    vector<pair<int, int>> avoidSegments = {};
    int includeNode = -1;
    cout << "Calling init" << endl;
    init(mode, source, destination, maxWalkTime, avoidNodes, avoidSegments, includeNode);
    cout << "creating graph" << endl;
    Graph<string> graph = populate();
    return 1;
}
