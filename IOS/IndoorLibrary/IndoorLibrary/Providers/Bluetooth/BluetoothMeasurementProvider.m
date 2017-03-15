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
                [IosMeasurementTransfer deliver:event];
        }
       
    }
    
//    float x = SensorBridge_getX();
//    float y = SensorBridge_getY();
//    NSLog(@"current (x, y) - (%f, %f)", x, y);
//    //[self.delegate currentLocation:CGPointMake(x, y)];
//    

       
    
    
 
}
- (void)locationManager:(CLLocationManager *)manager
rangingBeaconsDidFailForRegion:(CLBeaconRegion *)region
              withError:(NSError *)error{
    NSLog(@"%@",error);
}
#pragma mark - Set Beacon Data -
+(void) setBeaconMap:(NSArray*)beacons{
    
    
    [beacons enumerateObjectsUsingBlock:^(BeaconConfig*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        
        float x = obj.x;
        float y = obj.y;
        int major = (int)obj.minor ;
        //SensorBridge_onNewBeaconCoords(major, 2.f, x, y);
        NSLog(@"%d\n %f\n %f",major,x,y);
    }];


    
}



#pragma mark - Error
-(void)_showAlert:(NSString*) message
{
    UIAlertView * alert = [[UIAlertView alloc]initWithTitle:@"Error" message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    
    [alert show];
    
}


@end
