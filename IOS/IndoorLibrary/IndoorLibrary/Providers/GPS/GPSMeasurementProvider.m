//
//  GPSMeasurementProvider.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "GPSMeasurementProvider.h"
#import <CoreLocation/CLLocationManager.h>
#import "MeasurementEvent.h"
#import "MeasurementProvider.h"


@interface GPSMeasurementProvider()

@property (nonatomic, strong) CLLocationManager *manager;
@property (nonatomic, strong) MeasurementEvent *event;

@end

@implementation GPSMeasurementProvider



- (id) init
{
    self = [super init];
    
    if (self != nil)
    {
        self.manager = [[CLLocationManager alloc] init];
    }
    return self;
}

- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation {
    
    NSArray* coordinates = [[NSArray alloc] initWithObjects:@(newLocation.coordinate.latitude), @(newLocation.coordinate.longitude),nil];
    self.event = [[MeasurementEvent alloc] initWithTime:[[NSDate date] timeIntervalSince1970] withMeasurementType:GEO_VALUE andWithCordinate:coordinates];
    [MeasurementProvider deliver:self.event];
 
   
}

-(void)start
{
    [self.manager startUpdatingLocation];
}
-(void)stop
{
    [self.manager stopUpdatingLocation];
}

@end
