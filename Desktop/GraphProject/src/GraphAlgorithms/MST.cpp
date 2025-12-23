#include "MST.h"
#include <algorithm>
#include <iostream>

vector<Edge> lastMST;

int findSet(int x, vector<int>& parent) {
    if (parent[x] == x)
        return x;
    return parent[x] = findSet(parent[x], parent);
}

void kruskalMST() {
    vector<int> parent(V);
    for (int i = 0; i < V; i++)
        parent[i] = i;

    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b) { return a.w < b.w; });

    lastMST.clear();
    int total = 0;

    for (auto e : edges) {
        int x = findSet(e.u, parent);
        int y = findSet(e.v, parent);

        if (x != y) {
            parent[y] = x;
            lastMST.push_back(e);
            total += e.w;
        }
    }

    cout << endl<<"Kruskal Minimum Spanning Tree:"<<endl;
    for (auto e : lastMST) {
        cout << char(e.u + 'A') << " - "
             << char(e.v + 'A')
             << " (Weight " << e.w << ")"<<endl;
    }
    cout << "Total Weight = " << total << endl;
}
