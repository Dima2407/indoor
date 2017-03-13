//
//  BluetoothMeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementProvider.h"
#import <CoreLocation/CoreLocation.h>

@interface BluetoothMeasurementProvider : MeasurementProvider<CLLocationManagerDelegate>


@property (nonatomic, strong)  NSString *UUID;
@property (nonatomic, assign) CGFloat txPower;
@property (nonatomic, assign) NSInteger major;
@property (nonatomic, assign) NSInteger minor;
@property (nonatomic, assign) CGFloat damp;
@property (nonatomic, strong) NSArray *beacons;
@end
