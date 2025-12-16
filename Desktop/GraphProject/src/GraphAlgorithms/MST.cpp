#include "MST.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

// Helper class for Kruskal's algorithm
class DisjointSet {
private:
    vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            // Union by rank
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

vector<tuple<string, string, int>> MST::prim(const Graph& graph, const string& startNode) {
    int n = graph.getNumVertices();
    int start = graph.getNodeIndex(startNode);

    if (start == -1) {
        cerr << "Error: Start node '" << startNode << "' not found in graph." << endl;
        return {};
    }

    vector<bool> inMST(n, false);
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);

    // Min-heap priority queue: (weight, vertex)
    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    key[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        // Explore neighbors
        for (const auto& neighbor : graph.getAdjacencyList()[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({weight, v});
            }
        }
    }

    // Build MST edges from parent array
    vector<tuple<string, string, int>> mstEdges;
    for (int v = 0; v < n; v++) {
        if (parent[v] != -1) {
            // Find the weight between parent[v] and v
            int weight = 0;
            for (const auto& neighbor : graph.getAdjacencyList()[parent[v]]) {
                if (neighbor.first == v) {
                    weight = neighbor.second;
                    break;
                }
            }

            mstEdges.push_back({
                graph.getNodeName(parent[v]),
                graph.getNodeName(v),
                weight
            });
        }
    }

    return mstEdges;
}

vector<tuple<string, string, int>> MST::kruskal(const Graph& graph) {
    auto edges = graph.getAllEdges();
    int n = graph.getNumVertices();

    // Sort edges by weight (ascending)
    sort(edges.begin(), edges.end(),
         [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
             return get<2>(a) < get<2>(b);
         });

    DisjointSet ds(n);
    vector<tuple<string, string, int>> mstEdges;

    for (const auto& edge : edges) {
        int u = get<0>(edge);
        int v = get<1>(edge);
        int weight = get<2>(edge);

        if (ds.find(u) != ds.find(v)) {
            ds.unite(u, v);
            mstEdges.push_back({
                graph.getNodeName(u),
                graph.getNodeName(v),
                weight
            });

            // MST for n vertices has n-1 edges
            if (mstEdges.size() == n - 1) {
                break;
            }
        }
    }

    return mstEdges;
}

int MST::calculateTotalWeight(const vector<tuple<string, string, int>>& edges) {
    int total = 0;
    for (const auto& edge : edges) {
        total += get<2>(edge);
    }
    return total;
}
