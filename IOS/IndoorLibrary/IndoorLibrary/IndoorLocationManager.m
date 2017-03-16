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
#import "library/include/Navigator.h"
#import "library/include/Navigator/Math/Filter/MovingAverageFilter.h"
#import "library/include/Navigator/Math/Filter/NoFilter.h"
#ifdef __cplusplus
#include <library/include/Navigator.h>
#endif

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
#ifdef __cplusplus
    auto rssiFact = make_shared<MovingAverageFilterFactory>(5);
    auto distFact = make_shared<NoFilterFactory>();
    
    
    TrilatBeaconNavigator navigator(rssiFact, distFact);
#endif
    
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
            
            BeaconID = BeaconUID(data[1], data[2], data[3])
            BeaconReceivedData brd(event.time, beaconID, event.data[0]);
            outPos = navigator.process(brd);
            [sefl.locationUpdateDelegate locationUpdate outPos];
            break;
            
        default:
            break;
    }
}

@end
