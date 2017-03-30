//
//  BluetoothMeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "PrefixHeader.pch"


@interface BluetoothMeasurementProvider : MeasurementProvider<CLLocationManagerDelegate>



-(instancetype)initWithTransfer: (IosMeasurementTransfer*) bleTransfer;

@end
