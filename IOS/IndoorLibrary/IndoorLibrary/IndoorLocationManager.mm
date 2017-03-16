//
//  IndoorLocationManager.m
//  IndoorLibrary
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "IndoorLocationManager.h"
#import "MeasurementProvider.h"
#import "BluetoothMeasurementProvider.h"
#import "Navigator.h"
#include <iostream>
#include <cmath>
#include <vector>
//#import "MovingAverageFilter.h"
//#import "NoFilter.h"
#import "Beacon.h"


@interface IndoorLocationManager()<IosMeasurementTransferDelegate>
@end


@implementation IndoorLocationManager
- (instancetype)init
{
    self = [super init];
    if (self)
    {
        _transfer.delegate = self;
    }
    return self;
}

-(void) prepare {
    
    self.transfer = [[IosMeasurementTransfer alloc] init];
    double fakeRSSI(const Navigator::Math::Position3D &p1, const Navigator::Math::Position3D &p2, double txPower, double damp);
//    {
//        /*double dist = p1.distance(p2);
//         double temp = log10(dist);
//         return txPower - 10 * damp * temp;*/
//        return txPower - 10 * damp * log10( p1.distance(p2) );
//    }
//    
    // Filter factories
    auto rssiFact = std::make_shared<Navigator::Beacons::Factory::MovingAverageFilterFactory>(5);
    auto distFact = std::make_shared<Navigator::Beacons::Factory::NoFilterFactory>();
    
    // Create the Beacon Navigator
    Navigator::Beacons::TrilatBeaconNavigator navigator(rssiFact, distFact);
    
    // Create 3 beacons
    Navigator::Beacons::Beacon beacons[] = {
        Navigator::Beacons::Beacon(Navigator::Beacons::BeaconUID("Guinea Pig", 1, 0), -3.0, 2.0, Navigator::Math::Position3D(0.3, 0.5, 0.0), ""),
        Navigator::Beacons::Beacon(Navigator::Beacons::BeaconUID("Guinea Pig", 1, 1), -4.0, 2.5, Navigator::Math::Position3D(9.7, 0.4, 0.0), ""),
        Navigator::Beacons::Beacon(Navigator::Beacons::BeaconUID("Guinea Pig", 1, 2), -2.0, 3.0, Navigator::Math::Position3D(-0.2, 10.6, 0.0), "")
    };
    
    
    navigator.addBeacons(beacons);
    
    // Create and process 3 events
    Navigator::Math::Position3D inPos(0.75, 0.38, 0.0); // Some given position
    
       for (int i = 0; i < 3; i++) {
        double time = 0.1*i;
        
        const Navigator::Beacons::Beacon & b = beacons[i];
        
        // Create a data packet
       Navigator::Beacons::BeaconReceivedData brd(time, b.getUid(), fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp() ));
        
      
    Navigator::Math::Position3D outPos = navigator.process(brd);
           NSLog(@"-----Position X:%f, Y:%F, Z:%f----",outPos.x, outPos.y, outPos.z);
        
       }
    }
    
    -(void)addProvider:(MeasurementType)type{
    MeasurementProvider * provider = nil;
    switch (type) {
        case BLE_VALUE:
            provider = [[BluetoothMeasurementProvider alloc] init: self.transfer];
            break;
        default:
            break;
    }
    if(provider != nil){
        [self.providers addObject:provider];
    }
}

-(void) start{
    [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
        [obj start];
    }];
}

-(void) stop{
    [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
        [obj stop];
    }];
}



-(void)removeProvider: (MeasurementType) type{
    
}
-(void)process: (MeasurementEvent *) event{
    [self _processEvent:event];
}
-(void)_processEvent: (MeasurementEvent *) event{
    switch (event.type) {
        case BLE_VALUE:
            
//            BeaconID = BeaconUID(data[1], data[2], data[3])
//           BeaconReceivedData brd(event.time, beaconID, event.data[0]);
//            outPos = navigator.process(brd);
//            [sefl.locationUpdateDelegate locationUpdate outPos];
            
            
//            // Create 3 beacons
//            Beacon beacons[] = {
//                Beacon(BeaconUID("Guinea Pig", 1, 0), -3.0, 2.0, Position3D(0.3, 0.5, 0.0), ""),
//                Beacon(BeaconUID("Guinea Pig", 1, 1), -4.0, 2.5, Position3D(9.7, 0.4, 0.0), ""),
//                Beacon(BeaconUID("Guinea Pig", 1, 2), -2.0, 3.0, Position3D(-0.2, 10.6, 0.0), "")
//            };
//            
//            // Add them to the navigator
//            /*for (const Beacon &b : beacons)
//             navigator.addBeacon(b);*/
//            navigator.addBeacons(beacons);
//            
//            // Create and process 3 events
//            Position3D inPos(0.75, 0.38, 0.0); // Some given position
//            
//  
//            for (int i = 0; i < 3; i++) {
//                double time = 0.1*i;
//                
//                const Beacon & b = beacons[i];
//                
//                // Create a data packet
//                BeaconReceivedData brd(time, b.getUid(), fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp() ));
//                
//                // Process it
//                Position3D outPos = navigator.process(brd);
//                
//            NSLog(@"%@",outPos);
//
            
            
            
            
            break;
            
        default:
            break;
    }
}

@end
