#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "FileIO.h"
#include "MST.h"
#include "Dijkstra.h"

using namespace std;

void showMenu()
{
    cout << endl<<" Graph Algorithms Menu"<<endl<<endl;
    cout << "1. Load graph from file"<<endl;
    cout << "2. Display graph"<<endl;
    cout << "3. Minimum Spanning Tree (Prim)"<<endl;
    cout << "4. Minimum Spanning Tree (Kruskal)"<<endl;
    cout << "5. Shortest Path (Dijkstra)"<<endl;
    cout << "6. Save results to files"<<endl;
    cout << "7. Visualize graph"<<endl;
    cout << "8. Exit"<<endl;
    cout << "Choose (1-8): ";
}

int main()
{

    Graph graph;
    bool graphLoaded = false;
    int choice;

    /* Results storage */
    vector<tuple<string, string, int>> mstPrim;
    vector<tuple<string, string, int>> mstKruskal;
    int primWeight = 0;
    int kruskalWeight = 0;

    Dijkstra::PathResult shortestPath;

    while (true)
    {
        showMenu();
        cin >> choice;

        /* -------- OPTION 1: LOAD GRAPH -------- */
        if (choice == 1)
        {
            string filename;
            cout << "Enter graph file name:";
            cin >> filename;

            if (graph.readFromFile(filename))
            {
                cout << "Graph loaded successfully"<<endl;
                graphLoaded = true;
            }
            else
            {
                cout << "Error: Cannot open file"<<endl;
            }
        }

        /* -------- OPTION 2: DISPLAY GRAPH -------- */
        else if (choice == 2)
        {
            if (!graphLoaded)
            {
                cout << "Please load a graph first"<<endl;
            }
            else
            {
                graph.display();
            }
        }

        /* -------- OPTION 3: PRIM MST -------- */
        else if (choice == 3)
        {
            if (!graphLoaded)
            {
                cout << "Please load a graph first"<<endl;
                continue;
            }

            string start;
            cout << "Enter start node: ";
            cin >> start;

            mstPrim = MST::prim(graph, start);
            primWeight = MST::calculateTotalWeight(mstPrim);

            cout << endl<<"Prim MST:"<<endl;
            for (auto e : mstPrim)
            {
                cout << get<0>(e) << " - " << get<1>(e)
                     << " (Weight " << get<2>(e) << ")"<<endl;
            }
            cout << "Total Weight = " << primWeight << endl;
        }

        /* -------- OPTION 4: KRUSKAL MST -------- */
        else if (choice == 4)
        {
            if (!graphLoaded)
            {
                cout << "Please load a graph first"<<endl;
                continue;
            }

            mstKruskal = MST::kruskal(graph);
            kruskalWeight = MST::calculateTotalWeight(mstKruskal);

            cout << endl<<"Kruskal MST:"<<endl;
            for (auto e : mstKruskal)
            {
                cout << get<0>(e) << " - " << get<1>(e)
                     << " (Weight " << get<2>(e) << ")"<<endl;
            }
            cout << "Total Weight = " << kruskalWeight << endl;
        }

        /* -------- OPTION 5: SHORTEST PATH -------- */
        else if (choice == 5)
        {
            if (!graphLoaded)
            {
                cout << "Please load a graph first"<<endl;
                continue;
            }

            string start, end;
            cout << "Start node: ";
            cin >> start;
            cout << "End node: ";
            cin >> end;

            shortestPath = Dijkstra::findShortestPath(graph, start, end);

            if (shortestPath.pathExists)
            {
                cout << "Shortest Path: ";
                for (int i = 0; i < shortestPath.path.size(); i++)
                {
                    cout << shortestPath.path[i];
                    if (i != shortestPath.path.size() - 1)
                        cout << " -> ";
                }
                cout << endl<<"Distance = " << shortestPath.totalDistance << endl;
            }
            else
            {
                cout << "No path found"<<endl;
            }
        }

        /* -------- OPTION 6: SAVE TO FILES -------- */
        else if (choice == 6)
        {
            if (!graphLoaded)
            {
                cout << "Please load a graph first"<<endl;
                continue;
            }

            FileIO::writeMST("mst_prim.txt", mstPrim, primWeight);
            FileIO::writeMST("mst_kruskal.txt", mstKruskal, kruskalWeight);

            if (shortestPath.pathExists)
            {
                FileIO::writeShortestPath(
                    "shortest_path.txt",
                    shortestPath.path,
                    shortestPath.totalDistance
                );
            }

            cout << "Results saved to files successfully"<<endl;
        }

        /* -------- OPTION 7: VISUALIZATION (BONUS) -------- */
        else if (choice == 7)
        {
            if (!graphLoaded)
            {
                cout << "Please load a graph first"<<endl;
                continue;
            }

            ofstream dot("graph.dot");
            dot << "graph G {"<<endl;

            for (auto e : graph.getAllEdges())
            {
                dot << graph.getNodeName(get<0>(e))
                    << " -- "
                    << graph.getNodeName(get<1>(e))
                    << " [label=\"" << get<2>(e) << "\"];"<<endl;
            }

            dot << "}\n";
            dot.close();

            system("dot -Tpng graph.dot -o graph.png");
            cout << "Graph image created (graph.png)"<<endl;
        }

        /* -------- OPTION 8: EXIT -------- */
        else if (choice == 8)
        {
            cout << "Thank you. Program ended"<<endl;
            break;
        }

        else
        {
            cout << "Invalid choice"<<endl;
        }
    }

    return 0;
}
