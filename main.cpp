#include "populateGraph.h"
#include "cl_menu.h"

using namespace std;

int main() {
    int input;
    int mode;
    string  source = "";
    string destination = "";
    string  avoidNodesType = "";
    string avoidSegmentsType = "";
    int maxWalkTime = 0;
    vector<int> avoidNodesFile = {};
    vector<pair<int, int>> avoidSegmentsFile = {};

    init(input, mode, source, destination, avoidNodesType, avoidSegmentsType, maxWalkTime, avoidNodesFile, avoidSegmentsFile);
    Graph<std::string> graph = populate();

    auto v = graph.getVertexSet();
   // for (auto elem : v) {
   //     std::cout << elem->getInfo() << "\n";
   //}

}
