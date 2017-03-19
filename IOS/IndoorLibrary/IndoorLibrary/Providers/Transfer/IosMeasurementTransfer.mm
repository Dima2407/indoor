//
//  MeasurementTransfer.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "IosMeasurementTransfer.h"
#import "Navigator.h"
#import "Beacon.h"
#import "BeaconUID.h"


@implementation IosMeasurementTransfer
- (instancetype)init
{
    self = [super init];
    if (self)
    {
        
    }
    return self;
}

-(void)deliver:(MeasurementEvent*)event
{
    if(event.type == BLE_VALUE){
        if([self.delegate respondsToSelector:@selector(processEvent:)]) {
            [self.delegate processEvent:event];
        }
        
       

    }
    NSInteger eventType = event.type;
    switch (eventType) {
        case GEO_VALUE:
            NSLog(@"GEO_VALUE");
            NSLog(@"Latitude :%f, Longitude: %f",event.latitude, event.longitude);
            break;
        case BLE_VALUE:
            NSLog(@"BLE_VALUE");
           // NSLog(@"UUID:%zd, RSSI: %ld",ev, event.beacon.rssi);
            
            break;
        case WIFI_VALUE:
            NSLog(@"WIFI_VALUE");
            
            break;
        case SENSOR_VALUE:
            
            NSLog(@"SENSOR_VALUE");
            
            break;
            
        default:
            break;
            
    }
}

@end
