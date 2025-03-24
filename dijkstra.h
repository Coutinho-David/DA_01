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
void dijkstra_driving(Graph<T> * g, const std::string &origin) {
    // Initialize the vertices
    for(auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    auto s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        for(auto e : v->getAdj()) {
            auto oldDist = e->getDest()->getDist();
            if (relax_driving(e)) {
                if (oldDist == INF) {
                    q.insert(e->getDest());
                }
                else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

template <class T>
static std::vector<T> getPath(Graph<T> * g, const std::string &origin, const std::string &dest) {
    std::vector<T> res;
    auto v = g->findVertex(dest);
    if (v == nullptr || v->getDist() == INF) { // missing or disconnected
        return res;
    }
    res.push_back(v->getInfo());
    while(v->getPath() != nullptr) {
        v = v->getPath()->getOrig();
        res.push_back(v->getInfo());
    }
    reverse(res.begin(), res.end());
    if(res.empty() || res[0] != origin) {
        std::cout << "Origin not found!!" << std::endl;
    }
    return res;
}

template <class T>
std::string bestDrivingRoute(Graph<T> *g, const std::string &s, const std::string &t) {
    dijkstra_driving(g, s);  // Run Dijkstra from source `s`
    
    std::vector<T> path = getPath(g, s, t);
    if (path.empty()) {
        return "Yo, no route found!";
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

#endif
