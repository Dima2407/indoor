//
//  BluetoothBridge.cpp
//  IndoorLibrary
//
//  Created by AppleFace on 19.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#include <memory>

#include "BluetoothBridge.h"


std::shared_ptr<Navigator::Beacons::TrilatBeaconNavigator> navigator;


extern "C"
void BluetoothBridge_init() {
    auto rssiFact = std::make_shared<Navigator::Beacons::Factory::MovingAverageFilterFactory>(5);
    auto distFact = std::make_shared<Navigator::Beacons::Factory::NoFilterFactory>();
     navigator = std::make_shared<Navigator::Beacons::TrilatBeaconNavigator> (rssiFact, distFact);

    
}

extern "C"
void BluetoothBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z){
    Navigator::Beacons::Beacon beacon(Navigator::Beacons::BeaconUID(uuidstr,major,minor), txPower, damp, Navigator::Math::Position3D(x,y,z), "");
    
   navigator->addBeacon(beacon);
    
}
extern "C"
void BluetoothBridge_setPosition(){
Navigator::Math::Position3D inPos(0.75, 0.38, 0.0);
}
extern "C"
void BluetoothBridge_proces(double timestamp, std::string uuidStr, int major, int minor, double rssi) {
    Navigator::Beacons::BeaconUID uuid(uuidStr,major,minor);
    Navigator::Beacons::BeaconReceivedData brd(timestamp, uuid, rssi);
    
    // Process it
    navigator->process(brd);
  
    
}
extern "C"
void BluetoothBridge_getLastPosition(double * output){
Navigator::Math::Position3D outPos = navigator->getLastPosition();
    output[0] = outPos.x;
    output[1] = outPos.y;
    output[2] = outPos.z;
}
//extern "C"

