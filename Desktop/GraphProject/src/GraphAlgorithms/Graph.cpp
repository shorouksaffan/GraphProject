#include "Graph.h"
#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

Graph::Graph() : numVertices(0), isDirected(false), isWeighted(true) {}

bool Graph::readFromFile(const string& fname) {
    FileIO::GraphData data = FileIO::readGraph(fname);
    if (data.edges.empty()) return false;

    isDirected = data.isDirected;
    isWeighted = data.isWeighted;

    vector<string> nodes;
    for (auto& edge : data.edges) {
        string u = get<0>(edge), v = get<1>(edge);
        if (find(nodes.begin(), nodes.end(), u) == nodes.end()) nodes.push_back(u);
        if (find(nodes.begin(), nodes.end(), v) == nodes.end()) nodes.push_back(v);
    }

    numVertices = nodes.size();
    adjList.resize(numVertices);

    for (int i = 0; i < numVertices; i++) {
        nodeToIndex[nodes[i]] = i;
        indexToNode[i] = nodes[i];
    }

    for (auto& edge : data.edges) {
        int u = nodeToIndex[get<0>(edge)];
        int v = nodeToIndex[get<1>(edge)];
        int w = get<2>(edge);

        adjList[u].push_back({v, w});
        if (!isDirected) adjList[v].push_back({u, w});
    }

    return true;
}

void Graph::display() const {
    cout << "\nVertices: " << numVertices << "\n";
    for (int i = 0; i < numVertices; i++) {
        cout << indexToNode.at(i) << ": ";
        for (auto& n : adjList[i])
            cout << indexToNode.at(n.first) << "(" << n.second << ") ";
        cout << "\n";
    }
}

int Graph::getNodeIndex(const string& node) const {
    auto it = nodeToIndex.find(node);
    return it != nodeToIndex.end() ? it->second : -1;
}

string Graph::getNodeName(int index) const {
    auto it = indexToNode.find(index);
    return it != indexToNode.end() ? it->second : "";
}

const vector<vector<pair<int, int>>>& Graph::getAdjacencyList() const {
    return adjList;
}

vector<tuple<int, int, int>> Graph::getAllEdges() const {
    vector<tuple<int, int, int>> edges;
    for (int u = 0; u < numVertices; u++) {
        for (auto& n : adjList[u]) {
            int v = n.first;
            if (!isDirected && u < v) edges.push_back({u, v, n.second});
            else if (isDirected) edges.push_back({u, v, n.second});
        }
    }
    return edges;
}

void Graph::visualizeGraph() {
    if (numVertices == 0) return;

    ofstream f("graph.dot");
    f << "graph G {\n";
    for (int i = 0; i < numVertices; i++) f << "  " << indexToNode.at(i) << ";\n";
    f << "\n";

    for (int u = 0; u < numVertices; u++) {
        for (auto& n : adjList[u]) {
            int v = n.first;
            if (!isDirected && u < v)
                f << "  " << indexToNode.at(u) << " -- " << indexToNode.at(v)
                  << " [label=\"" << n.second << "\"];\n";
        }
    }
    f << "}\n";

    system("dot -Tpng graph.dot -o graph.png");
    cout << "Graph image: graph.png\n";
}
