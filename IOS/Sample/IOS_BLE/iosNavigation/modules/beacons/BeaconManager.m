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

-(void) setMode:(NSString*)mode{
    if ([mode isEqualToString:@"Standart"])
    {
        [self.manager setMode:STANDART_MODE];
    }
    else if ([mode isEqualToString:@"UseMesh"]){
    
         [self.manager setMode:MESH_MODE];
    }
    else{
        NSLog(@"Invalid mode type");
    }
}
-(void) setConfigs:(NSArray*)mesh and:(NSArray*)mask{
    
    [self.manager setMeshConfig:mesh andOut:mask];
    
}

-(void) startBeacon{
    [self.manager prepare];
    
     [self.manager start];
}

-(void) stopBeacon{
    
    [self.manager stop];
}
-(void)deleteMesh{
    [self.manager deleteMesh];
}

#pragma mark - IndoorLocationListenerProtocol

-(void)onLocation:(NSArray *)coordinte{
    
    
    CGFloat x = [[coordinte objectAtIndex:0] floatValue];
    CGFloat y = [[coordinte objectAtIndex:1] floatValue];
    
    if (isnan(x)) 

    {
        
        [self.delegate currentLocation:CGPointZero];
    }
    else{

        NSLog(@"%f  %f",x,y);
       //[self.delegate currentLocation:CGPointMake(0, 1)];
        NSArray* routing = nil;
        if ( [[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRout"])
        {
            self.manager.isRouting = YES;
            routing = [[self.manager getRouting] copy];
        }
       
    [self.delegate currentRouting:routing];
    [self.delegate currentLocation:CGPointMake(x, y)];

   }
}
-(CGFloat)getDistance{
    if ( [[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRout"])
    {
   return  [self.manager getDistance];
    }
    else{
        NSLog(@"Distance 0");
        return 0;
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
//      NSString* uuidUpperCase = [obj.uuid uppercaseString];
//        BeaconConfig *beacon = [[BeaconConfig alloc] initWithUUID:uuidUpperCase major:obj.major minor:obj.minor txPower:obj.txpower damp:obj.damp andX:obj.x andY:obj.y andZ:obj.z];
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
#pragma mark - Set Graph -
-(void) setGraph:(FloorModel*)floor withGraph:(NSString*)gpaphJsonString{
    
    NSString* parsedString = [gpaphJsonString stringByReplacingOccurrencesOfString:@"\r" withString:@""];
    if (parsedString == nil)
    {
        NSLog(@"Graph is nil");
    }
    else{
    [self.manager setGraph:parsedString and:floor.pixelSize];
    self.manager.isRouting = true;
    
    }
}
-(void)setDestination:(CGPoint)destination{
    [self.manager setDectinationPosition:[NSArray arrayWithObjects:@(destination.x),@(destination.y),0, nil]];
}

@end
