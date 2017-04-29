//
//  GPSMeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "IndoorPrefixHeader.pch"
#import <CoreLocation/CoreLocation.h>


@interface GPSMeasurementProvider : MeasurementProvider<CLLocationManagerDelegate>

-(instancetype)initWithTransfer: (IosMeasurementTransfer*) gpsTransfer;

@end
