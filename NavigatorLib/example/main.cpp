//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>

#include "Navigator.h"

using namespace std;
using namespace Navi::Beacons;
using namespace Navi::Beacons::Factory;
using Navi::Math::Position3D;

/// Calculate a fake RSSI signal for 2 points
double fakeRSSI(const Position3D &p1, const Position3D &p2, double txPower, double damp)
{
	// Гипотенуза
    double dist = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    double temp = log10(dist);

    return txPower - 10 * damp * temp;
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
    for (const Beacon &b : beacons)
        navigator.addBeacon(b);

    // Create and process 3 events
    Position3D inPos(0.75, 0.38, 0.0); // Some given position
    Position3D outPos;

    for (int i = 0; i < 3; i++) {
        double time = 0.1*i;

        const Beacon & b = beacons[i];

        // Create a data packet
        BeaconReceivedData brd(time, b.getUid(), fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp() ));

        // Process it
        outPos = navigator.process(brd);

        // Write to stdout
        cout << outPos.x << "  " << outPos.y << "  " << outPos.z << endl;
    }

    return 0;
}