#include "readLocations.h"
#include "readDistances.h"
#include "data_structures/Graph.h"

Graph<std::string>  populate() {
    
    std::vector<distance> distances = readDistances("Distances.csv");
    std::vector<location> locations = readLocations("Locations.csv");

    Graph<std::string> graph;
    
    for (location element : locations) {
        if (graph.addVertex(element.CODE)) {}
    }

    for (distance element : distances) {
       if (graph.addEdge(element.CODE1, element.CODE2, element.Driving, element.Walking)) {}
    }

    return graph;
}

