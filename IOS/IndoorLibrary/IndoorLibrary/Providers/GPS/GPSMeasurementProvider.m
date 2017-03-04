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
- (void)locationManager:(CLLocationManager *)manager
didChangeAuthorizationStatus:(CLAuthorizationStatus)status
{
    switch (status) {
        case kCLAuthorizationStatusNotDetermined:
            [manager requestAlwaysAuthorization];
            break;
        case kCLAuthorizationStatusAuthorizedWhenInUse:
            [manager startUpdatingLocation];
            break;
        case kCLAuthorizationStatusAuthorizedAlways:
            [manager startUpdatingLocation];
            break;
        case kCLAuthorizationStatusRestricted:
            [self _showAlert:@"App Permission Restricted. User can't enable Location Services"];
            
            break;
            
        default:
            break;
    }
}
-(void)_showAlert:(NSString*) message
{
    UIAlertView * alert = [[UIAlertView alloc]initWithTitle:@"" message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    
    [alert show];
    
}
- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(nonnull NSArray<CLLocation *> *)locations{
    CLLocation *location = [locations objectAtIndex:0];
    NSLog(@"%f", location.coordinate.latitude);
    self.longitude = location.coordinate.longitude;
    NSArray* coordinates = [[NSArray alloc] initWithObjects:@(location.coordinate.latitude), @(location.coordinate.longitude),nil];
    self.event = [[MeasurementEvent alloc] initWithTime:[[NSDate date] timeIntervalSince1970] withMeasurementType:GEO_VALUE andWithCordinate:coordinates];
    [MeasurementProvider deliver:self.event];
    
    
}
-(void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error{
    
    NSLog(@"%@",error.userInfo);
    if([CLLocationManager locationServicesEnabled]){
        
        NSLog(@"Location Services Enabled");
        
        if([CLLocationManager authorizationStatus]==kCLAuthorizationStatusDenied){
            UIAlertView    *alert = [[UIAlertView alloc]
                                     initWithTitle:@"App Permission Denied"
                                     message:@"To re-enable, please go to Settings and turn on Location Service for this app."
                                     delegate:nil
                                     cancelButtonTitle:@"OK"
                                     otherButtonTitles:nil];
            [alert show];
        }
    }
}

-(void)start
{
    self.manager.delegate = self;
    self.manager.desiredAccuracy = kCLLocationAccuracyBest;
    [self.manager requestAlwaysAuthorization];
    if ([self.manager locationServicesEnabled]){
        
        NSLog(@"Location Services Enabled");
        NSLog(@"%d",[CLLocationManager authorizationStatus]);
        
        
        [self.manager startUpdatingLocation];
        
        
    }
    
    
}
-(void)stop
{
    [self.manager stopUpdatingLocation];
}

@end
