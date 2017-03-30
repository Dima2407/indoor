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

-(instancetype)initWithLatitude:(CGFloat)latitude andLongitude:(CGFloat)longitude {
    
    self = [super init];
   
    
    if (self != nil)
    {
       
   
    _timestamp = [[NSDate date] timeIntervalSince1970];
    _type = GEO_VALUE;
    _latitude = latitude;
    _longitude = longitude;
        
    }
    return self;
        
}

-(instancetype)initWithBeacon:(CLBeacon *)beacon{
    self = [super init];
    
    
    if (self != nil)
    {
    _timestamp = [[NSDate date] timeIntervalSince1970];
    _beacon = beacon;
    _type = BLE_VALUE;
    }
    return self;
}
@end
