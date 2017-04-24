//
//  BeaconManager.m
//  iosNavigation
//
//  Created by Ievgen on 21.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "BeaconManager.h"

#import "BeaconModel.h"
#import "IndoorLocationManager.h"
#include <math.h>



@interface BeaconManager () <CLLocationManagerDelegate,IndoorLocationListener,ErrorListener>

@property (strong, nonatomic) CLLocationManager *SensoroLocationManager;
@property (strong, nonatomic) NSMutableData *jsonData;
@property (strong, nonatomic) NSMutableArray *beaconsArray;
@property (nonatomic, strong)IndoorLocationManager *manager;
@end
static  NSString *kSettingsframeOnLogs = @"kSettingsframeOnLogs";
@implementation BeaconManager

+(BeaconManager*) sharedManager{
    
    static BeaconManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[BeaconManager alloc]init];
    });
    return manager;
}

-(instancetype)init{
    self = [super init];
    
    if(self){
        
        self.status = YES;
        self.jsonData = [NSMutableData data];
        self.manager = [[IndoorLocationManager alloc] init];
        self.manager.locationListener = self;
        self.manager.errorListener = self;
        [self.manager addUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF"];
        [self.manager addProvider:BLE_PROVIDER];

        
    }
    return self;
}
-(NSArray*)getLogs{
   
    return [self.manager getLog];
}
#pragma mark - Action
-(void) startBeacon{
    BOOL log= [[NSUserDefaults standardUserDefaults] boolForKey:kSettingsframeOnLogs];
    self.manager.isStartLog = log;
    
     [self.manager start];
}

-(void) stopBeacon{
    
    [self.manager stop];
}

#pragma mark - IndoorLocationListenerProtocol

-(void)onLocation:(NSArray *)coordinte{
    
    
    CGFloat x = [[coordinte objectAtIndex:0] floatValue];
    CGFloat y = [[coordinte objectAtIndex:1] floatValue];
    
    if (isnan(x)) 

    {
        
        NSLog(@"Get NAN");
    }
    else{

        NSLog(@"%f  %f",x,y);
    [self.delegate currentLocation:CGPointMake(x, y)];

   }
}
-(void)getError:(IndoorError *)error{
    NSLog(@"error: %@", error.error.description);
}




#pragma mark - Save beacon json -
-(void) saveBeaconDataInJSON:(CLBeacon*)beacon stringUUID:(NSString*)key{
    
    NSDictionary *dataDic = [[NSDictionary alloc]initWithObjectsAndKeys:@(beacon.hash),key,nil];
    NSData *data = [NSJSONSerialization dataWithJSONObject:dataDic options:0 error:nil];
    [self.jsonData appendData:data];
    [self.jsonData writeToFile:@"beacon.json" atomically:YES];
}
#pragma mark - Set Beacon Data -
-(void) setBeaconMap:(FloorModel*)floor withBeaconData:(NSArray*)beacons{

//  [beacons enumerateObjectsUsingBlock:^(BeaconModel*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
//        BeaconConfig *beacon = [[BeaconConfig alloc] initWithUUID:obj.uuid major:obj.major minor:obj.minor txPower:obj.txpower damp:obj.damp andX:obj.x andY:obj.y andZ:obj.z];
//   
//
//        [self.manager setBeaconConfig:beacon];
//    }];
    BeaconConfig *firstBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48049 txPower:-71.2 damp:2 andX:4.5 andY:0.0 andZ:2.3];
    BeaconConfig *forthBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48050 txPower:-71.2 damp:2 andX:0.0 andY:3.7 andZ:2.6];
    
    BeaconConfig *thirdBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48051 txPower:-71.2 damp:2 andX:3 andY:12.8 andZ:2.3];
    BeaconConfig *secondBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48052 txPower:-71.2 damp:2 andX:0.3 andY:9.9 andZ:2.6];
 
    [self.manager setBeaconConfig:firstBeacon];
    [self.manager setBeaconConfig:secondBeacon];
    [self.manager setBeaconConfig:thirdBeacon];
    [self.manager setBeaconConfig:forthBeacon];


}

@end
