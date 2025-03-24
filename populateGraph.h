#include "CSV/readLocations.h"
#include "CSV/readDistances.h"
#include "data_structures/Graph.h"

Graph<std::string>  populate(std::vector<int> avoidNodes, std::vector<std::pair<int, int>> avoidSegments) {

    std::vector<distance> distances = readDistances("Distances.csv");
    std::vector<location> locations = readLocations("Locations.csv");

    Graph<std::string> graph;

    int i = 1;
    for (int id : avoidNodes) {
        locations.erase(distances.begin() + id - i);
        i++;
    }
    
    for (location element : locations) {
        if (graph.addVertex(element.CODE)) {
            auto v = graph.getVertexSet();
            v[element.Id - 1]->setParking(element.parking);
        }
    }

    std::vector<std::pair<std::string, std::string>> codes;
    for (std::pair<int, int> element : avoidSegments) {
        std::string code_first = locations[element.first - i];
        i++;
        std::string code_second = locations[element.second - i];
        i++;
        codes.emplace_back(code_first, code_second);
    }

    for (distance element : distances) {
       bool shouldSkip = false;
       for (const auto& avoidEdge : avoidSegmentCodes) {
            if ((avoidEdge.first == element.CODE1 && avoidEdge.second == element.CODE2) ||
                (avoidEdge.first == element.CODE2 && avoidEdge.second == element.CODE1)) {
                shouldSkip = true;
                break;
            }
        }

        if (!shouldSkip) {
            graph.addEdge(element.CODE1, element.CODE2, element.Driving, element.Walking);
        }

    }

    return graph;
}

