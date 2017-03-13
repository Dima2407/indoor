//
//  GPSMeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementProvider.h"
#import <CoreLocation/CoreLocation.h>


@interface GPSMeasurementProvider : MeasurementProvider<CLLocationManagerDelegate>
@property (nonatomic, strong) CLLocationManager *manager;
@property (nonatomic, strong) MeasurementEvent *event;
@property (nonatomic, assign) NSInteger latitude;
@property (nonatomic, assign) NSInteger longitude;
@end
