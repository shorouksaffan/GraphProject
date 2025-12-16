#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include <tuple>

using namespace std;

class FileIO {
public:
    struct GraphData {
        bool isDirected;
        bool isWeighted;
        int numVertices;
        vector<tuple<string, string, int>> edges;
        GraphData() : isDirected(false), isWeighted(true), numVertices(0) {}
    };

    static GraphData readGraph(const string& filename);
    static bool writeMST(const string& filename,
                         const vector<tuple<string, string, int>>& mstEdges,
                         int totalWeight);
    static bool writeShortestPath(const string& filename,
                                  const vector<string>& path,
                                  int totalDistance);
};

#endif
