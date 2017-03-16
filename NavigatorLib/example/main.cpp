//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>

#include "Navigator.h"

using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Factory;
using namespace Navigator::Math::Trilat;
using Navigator::Math::Position3D;
//using Navigator::Math::Trilat::fakeRSSI;

/// Calculate a fake RSSI signal for 2 points
double fakeRSSI(const Position3D &p1, const Position3D &p2, double txPower, double damp)
{
    /*double dist = p1.distance(p2);
    double temp = log10(dist);
    return txPower - 10 * damp * temp;*/
    return txPower - 10 * damp * log10( p1.distance(p2) );
}


///\toDO Short description
int main()
{
    // Filter factories
    auto rssiFact = make_shared<MovingAverageFilterFactory>(5);
    auto distFact = make_shared<NoFilterFactory>();

    // Create the Beacon Navigator
    TrilatBeaconNavigator navigator(rssiFact, distFact);

    // Create 3 beacons
    Beacon beacons[] = {
            Beacon(BeaconUID("Guinea Pig", 1, 0), -3.0, 2.0, Position3D(0.3, 0.5, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 1), -4.0, 2.5, Position3D(9.7, 0.4, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 2), -2.0, 3.0, Position3D(-0.2, 10.6, 0.0), "")
    };

    // Add them to the navigator
    /*for (const Beacon &b : beacons)
        navigator.addBeacon(b);*/
    navigator.addBeacons(beacons);

    // Create and process 3 events
    Position3D inPos(0.75, 0.38, 0.0); // Some given position
    
    cout << "  x  \t  y  \t  z  " << endl;
    for (int i = 0; i < 3; i++) {
        double time = 0.1*i;

        const Beacon & b = beacons[i];

        // Create a data packet
        BeaconReceivedData brd(time, b.getUid(), fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp() ));

        // Process it
        Position3D outPos = navigator.process(brd);

        // Write to stdout
        cout << outPos.x << "\t" << outPos.y << "\t" << outPos.z << endl;
    }

    return 0;
}