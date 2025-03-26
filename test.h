#include "data_structures/Graph.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <climits>

struct DistanceData {
    std::string CODE1;
    std::string CODE2;
    int Driving;
    int Walking;
};

DistanceData distance1 = {"TR", "CA", 10, 20};
DistanceData distance2 = {"TR", "BAO", INT_MAX, 15};
DistanceData distance3 = {"CA", "BAO", 5, 8};
DistanceData distance4 = {"CA", "AL", 8, 25};
DistanceData distance5 = {"BAO", "SE", 12, 10};
DistanceData distance6 = {"SE", "RB", INT_MAX, 10};
DistanceData distance7 = {"BAO", "FOZ", 20, 25};
DistanceData distance8 = {"AL", "RB", 15, 30};
DistanceData distance9 = {"AL", "FOZ", 30, 50};
DistanceData distance10 = {"FOZ", "RB", INT_MAX, 12};
DistanceData distance11 = {"AL", "CL", 6, 18};
DistanceData distance12 = {"FOZ", "CL", 14, 20};

struct location {
    std::string location;
    int Id;
    std::string CODE;
    bool parking;
};

location location1 = {"TRINDADE", 1, "TR", 0};
location location2 = {"Campo Alegre", 2, "CA", 1};
location location3 = {"Bolhao", 3, "BAO", 1};
location location4 = {"Aliados", 4, "AL", 0};
location location5 = {"Se", 5, "SE", 0};
location location6 = {"RIBEIRA", 6, "RB", 1};
location location7 = {"FOZ", 7, "FOZ", 1};
location location8 = {"Clerigos", 8, "CL", 0};

std::unordered_map<std::string, int> codeToId;

Graph<int> test() {
    std::vector<DistanceData> distances = {distance1, distance2, distance3, distance4, distance5, distance6, distance7, distance8, distance9, distance10, distance11, distance12};
    std::vector<location> locations = {location1, location2, location3, location4, location5, location6, location7, location8};

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
        graph.addBidirectionalEdge(id1, id2, element.Driving, element.Walking);
    }

    return graph;
}

