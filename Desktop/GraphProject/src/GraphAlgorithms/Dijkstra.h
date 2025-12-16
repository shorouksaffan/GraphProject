#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Graph.h"
#include <vector>
#include <string>

using namespace std;

class Dijkstra
{
public:
    struct PathResult {
        vector<string> path;
        int totalDistance;
        bool pathExists;
    };
    static PathResult findShortestPath(const Graph& graph, const string& start, const string& end);
};

#endif
