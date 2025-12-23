#include "Graph.h"
#include <fstream>
#include <iostream>

vector<Edge> edges;
int V, E;
bool graphLoaded = false;

bool loadGraph(const string& filename) {
    ifstream in(filename);
    if (!in) return false;

    in >> V >> E;
    edges.clear();

    for (int i = 0; i < E; i++) {
        char a, b;
        int w;
        in >> a >> b >> w;
        edges.push_back({a - 'A', b - 'A', w});
    }

    in.close();
    graphLoaded = true;
    return true;
}

void displayGraph() {
    cout << "\nGraph Edges:"<<endl;
    for (auto e : edges) {
        cout << char(e.u + 'A') << " -- "
             << char(e.v + 'A')
             << " (Weight " << e.w << ")"<<endl;
    }
}
