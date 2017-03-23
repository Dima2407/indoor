//
//  MeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementEvent.h"
#import "IosMeasurementTransfer.h"

typedef NS_ENUM(NSInteger, MeasurementProviderType)
{
    GPS_PROVIDER = 1,
    SENSOR_PROVIDER,
    WIFI_PROVIDER,
    BLE_PROVIDER
};

@interface MeasurementProvider : NSObject
@property (nonatomic, strong) IosMeasurementTransfer *transfer;
@property (nonatomic, assign) MeasurementProviderType type;
-(void)start;
-(void)stop;

@end
