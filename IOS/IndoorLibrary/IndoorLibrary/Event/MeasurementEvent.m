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

-(instancetype)initWithTime:(NSInteger)time withMeasurementType:(MeasurementType)type andWithCordinate: (NSArray*)coordinates{
    
    self = [super init];
    MeasurementEvent *event = nil;
    
    if (self != nil)
    {
        event = [self init];
    }
    event.timestamp = time;
    event.type = type;
    event.values = coordinates;
   
    return event;
}


@end
