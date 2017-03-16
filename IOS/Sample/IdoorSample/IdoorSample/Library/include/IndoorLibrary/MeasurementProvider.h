//
//  MeasurementProvider.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementEvent.h"
#import "IosMeasurementTransfer.h"

@interface MeasurementProvider : NSObject
@property (nonatomic, strong) IosMeasurementTransfer *transfer;

-(void)start;
-(void)stop;
@end
