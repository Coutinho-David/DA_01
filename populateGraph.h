#ifndef POPULATE_GRAPH_H
#define POPULATE_GRAPH_H


#include "csv/readLocations.h"
#include "csv/readDistances.h"
#include <unordered_map>
#include "data_structures/Graph.h"

std::unordered_map<std::string, int> codeToId;  // Maps CODE -> ID

Graph<int> populate(std::vector<int> &avoidNodes, std::vector<std::pair<int, int>> &avoidSegments) {
    std::vector<DistanceData> distanceData = readDistances("csv/Distances.csv");
    std::vector<location> locations = readLocations("csv/Locations.csv");

    Graph<int> graph;
    
    int i = 1;
    for (int id : avoidNodes) {
        locations.erase(locations.begin() + id - i);
        i++;
    }

    int j = 0;
    for (location element : locations) {
        codeToId[element.CODE] = element.Id;
        if (graph.addVertex(element.Id)) {
            auto v = graph.getVertexSet();
            v[j]->setParking(element.parking);
            j++;
        }
    }

    for (DistanceData element : distanceData) {
       bool shouldSkip = false;
       for (const auto& avoidEdge : avoidSegments) {
            if ((avoidEdge.first == codeToId[element.CODE1] && avoidEdge.second == codeToId[element.CODE2]) || (avoidEdge.first == codeToId[element.CODE2] && avoidEdge.second == codeToId[element.CODE1])) {
                shouldSkip = true;
                break;
            }
       }
        if (!shouldSkip) {
            int id1 = codeToId[element.CODE1];
            int id2 = codeToId[element.CODE2];
            graph.addBidirectionalEdge(id1, id2, element.Driving, element.Walking);
            }

    }

    return graph;
}

#endif
