//
//  MeasurementEvent.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, MeasurementType)
{
    GEO_VALUE = 1,
    SENSOR_VALUE,
    WIFI_VALUE,
    BLE_VALUE
};

@interface MeasurementEvent : NSObject
@property (nonatomic, assign) NSInteger timestamp;
@property (nonatomic, assign) MeasurementType type;
@property (nonatomic, strong) NSArray *values;
@property (nonatomic, assign) CGFloat latitude;
@property (nonatomic, assign) CGFloat longitude;
@property (nonatomic, assign) NSInteger RSSI;
@property (nonatomic, assign) NSUInteger UUID;

-(instancetype)initWithLatitude:(CGFloat)latitude andLatitude:(CGFloat)longitude;
-(instancetype)initWithRssi:(CGFloat)rssi andUUID:(NSUInteger)uuid;
@end
