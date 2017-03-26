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
@property (nonatomic, strong) CLLocationManager *manager;


@end

@implementation GPSMeasurementProvider



-(instancetype)initWithTransfer: (IosMeasurementTransfer*) transfer {
    self = [super init];
    
    if (self != nil)
    {
        self.startStatus = NO;
        self.manager = [[CLLocationManager alloc] init];
        self.manager.delegate = self;
        self.manager.desiredAccuracy = kCLLocationAccuracyBest;
        [self.manager requestWhenInUseAuthorization];
        self.transfer = transfer;
        self.type = GPS_PROVIDER;
        
       
    }
    return self;
}

#pragma mark - Error


-(void)_throwErrorWithOptions:(NSUInteger)code title:(NSString*)title message:(NSString*) message
{
    IndoorError *error = [[IndoorError alloc] initWithOptions:code title:title message:message];
    [self.transfer deliverError:error];
    
}

#pragma mark - CLLocationManagerDelegate


- (void)locationManager:(CLLocationManager *)manager
didChangeAuthorizationStatus:(CLAuthorizationStatus)status
{
    
    switch (status) {
        case kCLAuthorizationStatusNotDetermined:
            [self _throwErrorWithOptions:2 title:@"Error Permission" message:@"App Permission Denied"];
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
            
            
            [self _throwErrorWithOptions:3 title:@"Error Permission" message:@"App Permission Restricted. You can't enable Location Services"];
           break;
            
        default:
            break;
    }
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(nonnull NSArray<CLLocation *> *)locations{
    CLLocation *location = [locations objectAtIndex:0];
    MeasurementEvent *event = [[MeasurementEvent alloc] initWithLatitude:location.coordinate.latitude andLongitude:location.coordinate.longitude];
    [self.transfer deliver:event];
 
    
    
    
}
-(void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error{
    
    [manager stopUpdatingLocation];
    
    switch([error code])
    {
        case kCLErrorNetwork:
            
        {
            [self _throwErrorWithOptions:1 title:@"Error Network" message:@"Please check your network connection"];
        }
            break;
            
        case kCLErrorDenied:{
            
            [self _throwErrorWithOptions:2 title:@"Error Permission" message:@"App Permission Denied"];
       }
            break;
            
        default:
        {
            [self _throwErrorWithOptions:0 title:@"Unknown Error" message:@"Unknown network error"];
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
         [self _throwErrorWithOptions:2 title:@"Error Permission" message:@"App Permission Denied"];
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
            [self _throwErrorWithOptions:3 title:@"Error Permission" message:@"App Permission Restricted. You can't enable Location Services"];
            
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
