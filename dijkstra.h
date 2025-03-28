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

/**
 * @brief Relaxation function for driving distances.
 * @tparam T Type of vertex information.
 * @param edge Pointer to the edge being relaxed.
 * @return True if the edge was relaxed, false otherwise.
 * Applies the edge relaxation principles taught in the course.
 */
template <class T>
bool relax_driving(Edge<T> *edge);

/**
 * @brief Dijkstra's algorithm to compute shortest paths when driving.
 * @tparam T Type of vertex information.
 * @param g Pointer to the graph.
 * @param origin Source vertex.
 * @return Shortest paths, when found.
 * @complexity O((V + E) log V), where V is the number of vertices and E is the number of edges.
 */
template <class T>
void dijkstra_driving(Graph<T> *g, int origin);

/**
 * @brief Retrieves the shortest path from origin to destination.
 * @tparam T Type of vertex information.
 * @param g Pointer to the graph.
 * @param origin Source vertex.
 * @param dest Destination vertex.
 * @return Vector containing the path sequence.
 * @complexity O(V), as the path is traced back from the destination to the source.
 */
template <class T>
static std::vector<T> getPath(Graph<T> *g, int origin, int dest);

/**
 * @brief Computes the best driving route from source to destination.
 * @tparam T Type of vertex information.
 * @param g Pointer to the graph.
 * @param s Source vertex.
 * @param t Destination vertex.
 * @return String representation of the best driving route.
 * @complexity O((V + E) log V), due to Dijkstra's algorithm.
 */
template <class T>
std::string bestDrivingRoute(Graph<T> *g, int s, int t);

/**
 * @brief Computes an alternative driving route avoiding the best route's edges.
 * @tparam T Type of vertex information.
 * @param g Pointer to the graph.
 * @param s Source vertex.
 * @param t Destination vertex.
 * @return String representation of the alternative driving route.
 * @complexity O((V + E) log V) for the first Dijkstra call + O(E) for edge removal + O((V + E) log V) for the second Dijkstra call.
 */
template <class T>
std::string alternativeDrivingRoute(Graph<T> *g, int s, int t);

/**
 * @brief Computes the best and second best driving routes.
 * @tparam T Type of vertex information.
 * @param g Pointer to the graph.
 * @param s Source vertex.
 * @param t Destination vertex.
 * @param avoidNodes Nodes to avoid.
 * @param avoidSegments Edges to avoid.
 * @param includeNode Mandatory node to include in the path.
 * @return String representation of the routes.
 * @complexity O((V + E) log V) for Dijkstra plus additional overhead for avoidance logic.
 */
template <class T>
std::string bestAndAlternativeDrivingRoute(Graph<T> *g, int s, int t, vector<int> avoidNodes, vector<pair<int, int>> avoidSegments, int includeNode);

/**
 * @brief Computes a restricted driving route considering specific nodes.
 * @tparam T Type of vertex information.
 * @param g Pointer to the graph.
 * @param s Source vertex.
 * @param t Destination vertex.
 * @param includeNode Mandatory node to include.
 * @return String representation of the restricted driving route.
 * @complexity O((V + E) log V) for each Dijkstra execution (up to 2 times if includeNode is used).
 */
template <class T>
std::string restrictedDrivingRoute(Graph<T> *g, int s, int t, int includeNode);

/**
 * @brief Relaxation function for walking distances.
 * @tparam T Type of vertex information.
 * @param edge Pointer to the edge being relaxed.
 * @return True if the edge was relaxed, false otherwise.
 * Applies the edge relaxation principles taught in the course.
 */
template <class T>
bool relax_walking(Edge<T> *edge);

/**
 * @brief Runs Dijkstra's algorithm to compute shortest paths for walking.
 * @tparam T Type of vertex information.
 * @param g Pointer to the graph.
 * @param origin Source vertex.
 * @complexity O((V + E) log V), as it is based on Dijkstra's algorithm.
 */
template <class T>
void dijkstra_walking(Graph<T> *g, int origin);

template <class T>
bool relax_driving(Edge<T> *edge) {
    if (edge->getOrig()->getDist() + edge->getWeight()[0] < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeight()[0]);
        edge->getDest()->setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstra_driving(Graph<T> *g, int origin) {
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
    if (v == nullptr || v->getDist() == INF) {
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

template <class T>
std::string bestDrivingRoute(Graph<T> *g, int s, int t) {
    dijkstra_driving(g, s);
    
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

    result << "(" << g->findVertex(t)->getDist() << ")";
    
    return result.str();
}


template <class T>
std::string alternativeDrivingRoute(Graph<T> *g, int s, int t) {
    dijkstra_driving(g, s);
    std::vector<T> bestPath = getPath(g, s, t);
    if (bestPath.empty()) {
        return "AlternativeDrivingRoute:none";
    }
    
    int bestDist = g->findVertex(t)->getDist();
    
    for (size_t i = 0; i < bestPath.size() - 1; i++) {
        auto v = g->findVertex(bestPath[i]);
        if (v) {
            v->removeEdge(bestPath[i + 1]);
        }
    }
    
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

    result << "(" << g->findVertex(t)->getDist() << ")";
    
    return result.str();
}


template <class T>
std::string bestAndAlternativeDrivingRoute(Graph<T> *g, int s, int t, vector<int> avoidNodes, vector<pair<int, int>> avoidSegments, int includeNode ) {
    if(avoidNodes.empty() && avoidSegments.empty() && includeNode == -1) {
        std::string best = bestDrivingRoute(g, s, t);
        std::string alternative = alternativeDrivingRoute(g, s, t);
        return best + "\n" + alternative;
    }
    return restrictedDrivingRoute(g, s, t, includeNode);
}


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
bool relax_walking(Edge<T> *edge) {
    if (edge->getOrig()->getDist() + edge->getWeight()[1] < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeight()[1]);
        edge->getDest()->setPath(edge);
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
