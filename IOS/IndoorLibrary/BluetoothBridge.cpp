//
//  BluetoothBridge.cpp
//  IndoorLibrary
//
//  Created by AppleFace on 19.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#include "BluetoothBridge.h"
#include "stdio.h"

Navigator::Beacons::TrilatBeaconNavigator* navigator;

extern "C"
 Navigator::Beacons::TrilatBeaconNavigator* BluetoothBridge_init() {
    auto rssiFact = std::make_shared<Navigator::Beacons::Factory::MovingAverageFilterFactory>(5);
    auto distFact = std::make_shared<Navigator::Beacons::Factory::NoFilterFactory>();
     navigator = new Navigator::Beacons::TrilatBeaconNavigator (rssiFact, distFact);
    return navigator;
    
}

extern "C"
void BluetoothBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z){
    Navigator::Beacons::Beacon beacon(Navigator::Beacons::BeaconUID(uuidstr,major,minor), txPower, damp, Navigator::Math::Position3D(x,y,z), "");
   // navigator->addBeacon();
    
}
//extern "C"
//void BluetoothBridge_setBeacon(Navigator::Beacons::Beacon beacon) {
//    navigator.addBeacon(beacon);
//}

//extern "C"


