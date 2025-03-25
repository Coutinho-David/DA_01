// In populateGraph.h
#ifndef POPULATE_GRAPH_H
#define POPULATE_GRAPH_H



#include "readLocations.h"
#include "readDistances.h"
#include <unordered_map>
#include "data_structures/Graph.h"

std::unordered_map<std::string, int> codeToId;  // Maps CODE -> ID

Graph<int> populate() {
    std::vector<DistanceData> distances = readDistances("Distances.csv");
    std::vector<location> locations = readLocations("Locations.csv");

    Graph<int> graph;

    for (location element : locations) {
        codeToId[element.CODE] = element.Id;  // Store CODE -> ID mapping
        if (graph.addVertex(element.Id)) {
            auto v = graph.getVertexSet();
            v[element.Id - 1]->setParking(element.parking);
        }
    }

    for (DistanceData element : distances) {
        int id1 = codeToId[element.CODE1];
        int id2 = codeToId[element.CODE2];
        graph.addEdge(id1, id2, element.Driving, element.Walking);
    }

    return graph;
}

#endif // POPULATE_GRAPH_H