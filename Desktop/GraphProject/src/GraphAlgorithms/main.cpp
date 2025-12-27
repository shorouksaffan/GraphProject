#include <iostream>
#include "Graph.h"
#include "MST.h"
#include "Dijkstra.h"
#include "FileIO.h"

using namespace std;

void menu() {
    cout << "Graph Algorithms Menu"<<endl<<endl;
    cout << "1. Load graph from file"<<endl;
    cout << "2. Display graph"<<endl;
    cout << "3. Minimum Spanning Tree"<<endl;
    cout << "4. Shortest Path"<<endl;
    cout << "5. Save results to files"<<endl;
    cout << "6. Visualize graph"<<endl;
    cout << "7. Exit"<<endl;
}

int main() {
    int choice;
     menu();
    while (true) {
         cout<<endl<< "Choose from 1 to 7: ";
        cin >> choice;

        if (choice == 1) {
            string file;
            cout << "Enter graph file name: ";
            cin >> file;

            if (loadGraph(file))
                cout << "Graph loaded successfully"<<endl;
            else
                cout << "Error opening file"<<endl;
        }
        else if (choice == 2) {
            if (!graphLoaded) cout << "Load graph first"<<endl;
            else displayGraph();
        }
        else if (choice == 3) {
            if (!graphLoaded) cout << "Load graph first"<<endl;
            else kruskalMST();
        }
        else if (choice == 4) {
            if (!graphLoaded) cout << "Load graph first"<<endl;
            else dijkstra();
        }
        else if (choice == 5) {
            if (!graphLoaded) cout << "Load graph first"<<endl;
            else saveResults();
        }
        else if (choice == 6) {
            if (!graphLoaded) cout << "Load graph first"<<endl;
            else visualizeGraph();
        }
        else if (choice == 7) {
            cout << "Program ended"<<endl;
            break;
        }
        else {
            cout << "Invalid choice"<<endl;
        }
    }
    return 0;
}
