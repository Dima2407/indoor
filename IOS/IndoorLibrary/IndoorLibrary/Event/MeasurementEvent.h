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

-(instancetype)initWithTime:(NSInteger)time withMeasurementType:(MeasurementType)type andWithCordinate: (NSArray*)coordinates;

@end
