//
//  MeasurementEvent.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "MeasurementEvent.h"
#import "MeasurementProvider.h"


@interface MeasurementEvent()



@end

@implementation MeasurementEvent

-(instancetype)initWithLatitude:(CGFloat)latitude andLatitude:(CGFloat)longitude {
    
    self = [super init];
   
    
    if (self != nil)
    {
       
   
    _timestamp = [[NSDate date] timeIntervalSince1970]*1000;
    _type = GEO_VALUE;
    _latitude = latitude;
    _longitude = longitude;
        
    }
    return self;
        
}

-(instancetype)initWithRssi:(CGFloat)rssi andUUID:(NSUInteger)uuid{
    self = [super init];
    
    
    if (self != nil)
    {
    _timestamp = [[NSDate date] timeIntervalSince1970]*1000;
    _UUID = uuid;
    _RSSI = rssi;
    _type = BLE_VALUE;
    }
    return self;
}
@end
