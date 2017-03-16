//
//  BluethoothProviderConfiguration.m
//  IndoorLibrary
//
//  Created by AppleFace on 13.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "BluethoothProviderConfiguration.h"
#import "BluetoothMeasurementProvider.h"

@interface BluethoothProviderConfiguration()<ProviderConfiguration>



@end

@implementation BluethoothProviderConfiguration

+(void)updateCinfiguration:(NSArray<TConfig> *)inputArray{
    
    [BluetoothMeasurementProvider setBeaconMap:inputArray];
}
@end
