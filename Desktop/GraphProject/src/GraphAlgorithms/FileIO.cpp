#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

extern vector<Edge> lastMST;
extern vector<int> lastPath;
extern int lastDistance;

void saveResults() {
    ofstream mstFile("mst.txt");
    int total = 0;

    mstFile << "Minimum Spanning Tree:"<<endl;
    for (auto e : lastMST) {
        mstFile << char(e.u + 'A') << " "
                << char(e.v + 'A') << " "
                << e.w << endl;
        total += e.w;
    }
    mstFile << "Total Weight = " << total << endl;
    mstFile.close();

    ofstream pathFile("shortest_path.txt");
    pathFile << "Shortest Path:\n";
    for (int i = 0; i < lastPath.size(); i++) {
        pathFile << char(lastPath[i] + 'A');
        if (i != lastPath.size() - 1)
            pathFile << " -> ";
    }
    pathFile << "\nTotal Cost = " << lastDistance << endl;
    pathFile.close();

    cout << "Results saved to mst.txt and shortest_path.txt"<<endl;
}

void visualizeGraph() {
    ofstream dot("graph.dot");
    dot << "graph G {"<<endl;
    for (auto e : edges) {
        dot << char(e.u + 'A') << " -- "
            << char(e.v + 'A')
            << " [label=\"" << e.w << "\"];"<<endl;
    }
    dot << "}"<<endl;
    dot.close();

    system("dot -Tpng graph.dot -o graph.png");
    system("start graph.png");
}
