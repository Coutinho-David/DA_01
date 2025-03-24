// In populateGraph.h
#ifndef POPULATE_GRAPH_H
#define POPULATE_GRAPH_H



#include "readLocations.h"
#include "readDistances.h"

#include "data_structures/Graph.h"

Graph<std::string>  populate() {
    
    std::vector<DistanceData> distances = readDistances("Distances.csv");
    std::vector<location> locations = readLocations("Locations.csv");

    Graph<std::string> graph;
    
    for (location element : locations) {
        if (graph.addVertex(element.CODE)) {
            auto v = graph.getVertexSet();
            v[element.Id - 1]->setParking(element.parking);
        }
    }

    for (DistanceData element : distances) {
       if (graph.addEdge(element.CODE1, element.CODE2, element.Driving, element.Walking)) {}
    }

    return graph;
}


#endif // POPULATE_GRAPH_H