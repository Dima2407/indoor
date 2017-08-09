//
//  BluetoothMeasurementProvider.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "BluetoothMeasurementProvider.h"
#import <CoreLocation/CLLocationManager.h>

@interface BluetoothMeasurementProvider()<CLLocationManagerDelegate>
@property (nonatomic, assign) BOOL startStatus;
@property (nonatomic, strong) NSMutableArray* beaconsUUIDs;
@property (nonatomic, strong) NSMutableArray* beaconsRegion;
@property (nonatomic, strong) CLLocationManager *manager;
@property (nonatomic, strong) MeasurementEvent *event;
@property (nonatomic, strong) IosMeasurementTransfer *transfer;
@end

@implementation BluetoothMeasurementProvider
@synthesize transfer;


-(instancetype)initWithTransfer: (IosMeasurementTransfer*) bleTransfer andUUIDs:(NSMutableArray*)uuids{
    self = [super init];
    
    if(self){
        
    
        self.manager = [[CLLocationManager alloc]init];
        self.manager.delegate = self;
        self.manager.desiredAccuracy = kCLLocationAccuracyBest;
        self.transfer = bleTransfer;
          [self.manager requestWhenInUseAuthorization];
        self.beaconsRegion = [NSMutableArray new];
        self.beaconsUUIDs = uuids;
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
    [self.beaconsUUIDs enumerateObjectsUsingBlock:^(NSString*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        
            [self startBeaconWihtUUID:obj locationManager:self.manager];
    }];
  

  
   
}

-(void) startBeaconWihtUUID:(NSString*)uuid locationManager:(CLLocationManager*)locationManager{
    NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:uuid];
    CLBeaconRegion *region = [[CLBeaconRegion alloc]initWithProximityUUID:beaconUUID identifier:[NSString stringWithFormat:@"%@",uuid]];
    
    [self.beaconsRegion addObject:region];
    [locationManager startRangingBeaconsInRegion:region];
    
}

-(void)stop{
    
  
        [self.beaconsRegion enumerateObjectsUsingBlock:^(CLBeaconRegion*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            [self.manager stopRangingBeaconsInRegion:obj];
        }];
        
    
  
}

#pragma mark - CLLocationManagerDelegate -
-(void)locationManager:(CLLocationManager *)manager didRangeBeacons:(NSArray<CLBeacon *> *)beacons inRegion:(CLBeaconRegion *)region{
    NSMutableArray *indoorBeacons = [NSMutableArray new];
    [self.beaconsUUIDs enumerateObjectsUsingBlock:^(NSString*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        
        NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:obj];
        for(CLBeacon *beacon in beacons){
            if([beacon.proximityUUID isEqual:beaconUUID]){
                
//                MeasurementEvent * event =[[MeasurementEvent alloc] initWithBeacon:beacon];
//                [self.transfer deliver:event];
                
                [indoorBeacons addObject:beacon];
                
            }
            MeasurementEvent * event = [[MeasurementEvent alloc] initWithBeacons:[indoorBeacons copy]];
            [self.transfer deliver:event];
        }
    }];

    
    
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
