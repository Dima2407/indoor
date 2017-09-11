//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

// parttest1 : Test the particle filter (NOT navigator) with simulated random numbers

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <memory>

#include "Navigator.h"

//===================================
// Read 4 input files and set up simulated random numbers
void setUpSimRand(Navigator::Particles::ParticleFilter &pf) {
    using namespace std;
    using namespace Navigator::Particles;
    using namespace Navigator::Math;
    {
        string fileName("filesForTests/firstStageCoords30particles.txt");
        ifstream in(fileName);
        if (!in)
            throw logic_error("Cannot open file " + fileName + " !");

        pf.simRandPI.clear();
        pf.simRandPI.reserve(30);
        double x, y;
        while (in >> x >> y) {
            pf.simRandPI.emplace_back(x, y);
        }
    }
    {
        string fileName("filesForTests/secondStageCoords30particles.txt");
        ifstream in(fileName);
        if (!in)
            throw logic_error("Cannot open file " + fileName + " !");

        pf.simRandPP.clear();
        pf.simRandPP.reserve(30);
        double x, y;
        while (in >> x >> y) {
            pf.simRandPP.emplace_back(x, y);
        }
    }
    {
        string fileName("filesForTests/thirdStageParticleNumber.txt");
        ifstream in(fileName);
        in >> pf.simRandI;
        if (!in)
            throw logic_error("Cannot open file " + fileName + " !");
    }
    {
        string fileName("filesForTests/forthStage30Particles.txt");
        ifstream in(fileName);
        if (!in)
            throw logic_error("Cannot open file " + fileName + " !");

        pf.simRandBeta.clear();
        pf.simRandBeta.reserve(30);
        double x;
        while (in >> x) {
            pf.simRandBeta.push_back(x);
        }
    }

}

//===================================
// Read Z and delta from input files
void readZD(std::vector<Navigator::Math::Position2D> &z, std::vector<Navigator::Math::Position2D> &d) {
    using namespace std;
    using namespace Navigator::Math;

    {
        string fileName("filesForTests/INPUTbeaconsCoords.txt");
        ifstream in(fileName);
        if (!in)
            throw logic_error("Cannot open file " + fileName + " !");
        z.clear();
        z.reserve(100);

        string s;
        char c;
        int n;
        getline(in, s); // Skip line 1
        double x, y;

        while (in >> n >> ws >> c >> x >> y >> c) {
            z.emplace_back(x, y);
        }
    }
    {
        string fileName("filesForTests/INPUTAccelXYIncrement.txt");
        ifstream in(fileName);
        if (!in)
            throw logic_error("Cannot open file " + fileName + " !");
        d.clear();
        d.reserve(100);

        string s;
        char c;
        int n;
        getline(in, s); // Skip line 1
        getline(in, s); // Skip line 2
        d.emplace_back(0, 0);
        double x, y;

        while (in >> n >> ws >> c >> x >> y >> c) {
            d.emplace_back(x, y);
        }
    }
}

//===================================
int main() {
    using namespace std;
    using namespace Navigator::Particles;
    using namespace Navigator::Math;

    cout << "Goblins WON !" << endl;

    ParticleFilterConfig config;
    config.simulatedRandom = true;
    config.numPart = 7; // 7 particles
    ParticleFilter pf(config);
    setUpSimRand(pf);  // Parse input files and set up simulated random numbers

    // Now our lambdas without any map/mesh/mask
    auto meshCorrect = [](const Position2D &p) -> Position2D {
        return p;
    };
    auto allowMove = [](const Position2D &p1, const Position2D &p2) -> bool {
        return true; // Always allowed
    };

    // Z = simulated BLE positions read from a file
    vector<Position2D> beaconZ;
    // Delta = simulated ACC shifts read from a file
    vector<Position2D> accDelta;
    readZD(beaconZ, accDelta);

/*    cout << "beaconZ = " << endl;
    for (int i = 1; i <= beaconZ.size(); ++i)
        cout <<  i << " : " << beaconZ[i-1] << endl;
    cout << "accDelta = " << endl;
    for (int i = 1; i <= accDelta.size(); ++i)
        cout <<  i << " : " << accDelta[i-1] << endl;*/

    ofstream("particles.txt");
    ofstream("position.txt");
    Position2D outPos;
    for (int i = 1; i <= beaconZ.size(); ++i) {
        if (1 == i) {
            // Initialize
            pf.initialize(beaconZ.at(i - 1), meshCorrect);
            outPos = beaconZ.at(i - 1);
        } else {
            // Normal run, Starting with i == 2
            outPos = pf.process(accDelta.at(i - 1), beaconZ.at(i - 1), allowMove, meshCorrect);
        }

//        cout <<  i << " " << outPos << endl;
        // Print particles
        cout << i << "  ";
        for (const Position2D & p : pf.getParticles())
            cout << '[' << p << "]  ";
        cout << endl;
    }


    return 0;
}