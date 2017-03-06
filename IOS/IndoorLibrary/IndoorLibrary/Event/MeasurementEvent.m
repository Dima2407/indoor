//
//  MeasurementEvent.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "MeasurementEvent.h"
#import "MeasurementProvider.h"


@interface MeasurementEvent()



@end

@implementation MeasurementEvent

-(instancetype)initWithLatitude:(CGFloat)latitude andLatitude:(CGFloat)longitude {
    
    self = [super init];
    MeasurementEvent *event = nil;
    
    if (self != nil)
    {
        event = [self init];
    }
    event.timestamp = [[NSDate date] timeIntervalSince1970];
    event.type = GEO_VALUE;
    event.latitude = latitude;
    event.longitude = longitude;
    return event;
}


@end
