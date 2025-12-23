#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
using namespace std;

struct Edge {
    int u, v, w;
};

extern int V, E;
extern bool graphLoaded;
extern vector<Edge> edges;

bool loadGraph(const string& filename);
void displayGraph();

#endif
