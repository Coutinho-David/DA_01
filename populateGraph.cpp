#include "readLocations.h"
#include "readDistances.h"
#include "data_structures/Graph.h"

int main() {

    std::vector<distance> distances = readDistances("Distances.csv");
    std::vector<location> locations = readLocations("Locations.csv");

    Graph<std::string> graph;
    
    for (location element : locations) {
        if (graph.addVertex(element.CODE)) std::cout << "Added Vertex : " << element.CODE << "\n";
    }

    for (distance element : distances) {
       if (graph.addEdge(element.CODE1, element.CODE2, element.Driving)) {
            std::cout << "Added path : " << element.CODE1 << " ---> " << element.CODE2 << "\n";
       }
    }

    return 0;
}

