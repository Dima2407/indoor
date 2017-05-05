//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#include <iostream>
#include <vector>

#include "Navigator.h"

int main(){
    using namespace std;
    using namespace Navigator::Dijkstra;

    Graph g1({
                     {Edge(1, 3.0), Edge(2, 2.0)},                                // 0
                     {Edge(0, 3.0), Edge(4, 7.0)},                                // 1
                     {Edge(0, 2.0), Edge(3, 2.0), Edge(4, 5.0)},                  // 2
                     {Edge(2, 2.0), Edge(4, 2.0), Edge(5, 4.0)},                  // 3
                     {Edge(1, 7.0), Edge(2, 5.0), Edge(3, 2.0), Edge(5, 6.0)},    // 4
                     {Edge(3, 4.0), Edge(4, 6.0), Edge(6, 9.0)},                  // 5
                     {Edge(5, 9.0)}                                               // 6
                     });
    vector<int> path;

    cout << "dist = " << g1.dijkstra(4, 0, path) << endl;

    return 0;
}