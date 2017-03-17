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

/** @brief  Calculate a fake RSSI signal for 2 points
 *
 * This is for the example only, of course you don't need this for the real code
 */
double fakeRSSI(const Position3D &p1, const Position3D &p2, double txPower, double damp)
{
    /*double dist = p1.distance(p2);
    double temp = log10(dist);
    return txPower - 10 * damp * temp;*/
    return txPower - 10 * damp * log10( p1.distance(p2) );
}


/** @brief An example of Navigator usage with beacons
 *
 * @return
 */
int main()
{
    // 1) Filter factories:
    // We have to choose filters  for rssi and distances
    // Options:
    // No filtering:
    //      make_shared<NoFilterFactory>()
    // Running average filter with window size:
    //      make_shared<MovingAverageFilterFactory>(winSize)
    // Alpha-beta filter:
    //      make_shared<AlphaBetaFilterFactory>(alpha, beta)


    auto rssiFact = make_shared<MovingAverageFilterFactory>(5);
    // auto rssiFact = make_shared<AlphaBetaFilterFactory>(0.3, 0.3);
    // auto rssiFact = make_shared<NoFilterFactory>();

    auto distFact = make_shared<NoFilterFactory>();

    /* 2) Create the Beacon Navigator
     Here it is a local variable,
     Of course you can use it as a class field or shared_ptr or anything
     You always supply shared_ptr's to the two factories to the  TrilatBeaconNavigator constructor
     */
    TrilatBeaconNavigator navigator(rssiFact, distFact);

    /* Create 3 beacons
     * I used array of beacons in the example
     * In real life beacon data is obtained from a server or a map file
     *
     * Beacon: constructor
     * Beacon(uid, txpower, damp, xyz, "")
     *
     * uid can be created in several ways:
     * BeaconUID(std::string s, int major, int minor) // Preferred
     * BeaconUID(std::string s)
     * BeaconUID(long long hash)
     *
     * The only important thing is that data for each beacon must be unique(no repetitions),
     * and you later use EXACTLY the same UID construction in your events (data packets)
     *
     * In my example, only minor field is different
     */
    Beacon beacons[] = {
            Beacon(BeaconUID("Guinea Pig", 1, 0), -3.0, 2.0, Position3D(0.3, 0.5, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 1), -4.0, 2.5, Position3D(9.7, 0.4, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 2), -2.0, 3.0, Position3D(-0.2, 10.6, 0.0), "")
    };

    /* Add beacons: to the navigator
     *
     * You can add them one by one, or as an array/container
     * /
     *
    /*for (const Beacon &b : beacons)
        navigator.addBeacon(b);*/
    navigator.addBeacons(beacons);

    /* 3) Create and process events
     * For the example, I generate fake events for a point inPos
     * In real life, you receive events (timestamp, beacon uid, rssi) from you device
     * And send them to the navigator
     */
    Position3D inPos(0.75, 0.38, 0.0); // Some given position
    
    cout << "  x  \t  y  \t  z  " << endl;
    for (int i = 0; i < 3; i++) {

        /* The tamestamp is double in seconds
         * If your device use millisecond timestamp t, write something like
         * double timeStamp = 1.0*(t-t0)/1000;
         * Where t0 is the first millisecond timestamp
         * Subtracting it increases the accuracy of the mS -> S conversion
         *
         */
        double timeStamp = 0.1*i;

        /* For the example, I create a fake RSSI for each beacon
         * In real life you get rssi from your mobile device
         */
        const Beacon & b = beacons[i];
        double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp() );

        /* Create UID for the data packet
         * It must correctly identify one of the beacons addded to the navigator before
         */
        BeaconUID uid = BeaconUID("Guinea Pig", 1, i);

        // Create a data packet for our data
        BeaconReceivedData brd(timeStamp, uid , rssi);

        // Process it and get a position
        Position3D outPos = navigator.process(brd);

        // Write it to stdout
        cout << outPos.x << "\t" << outPos.y << "\t" << outPos.z << endl;
    }

    return 0;
}