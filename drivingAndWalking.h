#ifndef DRIVING_WALKING_ROUTE_H
#define DRIVING_WALKING_ROUTE_H

#include "dijkstra.h"
#include <limits>
#include <vector>
#include <string>
#include <sstream>

std::string drivingAndWalkingRoute(Graph<int> &g, int s, int t, int maxWalkTime) {
    
    int bestParkNode = -1;
    std::vector<int> bestDrivingRoute;
    std::vector<int> bestWalkingRoute;
    int bestDrivingTime = 0;
    int bestWalkingTime = 0;
    int bestTotalTime = std::numeric_limits<int>::max();

    for (auto parkVertex : g.getVertexSet()) {
        if (!parkVertex->isParking()) continue;
        
        // Find driving route to parking node \(using weight1 - driving time)
        dijkstra_driving(&g, s);
        auto drivingPath = getPath(&g, s, parkVertex->getInfo());
        int drivingTime = parkVertex->getDist();
        
        // Skip if driving path is impossible
        if (drivingPath.empty()) continue;

        // Find walking route from parking node to destination (using weight2 - walking time)
        dijkstra_walking(&g, parkVertex->getInfo());
        auto walkingPath = getPath(&g, parkVertex->getInfo(), t);
        int walkingTime = g.findVertex(t)->getDist();
        
        // Skip if walking path is impossible
        if (walkingPath.empty()) continue;

        // Check walking time constraint
        if (walkingTime > maxWalkTime) continue;

        // Update best route if this route is better
        int totalTime = drivingTime + walkingTime;
        if (totalTime < bestTotalTime || 
            (totalTime == bestTotalTime && walkingTime > bestWalkingTime)) {
            bestTotalTime = totalTime;
            bestParkNode = parkVertex->getInfo();
            bestDrivingTime = drivingTime;
            bestWalkingTime = walkingTime;
            
            // Store paths separately
            bestDrivingRoute = drivingPath;
            bestWalkingRoute = walkingPath;
        }
    }
 
    // Format output
    if (bestParkNode == -1) {
        return "DrivingAndWalkingRoute:none";
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

#endif // DRIVING_WALKING_ROUTE_H
