//
//  BluetoothMeasurementProvider.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "BluetoothMeasurementProvider.h"
#import <CoreLocation/CLLocationManager.h>
#import "MeasurementEvent.h"
#import "MeasurementProvider.h"
#import "BeaconConfig.h"



@interface BluetoothMeasurementProvider()
@property (strong, nonatomic) NSMutableArray *beaconsArray;
@property (nonatomic, assign) BOOL startStatus;
@property (nonatomic, strong) CLLocationManager *manager;
@property (nonatomic, strong) MeasurementEvent *event;
@property (nonatomic, strong) IosMeasurementTransfer *transfer;
@property (nonatomic, strong) NSMutableArray *uuids;
@end

@implementation BluetoothMeasurementProvider

static NSString *sensoroUUId = @"23A01AF0-232A-4518-9C0E-323FB773F5EF";
-(instancetype)init: (IosMeasurementTransfer*) transfer{
    self = [super init];
    
    if(self){
        
    
        self.manager = [[CLLocationManager alloc]init];
        self.manager.delegate = self;
        self.manager.desiredAccuracy = kCLLocationAccuracyBest;
        self.transfer = transfer;
        self.uuids = [NSMutableArray new];
          [self.manager requestWhenInUseAuthorization];
        //[self.uuids addObject:@"23A01AF0-232A-4518-9C0E-323FB773F5EF"];
        self.type = BLE_PROVIDER;
    }
    return self;
}
-(void)setUuid:(NSString*)uuid{
    [self.uuids addObject:uuid];
}

#pragma mark - Action
-(void) start{
  
         [self startBeaconWihtUUID:sensoroUUId locationManager:self.manager];
  
    NSLog(@"start");
   
}

-(void) startBeaconWihtUUID:(NSString*)uuid locationManager:(CLLocationManager*)locationManager{
    NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:uuid];
    CLBeaconRegion *region = [[CLBeaconRegion alloc]initWithProximityUUID:beaconUUID identifier:@"IT-JIM"];
    
   
    [locationManager startRangingBeaconsInRegion:region];
    NSLog(@"startBeaconWihtUUID");
}

-(void)stop{
    
  NSLog(@"stop");
        NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:sensoroUUId];
        CLBeaconRegion *region = [[CLBeaconRegion alloc]initWithProximityUUID:beaconUUID identifier:@"IT-JIM"];
        
        [self.manager stopRangingBeaconsInRegion:region];
  

    
}

#pragma mark - CLLocationManagerDelegate -
-(void)locationManager:(CLLocationManager *)manager didRangeBeacons:(NSArray<CLBeacon *> *)beacons inRegion:(CLBeaconRegion *)region{
NSLog(@"didRangeBeacons");
        NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:sensoroUUId];
        for(CLBeacon *beacon in beacons){
            if([beacon.proximityUUID isEqual:beaconUUID]){
                
                MeasurementEvent * event =[[MeasurementEvent alloc] initWithBeacon:beacon];
                [self.transfer deliver:event];
      
            
        }
    }


    
    
    
    
}
- (void)locationManager:(CLLocationManager *)manager
rangingBeaconsDidFailForRegion:(CLBeaconRegion *)region
              withError:(NSError *)error{
    NSLog(@"TTTTTTTTTTT",error);
    
}



@end
