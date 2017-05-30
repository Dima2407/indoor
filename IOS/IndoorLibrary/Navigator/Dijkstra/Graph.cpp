//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#include <limits>
#include <stdexcept>
#include <set>
#include <cmath>
#include <cstdio>
#include <algorithm>

#include "Navigator/Dijkstra/Graph.h"

namespace Navigator {
    namespace Dijkstra {

        double Graph::dijkstra(int source, int destination, std::vector<int> &path) {
            using namespace std;

            int size = edges.size(); // Graph size

            if (source < 0 || source >= size || destination < 0 || destination >= size)
                throw runtime_error("Index out of bounds in dijkstra.");


//            printf("size = %d\n", size);
            const double INF = numeric_limits<double>::max(); // Our infinity

            // The parent vector
            vector<int> parent(size, -17);

            // The distances vector
            vector<double> distances(size, INF);
            distances[source] = 0.0;

            // The unvisited but activated vertices with distance, set guarantees the lowest dist comes first
            set<pair<double, int> > active;
            active.insert({0.0, source});

            // Clear the path
            path.clear();

            while (active.size()) {
                const auto &curPair = active.begin(); // Current location as pair
                int current = curPair->second; // and as index

//                printf("current = %d\n", current);

                if (current == destination) {
//                    puts("Found !");
                    // We reached the destination = success

                    // Backtrack the path trough parents
                    // From destination to source INCLUSIVE

                    int i = destination;
                    while (true) {
                        path.push_back(i);
                        if (i == source)
                            break;
                        i = parent[i]; // Move to the parent
                        if (-17 == i) {
//                            puts("Cannot find path !");
                            path.clear();
                            break;
                        }
                    }

                    if (!path.empty())
                        reverse(path.begin(), path.end()); // Reverse the order

                    return curPair->first; // Return the distance
                }

                // Loop over neighbors of current : activate them all, check distances
                for (const Edge &e: edges[current]) {
                    int n = e.to; // Neighbor
                    if (n < 0 || n >= size)
                        throw runtime_error("Index out of bounds in dijkstra !");

                    if (n == current)
                        throw runtime_error("Self-linked vertex in dijkstra !");

                    double oldDist = distances[n];
                    double newDist = curPair->first + e.weight;

                    // Check if newDist is shorter, always works if oldDist == INF
                    if (newDist < oldDist) {
                        // We change the distance to e.to
                        active.erase({oldDist, n}); // Erase the old pair, if present
                        distances[n] = newDist;
                        active.insert({newDist, n});

                        parent[n] = current;
                    }
                }

                // Remove current from active
                active.erase(curPair);
            }

            return nan(""); // Failure !
        }
    }
}