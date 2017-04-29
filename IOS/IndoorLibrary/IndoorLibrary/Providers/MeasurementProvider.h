//
//  MeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "IndoorPrefixHeader.pch"
/*!
 * @typedef MeasurementProviderType
 * @brief A list of providers types.
 * @constant GPS_PROVIDER gets coordinates by GPS.
 * @constant SENSOR_PROVIDER  get coordinates by Accelerometer.
 * @constant WIFI_PROVIDER get coordinates by WIFI beacons.
 * @constant BLE_PROVIDER get coordinates by beacons.
 */
typedef NS_ENUM(NSInteger, MeasurementProviderType)
{
    GPS_PROVIDER = 1,
    SENSOR_PROVIDER,
    WIFI_PROVIDER,
    BLE_PROVIDER
};

@interface MeasurementProvider : NSObject

@property (nonatomic, assign) MeasurementProviderType type;
-(void)start;
-(void)stop;

@end
