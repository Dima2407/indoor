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

@interface BluetoothMeasurementProvider()
@property (strong, nonatomic) NSMutableArray *beaconsArray;
@property (nonatomic, assign) BOOL startStatus;



@end

@implementation BluetoothMeasurementProvider
static NSString *sensoroUUId = @"23A01AF0-232A-4518-9C0E-323FB773F5EF";

-(instancetype)init{
    self = [super init];
    
    if(self){
        
    
        self.manager = [[CLLocationManager alloc]init];
        self.manager.delegate = self;
        self.manager.desiredAccuracy = kCLLocationAccuracyBest;
    }
    return self;
}

#pragma mark - Start beacon -
-(void) start{
    
    [self startBeaconWihtUUID:sensoroUUId locationManager:self.manager];
   
}

-(void) startBeaconWihtUUID:(NSString*)uuid locationManager:(CLLocationManager*)locationManager{
    
    NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:uuid];
    CLBeaconRegion *region = [[CLBeaconRegion alloc]initWithProximityUUID:beaconUUID identifier:@"IT-JIM"];
    
   
    [locationManager startRangingBeaconsInRegion:region];
}

#pragma mark - CLLocationManagerDelegate -
-(void)locationManager:(CLLocationManager *)manager didRangeBeacons:(NSArray<CLBeacon *> *)beacons inRegion:(CLBeaconRegion *)region{
    
    NSUUID *sensoro = [[NSUUID alloc]initWithUUIDString:sensoroUUId];
  
    
    for(CLBeacon *beacon in beacons){
        if([beacon.proximityUUID isEqual:sensoro]){
        [MeasurementTransfer deliver:[[MeasurementEvent alloc] initWithRssi:beacon.rssi andUUID:beacon.minor.integerValue]];
        }

       
    }
    
 
}
- (void)locationManager:(CLLocationManager *)manager
rangingBeaconsDidFailForRegion:(CLBeaconRegion *)region
              withError:(NSError *)error{
    NSLog(@"%@",error);
}
#pragma mark - Set Beacon Data -
-(void) setBeaconMap:(NSArray*)beacons{
    
        
}

-(void)stop{

    NSUUID *beaconUUID = [[NSUUID alloc]initWithUUIDString:sensoroUUId];
    CLBeaconRegion *region = [[CLBeaconRegion alloc]initWithProximityUUID:beaconUUID identifier:@"IT-JIM"];

    [self.manager stopRangingBeaconsInRegion:region];
}

@end
