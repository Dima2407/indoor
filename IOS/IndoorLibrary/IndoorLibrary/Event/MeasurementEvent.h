//
//  MeasurementEvent.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CLBeaconRegion.h>
#import <CoreMotion/CoreMotion.h>

typedef NS_ENUM(NSInteger, MeasurementType)
{
    GEO_VALUE = 1,
    SENSOR_VALUE,
    WIFI_VALUE,
    BLE_VALUE
};

@interface MeasurementEvent : NSObject
@property (nonatomic, assign) CGFloat timestamp;
@property (nonatomic, assign) MeasurementType type;
@property (nonatomic, strong) NSArray *values;
@property (nonatomic, assign) CGFloat latitude;
@property (nonatomic, assign) CGFloat longitude;
@property (nonatomic, strong) CLBeacon *beacon;
@property (nonatomic, assign) CGFloat txPower;
@property (nonatomic, assign) CMAccelerometerData  *accelerometerData;
@property (nonatomic, assign) CMDeviceMotion *motion;

-(instancetype)initWithLatitude:(CGFloat)latitude andLongitude:(CGFloat)longitude;
-(instancetype)initWithBeacon:(CLBeacon *)beacon;
-(instancetype)initWithAccelerometerData:(CMAccelerometerData *)accelerometer andDeviceMotion:(CMDeviceMotion*)motion;
@end
