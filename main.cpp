//#include "populateGraph.h"
#include "cl_menu.h"
#include "dijkstra.h"
#include "test.h"
#include "drivingAndWalking.h"
#include "outputGen.h"

#include <vector>
using namespace std;

int main() {
  
    int input;
    int mode;
    int source;
    int destination;
    int maxWalkTime = 0;
    vector<int> avoidNodes = {};
    vector<pair<int, int>> avoidSegments = {};
    int includeNode;
    
    cout << "Calling init" << endl;
    init(input, mode, source, destination, maxWalkTime, avoidNodes, avoidSegments, includeNode);
    cout << "creating graph" << endl;
    
    Graph<int> graph = test(avoidNodes, avoidSegments);

    string res;
    
    mode == 1 ? res = bestAndAlternativeDrivingRoute(&graph, source, destination) : res = drivingAndWalkingRoute(graph, source, destination, maxWalkTime);
     
    outputGen(source, destination, res);

    return 0;
}
