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

/**
 * @brief Computes the optimal driving and walking route between two points.
 *
 * This function finds the best parking node along the way and determines the
 * most efficient route by combining driving and walking segments. If no
 * valid parking node is found within the maximum allowed walking time,
 * an alternative approximate solution is attempted.
 *
 * @param graph A reference to the graph representing the map.
 * @param s The starting node (source).
 * @param t The destination node (target).
 * @param maxWalkTime The maximum allowed walking time from parking to the destination.
 *
 * @return String containing the best or alternative route,
 *         including driving paths, walking paths, parking nodes, and total times.
 *
 * @note **Time Complexity:** O(V^2 log V + E) when iterating over multiple parking options.
*/
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
        auto drivingPath = getPath(&graph, s, parkVertex->getInfo());
        int drivingTime = parkVertex->getDist();
        if (drivingPath.empty()) continue;

        dijkstra_walking(&graph, parkVertex->getInfo());
        auto walkingPath = getPath(&graph, parkVertex->getInfo(), t);
        int walkingTime = graph.findVertex(t)->getDist();
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

        for (auto parkVertex : graph.getVertexSet()) {
            if (!parkVertex->isParking()) continue;

            dijkstra_driving(&graph, s);
            auto drivingPath = getPath(&graph, s, parkVertex->getInfo());
            int drivingTime = parkVertex->getDist();
            if (drivingPath.empty()) continue;

            dijkstra_walking(&graph, parkVertex->getInfo());
            auto walkingPath = getPath(&graph, parkVertex->getInfo(), t);
            int walkingTime = graph.findVertex(t)->getDist();
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
