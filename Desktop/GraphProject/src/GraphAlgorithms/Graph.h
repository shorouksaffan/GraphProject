#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
public:
    Graph();
    bool readFromFile(const string& filename);
    void display() const;
    int getNodeIndex(const string& node) const;
    string getNodeName(int index) const;
    int getNumVertices() const { return numVertices; }
    const vector<vector<pair<int, int>>>& getAdjacencyList() const;
    vector<tuple<int, int, int>> getAllEdges() const;
    void visualizeGraph();

private:
    int numVertices;
    bool isDirected, isWeighted;
    unordered_map<string, int> nodeToIndex;
    unordered_map<int, string> indexToNode;
    vector<vector<pair<int, int>>> adjList;
};

#endif
