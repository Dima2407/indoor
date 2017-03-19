//
//  BluetoothBridge.h
//  IndoorLibrary
//
//  Created by AppleFace on 19.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#ifndef BluetoothBridge_H
#define BluetoothBridge_H

#include <stdio.h>
#import "Navigator.h"
#import "Beacon.h"
#import "BeaconUID.h"

#endif /* BluetoothBridge_hpp */


//первая инициализация
#ifdef __cplusplus
extern "C"
#endif
 Navigator::Beacons::TrilatBeaconNavigator* BluetoothBridge_init();

////начало добавления кординат биконов
//#ifdef __cplusplus
//extern "C"
//#endif
//void  BluetoothBridge_setBeacon(Navigator::Beacons::Beacon beacon);

//init биконa
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z);



