//
//  MeasurementTransfer.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "MeasurementTransfer.h"

    

@implementation MeasurementTransfer

+(void)deliver:(MeasurementEvent*)event
{
    NSInteger eventType = event.type;
    switch (eventType) {
        case GEO_VALUE:
            NSLog(@"GEO_VALUE");
            NSLog(@"Latitude :%f, Longitude: %f",event.latitude, event.longitude);
            break;
        case BLE_VALUE:
            NSLog(@"BLE_VALUE");
            NSLog(@"UUID:%zd, RSSI: %ld",event.UUID, (long)event.RSSI);
            
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
