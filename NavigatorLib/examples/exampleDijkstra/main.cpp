//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#include <iostream>
#include <vector>

#include "Navigator.h"

int main() {
    using namespace std;
    using namespace Navigator::Dijkstra;
    using namespace Navigator::Math;

    //----------------------------------------------------------
    // Fun with class Graph (graph with no vertex coordinates)

    cout << "Let's try Graph ! \n";

    Graph g1({
                     {Edge(1, 3.0), Edge(2, 2.0)},                                // 0
                     {Edge(0, 3.0), Edge(4, 7.0)},                                // 1
                     {Edge(0, 2.0), Edge(3, 2.0), Edge(4, 5.0)},                  // 2
                     {Edge(2, 2.0), Edge(4, 2.0), Edge(5, 4.0)},                  // 3
                     {Edge(1, 7.0), Edge(2, 5.0), Edge(3, 2.0), Edge(5, 6.0)},    // 4
                     {Edge(3, 4.0), Edge(4, 6.0), Edge(6, 9.0)},                  // 5
                     {Edge(5, 9.0)},                                              // 6
                     vector<Edge>()                                               // 7 (unconnected)
             });
    vector<int> path;

    cout << "dist = " << g1.dijkstra(1, 6, path) << endl;

    cout << "path = ";
    for (int i : path)
        cout << i << " ";
    cout << endl;

    //----------------------------------------------------------
    // Fun with class PointGraph (graph with Position3D vertex coordinates)

    cout << "\nLet's try PointGraph ! \n";

    // Edges
    const vector<vector<Edge>> edges = {
            {Edge(1, 3.0), Edge(2, 2.0)},                                // 0
            {Edge(0, 3.0), Edge(4, 7.0)},                                // 1
            {Edge(0, 2.0), Edge(3, 2.0), Edge(4, 5.0)},                  // 2
            {Edge(2, 2.0), Edge(4, 2.0), Edge(5, 4.0)},                  // 3
            {Edge(1, 7.0), Edge(2, 5.0), Edge(3, 2.0), Edge(5, 6.0)},    // 4
            {Edge(3, 4.0), Edge(4, 6.0), Edge(6, 9.0)},                  // 5
            {Edge(5, 9.0)},                                              // 6
            vector<Edge>()                                               // 7 (unconnected)
    };

    // Let's give it some vertices
    const vector<Position3D> vertices = {
            {1.0,  0.0,  0.0}, // 0
            {0.0,  2.0,  0.0}, // 1
            {3.0,  0.0,  0.0}, // 2
            {5.0,  0.0,  0.0}, // 3
            {7.0,  0.0,  0.0}, // 4
            {8.0,  3.0,  0.0}, // 5
            {17.0, 3.0,  0.0}, // 6
            {17.0, 10.0, 0.0} // 7
    };

    PointGraph g2(edges, vertices);

    // A point path
    vector<Position3D> pointPath;

    cout << "dist = " << g2.dijkstraP(1, 6, pointPath) << endl;
    for (const Position3D &p : pointPath)
        cout << p.x << " " << p.y << endl;

    // More things you can do with a PointGraph
    cout << "\nPointGraph additional operations :\n\n";
    // Find a vertex index from coordinates
    cout << "Vertex index from XYZ : g2.findVertex(Position3D(17, 3, 0)) = " << g2.findVertex(Position3D(17, 3, 0))
         << endl;
    cout << "Number of vertices    :  g2.getSize() = " << g2.getSize() << endl;
    cout << "All vertices          :  g2.getVerices() = \n";

    const auto &vert = g2.getVertices();
    for (int i = 0; i < vert.size(); ++i) {
        const auto &v = vert[i];
        cout << i << " : " << v.x << " " << v.y << " " << v.z << "\n";
    }

    cout << "All edges             :  g2.getVerices() = \n";
    const auto &ed = g2.getEdges();
    // Loop over all 'from' vertices
    for (int i = 0; i < edges.size(); ++i) {
        // Loop over all 'to' vertices
        for (const auto &e : ed[i])
            cout << i << " : " << e.to << " " << e.weight << "\n";
    }

    //----------------------------------------------------------
    // Fun with class PointGraph, Reading PointGraph from a disk file

    cout << "\nLet's try PointGraph from file graph.txt ! \n";

    PointGraph g3("graph.txt");
    pointPath.clear();

    cout << "dist = " << g2.dijkstraP(1, 6, pointPath) << endl;
    for (const Position3D &p : pointPath)
        cout << p.x << " " << p.y << endl;

    return 0;
}