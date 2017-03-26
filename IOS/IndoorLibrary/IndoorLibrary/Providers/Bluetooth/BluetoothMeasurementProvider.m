//
//  BluetoothMeasurementProvider.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "BluetoothMeasurementProvider.h"
#import <CoreLocation/CLLocationManager.h>

@interface BluetoothMeasurementProvider()
@property (strong, nonatomic) NSMutableArray *beaconsArray;
@property (nonatomic, assign) BOOL startStatus;
@property (nonatomic, strong) CLLocationManager *manager;
@property (nonatomic, strong) MeasurementEvent *event;
@property (nonatomic, strong) IosMeasurementTransfer *transfer;
@end

@implementation BluetoothMeasurementProvider

static NSString *sensoroUUId = @"23A01AF0-232A-4518-9C0E-323FB773F5EF";
-(instancetype)initWithTransfer:(IosMeasurementTransfer *)transfer{
    self = [super init];
    
    if(self){
        
    
        self.manager = [[CLLocationManager alloc]init];
        self.manager.delegate = self;
        self.manager.desiredAccuracy = kCLLocationAccuracyBest;
        self.transfer = transfer;
          [self.manager requestWhenInUseAuthorization];
        self.type = BLE_PROVIDER;
    }
    return self;
}

#pragma mark - Error


-(void)_throwErrorWithOptions:(NSUInteger)code title:(NSString*)title message:(NSString*) message
{
    IndoorError *error = [[IndoorError alloc] initWithOptions:code title:title message:message];
    [self.transfer deliverError:error];
    
}

#pragma mark - Action
-(void) start{
  
    [self startBeaconWihtUUID:sensoroUUId locationManager:self.manager];
  
   
}

-(void) startBeaconWihtUUID:(NSString*)uuid locationManager:(CLLocationManager*)locationManager{
    NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:uuid];
    CLBeaconRegion *region = [[CLBeaconRegion alloc]initWithProximityUUID:beaconUUID identifier:@"IT-JIM"];
    
   
    [locationManager startRangingBeaconsInRegion:region];
    
}

-(void)stop{
    
  
        NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:sensoroUUId];
        CLBeaconRegion *region = [[CLBeaconRegion alloc]initWithProximityUUID:beaconUUID identifier:@"IT-JIM"];
        
        [self.manager stopRangingBeaconsInRegion:region];
  
}

#pragma mark - CLLocationManagerDelegate -
-(void)locationManager:(CLLocationManager *)manager didRangeBeacons:(NSArray<CLBeacon *> *)beacons inRegion:(CLBeaconRegion *)region{

        NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:sensoroUUId];
        for(CLBeacon *beacon in beacons){
            if([beacon.proximityUUID isEqual:beaconUUID]){
                
                MeasurementEvent * event =[[MeasurementEvent alloc] initWithBeacon:beacon];
                [self.transfer deliver:event];
            
        }
    }
}

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

- (void)locationManager:(CLLocationManager *)manager
rangingBeaconsDidFailForRegion:(CLBeaconRegion *)region
              withError:(NSError *)error{
 
    [self _throwErrorWithOptions:5 title:@"Beacon Region Error" message:error.description];
}



@end
