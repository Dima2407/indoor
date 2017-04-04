//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>


// This includes everything you need
#include "Navigator.h"

// There are a few namespaces in the librrary
using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Factory;
using namespace Navigator::Math::Trilat;
using Navigator::Math::Position3D;

/** @brief Example 2: An example of Navigator usage with beacons
 *
 *  This is newer that example 1 and demonstrates using navigator.process(vector)
 *  and the configuration parameters of the navigator
 *
 * @return
 */
int main() {
    cout << "EXAMPLE 2 \n";


    // 1) Filter factories:
    // We have to choose filters  for rssi and distances
    // Options:
    // No filtering:
    //      make_shared<NoFilterFactory>()
    // Running average filter with window size:
    //      make_shared<MovingAverageFilterFactory>(winSize)
    // Alpha-beta filter:
    //      make_shared<AlphaBetaFilterFactory>(alpha, beta)


    const auto rssiFact = make_shared<MovingAverageFilterFactory>(3);
    // auto rssiFact = make_shared<AlphaBetaFilterFactory>(0.3, 0.3);
    // auto rssiFact = make_shared<NoFilterFactory>();

    const auto distFact = make_shared<NoFilterFactory>();

    /* 2) Create the Beacon Navigator
     Here it is a local variable,
     Of course you can use it as a class field or shared_ptr or anything
     You always supply shared_ptr's to the two factories to the  TrilatBeaconNavigator constructor
     */
    TrilatBeaconNavigator navigator(rssiFact, distFact);

    // Configure the navigator

    // Beacon timeout in seconds (default = 10)
    // After that time idle the beacon's filters are reset
    navigator.setBeaconTimeout(1.5);

    // Do we use full 3D trilat instead of 2D ? (default = false)
    navigator.setUse3DTrilat(false);

    // Max number of nearest beacons to use on each trilateration
    // 0 = unlimited, default = 0
    navigator.setUseNearest(3);

    /* Create 4 beacons
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
    const Beacon beacons[] = {
            Beacon(BeaconUID("Guinea Pig", 1, 0), -30.0, 2.0, Position3D(0.6, 0.2, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 1), -35.0, 2.5, Position3D(9.8, 0.3, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 2), -40.0, 3.0, Position3D(-0.1, 10.4, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 3), -45.0, 2.4, Position3D(9.9, 10.1, 0.0), "")
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
    Position3D inPos(2.31, 6.95, 0.0); // Some given position


    // Create a vector of packets which share the same timestamp
    vector<BeaconReceivedData> brds;


    /* The timestamp is double in seconds
     * If your device use millisecond timestamp t, write something like
     * double timeStamp = 1.0*(t-t0)/1000;
     * Where t0 is the first millisecond timestamp
     * Subtracting it increases the accuracy of the mS -> S conversion
     *
     * Here all packets share the same timestamp (in contrast to example 1)
     *
     * Packets with different timestamp must not be bundled together like this !
     *
     * How it works:
     * after each process() the lastPosition is updated
     * you should run process(), either 1-value or vector version
     * each time you get new data from your device
     * And use the vector version if you have a number of packets sharing a timestamp
     * The small error like 0.001 in timestamp is no problem
     *
     * In fact, the vector version of process() sets the same timestamp (the one of
     * the first elements) to all packets
     */
    double timeStamp = 1.7;

    for (int i = 0; i < 4; i++) {

        /* For the example, I create a fake RSSI for each beacon
         * In real life you get rssi from your mobile device
         */
        const Beacon &b = beacons[i];
        double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp());

        /* Create UID for the data packet
         * It must correctly identify one of the beacons addded to the navigator before
         */
        BeaconUID uid = BeaconUID("Guinea Pig", 1, i);

        // Create a data packet for our data
        brds.push_back(BeaconReceivedData(timeStamp, uid, rssi));
    }

    // Process the whole bunch of data in a single process() call
    // This should be ONLY used if all packets (approximately) share the same timestamp !
    // This way trilateration is called only once and there is (usually) no nans
    navigator.process(brds);

    // You can also process and get position like this
    // Position3D outPos = navigator.process(brds);

    // Get the current position
    Position3D outPos = navigator.getLastPosition();

    // Write it to stdout
    cout << "  x  \t  y  \t  z  " << endl;

    cout << outPos.x << "\t" << outPos.y << "\t" << outPos.z << endl;


    // Try findProcessorByUid
    auto processor = navigator.findProcessorByUid(BeaconUID("Guinea Pig", 1, 2));
    if (processor == nullptr) {
        cout << "Beacon Processor not found !!! " << endl;
    } else {
        cout << "Last distance = " << processor -> getLastDistance() << endl;
        cout << "Last timestamp = " << processor -> getLastTimeStamp() << endl;
    }


    // If you want to remove a beacon
    // navigator.deleteBeacon(BeaconUID("Guinea Pig", 1, 2));

    // Or remove all beacons
    // navigator.clear();

    return 0;
}