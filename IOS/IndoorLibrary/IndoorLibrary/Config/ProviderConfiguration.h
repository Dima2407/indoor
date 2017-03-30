//
//  ProviderConfiguration.h
//  IndoorLibrary
//
//  Created by AppleFace on 13.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TConfig.h"
#import "MeasurementProvider.h"


@protocol ProviderConfiguration

-(void)updateCinfiguration:(NSArray<TConfig> *)inputArray withBLEProvider:(MeasurementProvider *)provider;



@end
