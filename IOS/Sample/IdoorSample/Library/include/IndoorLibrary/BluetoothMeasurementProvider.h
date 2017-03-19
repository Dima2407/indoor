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
#import "MeasurementTranfer.h"

@interface BluetoothMeasurementProvider : MeasurementProvider<CLLocationManagerDelegate>

@property (nonatomic, strong) CLLocationManager *manager;
@property (nonatomic, strong) MeasurementEvent *event;
@property (nonatomic, strong) IosMeasurementTransfer *transfer;

-(instancetype)init: (IosMeasurementTransfer*) transfer;
-(void) setBeaconMap:(NSArray*)beaconConfigs;

@end
