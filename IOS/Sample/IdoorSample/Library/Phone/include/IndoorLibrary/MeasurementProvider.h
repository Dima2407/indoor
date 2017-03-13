//
//  MeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementEvent.h"
#import "MeasurementTransfer.h"

@interface MeasurementProvider : NSObject
@property (nonatomic, strong) MeasurementTransfer *transfer;

-(void)start;
-(void)stop;
@end
