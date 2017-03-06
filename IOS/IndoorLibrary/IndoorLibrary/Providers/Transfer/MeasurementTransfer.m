//
//  MeasurementTransfer.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "MeasurementTransfer.h"


@implementation MeasurementTransfer
+(void)deliver:(MeasurementEvent*)event
{
    NSLog(@"delivered");
    NSLog(@"Latitude :%f, Longitude: %f",event.latitude, event.longitude);
}
@end
