#include "Dijkstra.h"
#include "Graph.h"
#include <queue>
#include <climits>

using namespace std;

Dijkstra::PathResult Dijkstra::findShortestPath(const Graph& g,
                                                const string& s,
                                                const string& e) {
    PathResult r;
    int n = g.getNumVertices();
    int si = g.getNodeIndex(s);
    int ei = g.getNodeIndex(e);

    if (si == -1 || ei == -1) return r;

    vector<int> d(n, INT_MAX), p(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    d[si] = 0;
    q.push(make_pair(0, si));

    while (!q.empty()) {
        int dist = q.top().first;
        int u = q.top().second;
        q.pop();

        if (dist > d[u]) continue;

        for (const auto& neighbor : g.getAdjacencyList()[u]) {
            int v = neighbor.first;
            int w = neighbor.second;
            int nd = d[u] + w;

            if (nd < d[v]) {
                d[v] = nd;
                p[v] = u;
                q.push(make_pair(nd, v));
            }
        }
    }

    if (d[ei] == INT_MAX) return r;

    for (int v = ei; v != -1; v = p[v]) {
        r.path.insert(r.path.begin(), g.getNodeName(v));
    }

    r.totalDistance = d[ei];
    r.pathExists = true;
    return r;
}
