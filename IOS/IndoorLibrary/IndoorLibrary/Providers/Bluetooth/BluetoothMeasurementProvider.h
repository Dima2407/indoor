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


-(void)setUuid:(NSString*)uuid;
-(instancetype)init: (IosMeasurementTransfer*) transfer;

@end
