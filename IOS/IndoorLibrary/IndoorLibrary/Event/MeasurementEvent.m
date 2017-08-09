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
-(instancetype)initWithAccelerometerData:(CMAccelerometerData *)accelerometer andDeviceMotion:(CMDeviceMotion*)motion{
    self = [super init];
    
    
    if (self != nil)
    {
        _timestamp = [[NSDate date] timeIntervalSince1970];
        _accelerometerData = accelerometer;
        _motion = motion;
        _type = SENSOR_VALUE;
    }
    return self;
}
-(instancetype)initWithBeacons:(NSArray<CLBeacon*> *)beacons{
    self = [super init];
    
    if (self != nil)
    {
        _timestamp = [[NSDate date] timeIntervalSince1970];
        _beacons = beacons;
        _type = BLE_VALUE;
    }
    return self;
}
@end
