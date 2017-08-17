//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <cstdio>
#include <vector>

// This includes everything you need
#include "Navigator.h"

// There are a few namespaces in the library
using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Mesh;
using namespace Navigator::Math::Trilat;
using namespace Navigator::Accel;
using namespace Navigator::Particles;
using Navigator::Math::Position3D;

/** @brief Example 5: An example of ParticleNavigator usage
 *
 *  ParticleNavigator is an umbrella navigator which requires a Beacon and an Accel navigator,
 *  as well as a RectanMesh (optional). See previous examples on more details on Beacon and Accel.
 *
 * @return
 */
int main() {
    cout << "EXAMPLE 5 \n";

    /* 1) Create an RectMesh object
     * we use shared_ptr as usual for the lifecycle */
    // Some mesh, no walls at present
    constexpr double nx = 201, ny = 201;
    constexpr double dx = 0.1, dy = 0.1;
    constexpr double x0 = -10.0, y0 = -10.0;
    shared_ptr<RectanMesh> rMesh = make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);
    // Create a mask table
    vector<int> mTable(nx*ny);
    // Fill the table with the "identity" operation (all white)
    for (int i = 0; i < nx*ny; i++)
        mTable[i] = i;
    rMesh->setMaskTable(mTable);

    /* 2) Create the KalmanBeaconNavigator with default parameters
     */
    shared_ptr<AbstractBeaconNavigator> bNav = make_shared<KalmanBeaconNavigator>(rMesh);
    // Create 4 beacons and add them to the navigator
    const Beacon beacons[] = {
            Beacon(BeaconUID("Guinea Pig", 1, 0), -30.0, 2.0, Position3D(0.6, 0.2, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 1), -35.0, 2.5, Position3D(9.8, 0.3, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 2), -40.0, 3.0, Position3D(-0.1, 10.4, 0.0), ""),
            Beacon(BeaconUID("Guinea Pig", 1, 3), -45.0, 2.4, Position3D(9.9, 10.1, 0.0), "")
    };
    bNav->addBeacons(beacons);

    for (const Beacon &b: beacons)
        cout << "Beacon = " << b.getUid() << endl;

    /* 3) Create and accel navigator with some starting point,
     * starting point could come from beacon navigation*/
    AccelConfig aConfig;
    aConfig.useFilter = false; // Should be true for real cases
    double startX = 2.31, startY = 6.95; // Start coordinates
    shared_ptr<StandardAccelNavigator> aNav = make_shared<StandardAccelNavigator>(rMesh, startX, startY, aConfig);

    /* 4) Create the particle navigator */
    ParticleNavigator pNav(bNav, aNav, rMesh);

    /* 5) Create and process BLE events
     * only one packet is enough here to get some position for the particle navigator
     * In real life send BLE packets as soon as they come
     */
    {
        Position3D inPos(2.31, 6.95, 0.0); // Some given position
        // Create a vector of packets which share the same timestamp
        vector<BeaconReceivedData> brds;
        double timeStamp = 1.7;
        for (int i = 0; i < 4; i++) {
            const Beacon &b = beacons[i];
            double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp());
            BeaconUID uid = BeaconUID("Guinea Pig", 1, i);
            brds.emplace_back(timeStamp, uid, rssi);
        }
        Position3D outPos = bNav->process(brds);
        printf("BLE position =  %lf  %lf \n", outPos.x, outPos.y);
    }

    /* 6) The first call to pNav, initializes it with the BLE position
     */
    Position3D outPos = pNav.obtainLastPosition();
    printf("PAR position =  %lf  %lf \n", outPos.x, outPos.y);

    /* 7) Now push accelerometer a bit
     */
    for (int i = 0; i < 2; ++i){
        // Uniform acceleration in the -x direction
        AccelReceivedData ard{i*0.1, -1.0, 0.0, -1.0, 0.0, 0.0, 0.0};
        outPos = aNav->process(ard);
        printf("ACC position =  %lf  %lf \n", outPos.x, outPos.y);
    }

    /* 8) Finally, we call pNav again to get a new position
     */
    outPos = pNav.obtainLastPosition();
    printf("PAR position =  %lf  %lf \n", outPos.x, outPos.y);

    return 0;
}
