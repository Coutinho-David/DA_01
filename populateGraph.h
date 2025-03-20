#include "CSV/readLocations.h"
#include "CSV/readDistances.h"
#include "data_structures/Graph.h"

Graph<std::string>  populate(std::vector<int> avoidNodes, std::vector<std::pair<int, int>> avoidSegments) {

    std::vector<distance> distances = readDistances("Distances.csv");
    std::vector<location> locations = readLocations("Locations.csv");

    Graph<std::string> graph;

    int i = 1;
    for (int id : avoidNodes) {
        distances.erase(distances.begin() + id - i);
        i++;
    }
    
    for (location element : locations) {
        if (graph.addVertex(element.CODE)) {
            auto v = graph.getVertexSet();
            v[element.Id - 1]->setParking(element.parking);
        }
    }

    for (distance element : distances) {
       if (graph.addEdge(element.CODE1, element.CODE2, element.Driving, element.Walking)) {}
    }

    return graph;
}

