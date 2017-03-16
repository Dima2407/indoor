//
//  MeasurementTransfer.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementEvent.h"
#import "MeasurementTranfer.h"


@interface IosMeasurementTransfer : NSObject<MeasurementTranfer>

+(void)deliver:(MeasurementEvent*)event;

@end
