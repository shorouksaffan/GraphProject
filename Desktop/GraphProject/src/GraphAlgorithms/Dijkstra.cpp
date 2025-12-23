#include "Dijkstra.h"
#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>

vector<int> lastPath;
int lastDistance = 0;

void dijkstra() {
    vector<vector<pair<int,int>>> adj(V);
    for (auto e : edges) {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }

    char s, d;
    cout << "Enter start node: ";
    cin >> s;
    cout << "Enter destination node: ";
    cin >> d;

    int src = s - 'A';
    int dest = d - 'A';

    if (src < 0 || src >= V || dest < 0 || dest >= V) {
        cout << "Error: Node not found!"<<endl;
        return;
    }

    vector<int> dist(V, INT_MAX), parent(V, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto v : adj[u]) {
            if (dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                parent[v.first] = u;
                pq.push({dist[v.first], v.first});
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "No path exists"<<endl;
        return;
    }

    lastPath.clear();
    for (int v = dest; v != -1; v = parent[v])
        lastPath.push_back(v);

    reverse(lastPath.begin(), lastPath.end());
    lastDistance = dist[dest];

    cout << "\nShortest Path: ";
    for (int i = 0; i < lastPath.size(); i++) {
        cout << char(lastPath[i] + 'A');
        if (i != lastPath.size() - 1) cout << " -> ";
    }
    cout << "\nTotal Cost = " << lastDistance << endl;
}
