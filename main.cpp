//#include "populateGraph.h"
#include "cl_menu.h"
#include "dijkstra.h"
#include "test.h"
#include "drivingAndWalking.h"

#include <vector>
using namespace std;


int run();

int main() {
    if (run()) cout << "\nSUCCESSFUL RUN" << endl;
    return 0;
}

int run() {
   // Graph<int> graph = populate();

        //test bestAndAlternativeDrivingRoute

    //cout << bestAndAlternativeDrivingRoute(&graph, 1, 45) << endl;

        //test restrictedDrivingRoute

    /*
    std::vector<int> avoidNodes = {3, 7};  
    std::vector<pair<int, int>> avoidSegments = {{1, 4}, {2, 5}};  
    int includeNode = 6;  
    cout << restrictedDrivingRoute(&graph, 1, 45, avoidNodes, avoidSegments, includeNode) << endl;
    */
        //test DrivingAndWalkingRoute

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

    //cout << bestAndAlternativeDrivingRoute(&graph, source, destination);
   // cout << restrictedDrivingRoute(&graph, source, destination, avoidNodes, avoidSegments, 4) << endl;
    
    cout << drivingAndWalkingRoute(graph, source, destination, maxWalkTime, avoidNodes, avoidSegments) << "\n";
    return 1;
}
