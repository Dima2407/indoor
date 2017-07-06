//
//  SensorMeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementProvider.h"

@interface SensorMeasurementProvider : MeasurementProvider

-(instancetype)initWithTransfer: (IosMeasurementTransfer*) sensorTransfer;
@end
