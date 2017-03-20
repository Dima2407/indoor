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
#import "BluetoothBridge.h"


@interface BluetoothMeasurementProvider()
@property (strong, nonatomic) NSMutableArray *beaconsArray;
@property (nonatomic, assign) BOOL startStatus;
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
    }
    return self;
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
    
    NSUUID *sensoro = [[NSUUID alloc]initWithUUIDString:sensoroUUId];
    
    
    
    for(CLBeacon *beacon in beacons){
        if([beacon.proximityUUID isEqual:sensoro]){
            
            MeasurementEvent * event =[[MeasurementEvent alloc] initWithBeacon:beacon];
                [self.transfer deliver:event];
        }
       
    }
}
- (void)locationManager:(CLLocationManager *)manager
rangingBeaconsDidFailForRegion:(CLBeaconRegion *)region
              withError:(NSError *)error{
    NSLog(@"%@",error);
}
#pragma mark - Set Beacon Data -
-(void) setBeaconMap:(NSArray*)beaconConfigs{
    
        BluetoothBridge_init();
        //BluetoothBridge_setPosition();
    
        [beaconConfigs enumerateObjectsUsingBlock:^(BeaconConfig*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {

        std::string uuidstr = std::string([obj.uuid UTF8String]);
        int major = (int)obj.major ;
        int minor = (int)obj.minor;
        double txPower = obj.txPower;
        double damp = obj.damp;
        BluetoothBridge_initBeacon(uuidstr,major,minor,txPower, damp,obj.x ,obj.y,obj.z);
      
        //navigator.addBeacon(beacon);
    }];
//
   BluetoothBridge_proces();


    
}



@end
