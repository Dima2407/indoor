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
@property (nonatomic, strong)MeasurementProvider *provider;
@property (nonatomic, assign) BOOL startStatus;
@property (nonatomic, strong) IosMeasurementTransfer *transfer;



@end

@implementation GPSMeasurementProvider



- (id) init
{
    self = [super init];
    
    if (self != nil)
    {
        self.startStatus = NO;
        self.manager = [[CLLocationManager alloc] init];
        self.manager.delegate = self;
        self.manager.desiredAccuracy = kCLLocationAccuracyBest;
        [self.manager requestWhenInUseAuthorization];
        self.transfer = [[IosMeasurementTransfer alloc] init];
    }
    return self;
}
-(void)_showAlert:(NSString*) message
{
    UIAlertView * alert = [[UIAlertView alloc]initWithTitle:@"Error" message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    
    [alert show];
    
}

#pragma mark - CLLocationManagerDelegate


- (void)locationManager:(CLLocationManager *)manager
didChangeAuthorizationStatus:(CLAuthorizationStatus)status
{
    
    switch (status) {
        case kCLAuthorizationStatusNotDetermined:
             NSLog(@"Determined");
            [manager requestWhenInUseAuthorization];
            break;
        case kCLAuthorizationStatusAuthorizedWhenInUse:
             NSLog(@"AuthorizedWhenInUse");
            if (self.startStatus)
            {
                 [manager startUpdatingLocation];
            }
           
            break;
        case kCLAuthorizationStatusAuthorizedAlways:
             NSLog(@"AuthorizedAlways");
            if (self.startStatus)
            {
                [manager startUpdatingLocation];
            }
            break;
        case kCLAuthorizationStatusRestricted:
             NSLog(@"Restricted");
            [self _showAlert:@"App Permission Restricted. You can't enable Location Services"];
            
            break;
            
        default:
            break;
    }
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(nonnull NSArray<CLLocation *> *)locations{
    
    CLLocation *location = [locations objectAtIndex:0];
    MeasurementEvent *event = [[MeasurementEvent alloc] initWithLatitude:location.coordinate.latitude andLatitude:location.coordinate.longitude];
    [self.transfer deliver:event];
 
    
    
    
}
-(void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error{
    
    [manager stopUpdatingLocation];
    NSLog(@"error%@",error);
    switch([error code])
    {
        case kCLErrorNetwork:
        {
            [self _showAlert:@"Please check your network connection."];
           
           
        }
            break;
        case kCLErrorDenied:{
            
            [self _showAlert:@"App Permission Denied"];

       }
            break;
        default:
        {
            [self _showAlert:@"Unknown network error"];
          
        }
            break;
    }
}

#pragma mark - Actions


-(void)start
{
    self.startStatus = YES;
    CLAuthorizationStatus status = [CLLocationManager authorizationStatus];
    switch (status) {
        case kCLAuthorizationStatusNotDetermined:
            NSLog(@"Determined");
            [self _showAlert:@"App Permission Denied"];
            break;
        case kCLAuthorizationStatusAuthorizedWhenInUse:
            NSLog(@"AuthorizedWhenInUse");
            [self.manager startUpdatingLocation];
            break;
        case kCLAuthorizationStatusAuthorizedAlways:
            NSLog(@"AuthorizedAlways");
            [self.manager startUpdatingLocation];
            break;
        case kCLAuthorizationStatusRestricted:
            NSLog(@"Restricted");
            [self _showAlert:@"App Permission Restricted. User can't enable Location Services"];
            
            break;
            
        default:
            break;
    }
    
    
}
-(void)stop
{
    [self.manager stopUpdatingLocation];
    self.startStatus = NO;
}

@end
