#ifndef DRIVING_WALKING_ROUTE_H
#define DRIVING_WALKING_ROUTE_H

#include "dijkstra.h"
#include <limits>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>

struct route {
    int parkNode;
    std::vector<int> drivingPath;
    int drivingTime;
    std::vector<int> walkingPath;
    int walkingTime;
    int totalTime;
};

std::string drivingAndWalkingRoute(Graph<int> &graph, int s, int t, int maxWalkTime) {
    
    int bestParkNode = -1;
    std::vector<int> bestDrivingRoute;
    std::vector<int> bestWalkingRoute;
    int bestDrivingTime = 0;
    int bestWalkingTime = 0;
    int bestTotalTime = INT_MAX;

    for (auto parkVertex : graph.getVertexSet()) {
        if (!parkVertex->isParking()) continue;
        
        dijkstra_driving(&graph, s);
        auto drivingPath = getPath(&g, s, parkVertex->getInfo());
        int drivingTime = parkVertex->getDist();
        if (drivingPath.empty()) continue;

        dijkstra_walking(&g, parkVertex->getInfo());
        auto walkingPath = getPath(&g, parkVertex->getInfo(), t);
        int walkingTime = g.findVertex(t)->getDist();
        if (walkingPath.empty()) continue;

        if (walkingTime > maxWalkTime) continue;

        int totalTime = drivingTime + walkingTime;
        if (totalTime < bestTotalTime || (totalTime == bestTotalTime && walkingTime > bestWalkingTime)) {
            bestTotalTime = totalTime;
            bestParkNode = parkVertex->getInfo();
            bestDrivingTime = drivingTime;
            bestWalkingTime = walkingTime;
            bestDrivingRoute = drivingPath;
            bestWalkingRoute = walkingPath;
        }
    }

    //start approximate solution 
    if (bestParkNode == -1) {
        std::vector<route> alternatives;

        for (auto parkVertex : g.getVertexSet()) {
            if (!parkVertex->isParking()) continue;

            dijkstra_driving(&g, s);
            auto drivingPath = getPath(&g, s, parkVertex->getInfo());
            int drivingTime = parkVertex->getDist();
            if (drivingPath.empty()) continue;

            dijkstra_walking(&g, parkVertex->getInfo());
            auto walkingPath = getPath(&g, parkVertex->getInfo(), t);
            int walkingTime = g.findVertex(t)->getDist();
            if (walkingPath.empty()) continue;

            route option;
            option.parkNode = parkVertex->getInfo();
            option.drivingPath = drivingPath;
            option.drivingTime = drivingTime;
            option.walkingPath = walkingPath;
            option.walkingTime = walkingTime;
            option.totalTime = drivingTime + walkingTime;
            alternatives.push_back(option);
        }

        if (alternatives.empty()) {
            return "DrivingAndWalkingRoute: none";
        }

        std::sort(alternatives.begin(), alternatives.end(), [](const route& a, const route& b) { 
                if (a.totalTime != b.totalTime) return a.totalTime < b.totalTime;
                return a.walkingTime < b.walkingTime;
        });

        int numAlternatives = std::min(2, (int)alternatives.size());
        if (numAlternatives == 0) return "DrivingAndWalkingRoute:none";

        std::ostringstream result;
        for (int i = 0; i < numAlternatives; ++i) {
            auto alt = alternatives[i];
            result << "DrivingRoute" << (i+1) << ":";
        
            for (size_t j = 0; j < alt.drivingPath.size(); ++j) {
                result << alt.drivingPath[j];
                if (j != alt.drivingPath.size() - 1) result << ",";
            }

            result << "(" << alt.drivingTime << ")\n";
            result << "ParkingNode" << (i+1) << ":" << alt.parkNode << "\n";
            result << "WalkingRoute" << (i+1) << ":";
            for (size_t j = 0; j < alt.walkingPath.size(); ++j) {
                result << alt.walkingPath[j];
                if (j != alt.walkingPath.size() - 1) result << ",";
            }
            result << "(" << alt.walkingTime << ")\n";
            result << "TotalTime" << (i+1) << ":" << alt.totalTime;
            if (i < numAlternatives - 1) result << "\n";
        }
        return result.str();
    }

    std::ostringstream result;
    result << "DrivingRoute:";
    for (size_t i = 0; i < bestDrivingRoute.size(); i++) {
        result << bestDrivingRoute[i];
        if (i != bestDrivingRoute.size() - 1) result << ",";
    }
    result << "(" << bestDrivingTime << ")\n";
    result << "ParkingNode:" << bestParkNode << "\n";
    result << "WalkingRoute:";
    for (size_t i = 0; i < bestWalkingRoute.size(); i++) {
        result << bestWalkingRoute[i];
        if (i != bestWalkingRoute.size() - 1) result << ",";
    }
    result << "(" << bestWalkingTime << ")\n";
    result << "TotalTime:" << bestTotalTime;

    return result.str();
}

#endif 
