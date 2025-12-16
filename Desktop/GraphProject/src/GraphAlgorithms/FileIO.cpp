#include "FileIO.h"
#include <fstream>
#include <sstream>

using namespace std;

FileIO::GraphData FileIO::readGraph(const string& filename) {
    GraphData data;
    ifstream file(filename);

    if (!file.is_open()) return data;

    string line;
    getline(file, line);
    stringstream first(line);
    first >> data.numVertices;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string u, v;
        int w = 1;

        if (ss >> u >> v >> w || ss >> u >> v) {
            data.edges.push_back(make_tuple(u, v, w));
        }
    }

    file.close();
    return data;
}

bool FileIO::writeMST(const string& filename,
                     const vector<tuple<string, string, int>>& mstEdges,
                     int totalWeight) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "MST Total Weight: " << totalWeight << "\n";
    for (const auto& edge : mstEdges) {
        file << get<0>(edge) << " - " << get<1>(edge)
             << " (" << get<2>(edge) << ")\n";
    }

    file.close();
    return true;
}

bool FileIO::writeShortestPath(const string& filename,
                              const vector<string>& path,
                              int totalDistance) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "Shortest Path Distance: " << totalDistance << "\nPath: ";
    for (size_t i = 0; i < path.size(); ++i) {
        file << path[i] << (i + 1 < path.size() ? " -> " : "\n");
    }

    file.close();
    return true;
}
