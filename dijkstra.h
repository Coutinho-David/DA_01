#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "data_structures/Graph.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>
#include <sstream>
#include <iostream>
#include "data_structures/MutablePriorityQueue.h"

using namespace std;

template <class T>
bool relax_driving(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getWeight()[0] < edge->getDest()->getDist()) { // we have found a better way to reach v
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeight()[0]); // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}

template <class T>
void dijkstra_driving(Graph<T> *g, int origin) {
    // Initialize the vertices
    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    auto s = g->findVertex(origin);
    if (!s) return;  // Safety check in case the origin is not found
    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        for (auto e : v->getAdj()) {
            auto oldDist = e->getDest()->getDist();
            if (relax_driving(e)) {
                if (oldDist == INF) {
                    q.insert(e->getDest());
                } else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

template <class T>
static std::vector<T> getPath(Graph<T> *g, int origin, int dest) {
    std::vector<T> res;
    auto v = g->findVertex(dest);
    if (v == nullptr || v->getDist() == INF) { // missing or disconnected
        return res;
    }
    res.push_back(v->getInfo());
    while (v->getPath() != nullptr) {
        v = v->getPath()->getOrig();
        res.push_back(v->getInfo());
    }
    reverse(res.begin(), res.end());
    if (res.empty() || res[0] != origin) {
        std::cout << "Origin not found!!" << std::endl;
    }
    return res;
}

// function to call to BestDrivingRoute

template <class T>
std::string bestDrivingRoute(Graph<T> *g, int s, int t) {
    dijkstra_driving(g, s);  // Run Dijkstra from source `s`
    
    std::vector<T> path = getPath(g, s, t);
    if (path.empty()) {
        return "BestDrivingRoute:none";
    }

    std::ostringstream result;
    result << "BestDrivingRoute:";
    
    for (size_t i = 0; i < path.size(); i++) {
        result << path[i];
        if (i != path.size() - 1) {
            result << ",";
        }
    }

    // Append total distance
    result << "(" << g->findVertex(t)->getDist() << ")";
    
    return result.str();
}

// function to call to AlternativeDrivingRoute

template <class T>
std::string alternativeDrivingRoute(Graph<T> *g, int s, int t) {
    // Find the best route first
    dijkstra_driving(g, s);
    std::vector<T> bestPath = getPath(g, s, t);
    if (bestPath.empty()) {
        return "AlternativeDrivingRoute:none";
    }
    
    int bestDist = g->findVertex(t)->getDist();
    
    // Remove edges that were part of the best path
    for (size_t i = 0; i < bestPath.size() - 1; i++) {
        auto v = g->findVertex(bestPath[i]);
        if (v) {
            v->removeEdge(bestPath[i + 1]);
        }
    }
    
    // Find an alternative route
    dijkstra_driving(g, s);
    std::vector<T> altPath = getPath(g, s, t);
    
    if (altPath.empty() || g->findVertex(t)->getDist() < bestDist) {
        return "AlternativeDrivingRoute:none";
    }

    std::ostringstream result;
    result << "AlternativeDrivingRoute:";
    
    for (size_t i = 0; i < altPath.size(); i++) {
        result << altPath[i];
        if (i != altPath.size() - 1) {
            result << ",";
        }
    }

    // Append total distance
    result << "(" << g->findVertex(t)->getDist() << ")";
    
    return result.str();
}

// function to call to BestAndAlternativeDrivingRoute

template <class T>
std::string bestAndAlternativeDrivingRoute(Graph<T> *g, int s, int t, vector<int> avoidNodes, vector<pair<int, int>> avoidSegments, int includeNode ) {
    if(avoidNodes.empty() && avoidSegments.empty() && includeNode == -1) {
        std::string best = bestDrivingRoute(g, s, t);
        std::string alternative = alternativeDrivingRoute(g, s, t);
        return best + "\n" + alternative;
    }
    return restrictedDrivingRoute(g, s, t, includeNode);
}

// function to call to RestrictedDrivingRoute

template <class T>
std::string restrictedDrivingRoute(Graph<T> *g, int s, int t, int includeNode) {
    std::vector<T> path;
    int totalDistance = INF;
    if (includeNode != -1) {
        dijkstra_driving(g, s);
        auto firstHalf = getPath(g, s, includeNode);
        int firstDist = g->findVertex(includeNode)->getDist();

        dijkstra_driving(g, includeNode);
        auto secondHalf = getPath(g, includeNode, t);
        int secondDist = g->findVertex(t)->getDist();

        if (!firstHalf.empty() && !secondHalf.empty()) {
            totalDistance = firstDist + secondDist;
            firstHalf.pop_back();
            path.insert(path.end(), firstHalf.begin(), firstHalf.end());
            path.insert(path.end(), secondHalf.begin(), secondHalf.end());
        }
    } else {
        dijkstra_driving(g, s); 
        path = getPath(g, s, t);    
        totalDistance = g->findVertex(t)->getDist();
    }

    if (path.empty()) return "RestrictedDrivingRoute:none";
    std::ostringstream result;
    result << "RestrictedDrivingRoute:";
    for (size_t i = 0; i < path.size(); i++) {
        result << path[i];
        if (i != path.size() - 1) result << ",";
    }
    result << "(" << totalDistance << ")";

    return result.str();
}

    template <class T>
bool relax_walking(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    if (edge->getOrig()->getDist() + edge->getWeight()[1] < edge->getDest()->getDist()) { // we have found a better way to reach v
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeight()[1]); // d[v] = d[u] + w(u,v)
        edge->getDest()->setPath(edge); // set the predecessor of v to u; in this case the edge from u to v
        return true;
    }
    return false;
}

template <class T>
void dijkstra_walking(Graph<T> *g, int origin) {
    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    auto s = g->findVertex(origin);
    if (!s) return;
    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        for (auto e : v->getAdj()) {
            auto oldDist = e->getDest()->getDist();
            if (relax_walking(e)) {
                if (oldDist == INF) {
                    q.insert(e->getDest());
                } else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}




#endif // DIJKSTRA_H
