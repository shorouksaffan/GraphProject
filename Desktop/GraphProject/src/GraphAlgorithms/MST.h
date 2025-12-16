#ifndef MST_H
#define MST_H
#include "Graph.h"
#include <vector>
#include <tuple>
#include <string>
using namespace std;
class MST
{
public:
    // Prim's Algorithm
    static vector<tuple<string, string, int>> prim(const Graph& graph, const string& startNode);
    // Kruskal's Algorithm
    static vector<tuple<string, string, int>> kruskal(const Graph& graph);

    static int calculateTotalWeight(const vector<tuple<string,string, int>>& edges);
};

#endif
