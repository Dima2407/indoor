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

const std::string  prefix("filesForTests2/");

//===================================
// Read 4 input files and set up simulated random numbers
void setUpSimRand(Navigator::Particles::ParticleFilter &pf) {
    using namespace std;
    using namespace Navigator::Particles;
    using namespace Navigator::Math;
    {
        string fileName(prefix + "firstStageCoords30particles.txt");
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
        string fileName(prefix + "secondStageCoords30particles.txt");
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
        string fileName(prefix + "thirdStageParticleNumber.txt");
        ifstream in(fileName);
        in >> pf.simRandI;
        if (!in)
            throw logic_error("Cannot open file " + fileName + " !");
    }
    {
        string fileName(prefix + "forthStage30Particles.txt");
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
        string fileName(prefix + "INPUTbeaconsCoords.txt");
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
        string fileName(prefix + "INPUTAccelXYIncrement.txt");
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

    ofstream filePar("particles.txt");
    ofstream filePar0("particles0.txt");
    ofstream filePos("position.txt");
    ofstream fileBe("betas.txt");
    ofstream fileWe("weights.txt");
    ofstream fileMaxWe("maxweight.txt");
    ofstream fileCho("chosen.txt");

    Position2D outPos;
    for (int i = 1; i <= beaconZ.size(); ++i) {
        if (1 == i) {
            // Initialize
            pf.initialize(beaconZ.at(i - 1), meshCorrect);
            outPos = beaconZ.at(i - 1);
            {
                // Calculate all the possible particle positions at time 2 (second input pos)
                // This are the position before resampling
                ofstream fileP2("part2.txt");
                for (int p = 0; p < pf.getParticles().size(); ++p)
                    fileP2 << pf.getParticles().at(p) + pf.simRandPP.at(p) << endl;
            }
        } else {
            // Normal run, Starting with i == 2
            outPos = pf.process(accDelta.at(i - 1), beaconZ.at(i - 1), allowMove, meshCorrect);
        }

        filePos << i << " " << outPos << endl;

        // Print particles
        filePar << i << "  ";
        for (const Position2D & p : pf.getParticles())
            filePar << '[' << p << "]  ";
        filePar << endl;

        // Print particles0 (before resampling)
        filePar0 << i << "  ";
        for (const Position2D & p : pf.getTmpParticles())
            filePar0 << '[' << p << "]  ";
        filePar0 << endl;

        // Print weights
        fileWe << i << "    ";
        for (double d : pf.getWeights())
            fileWe <<  d << "  ";
        fileWe << endl;

        // Print betas
        fileBe << i << "    ";
        for (double d : pf.getBetas())
            fileBe <<  d << "  ";
        fileBe << endl;

        // Prints chosen (particle numbers chosen at resample, start with 1)
        fileCho << i << "    ";
        for (int  i: pf.getChosen())
            fileCho <<  i << "  ";
        fileCho << endl;


        // Print max weights
        fileMaxWe << i << "  " << pf.getMaxWeight() << endl;
    }


    return 0;
}