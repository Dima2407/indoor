//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

// parttest1 : Test the particle filter (NOT navigator) with simulated random numbers

#include <iostream>
#include <cmath>
#include <cstdio>
#include <memory>

#include "Navigator.h"

int main(){
    using namespace std;
    using namespace Navigator::Particles;
    using namespace Navigator::Math;

    cout << "Goblins WON !" << endl;

    ParticleFilterConfig config;
    config.simulatedRandom = true;
    ParticleFilter pf(config);

    // Now our lambdas without any map/mesh/mask
    auto meshCorrect = [](const Position2D &p) -> Position2D{
        return p;
    };
    auto allowMove = [](const Position2D &p1, const Position2D &p2) -> bool {
            return true; // Always allowed
    };

    Position2D initPos(0.0, 0.0);  // Read from file ?

    // Set some random numbers
    // pf.simRandP = ..;
    pf.initialize(initPos, meshCorrect);

    return 0;
}