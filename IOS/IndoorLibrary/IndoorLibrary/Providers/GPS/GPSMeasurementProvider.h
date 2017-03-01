//
//  GPSMeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementProvider.h"
#import <CoreLocation/CLLocationManager.h>

@interface GPSMeasurementProvider : MeasurementProvider<CLLocationManagerDelegate>

@end
