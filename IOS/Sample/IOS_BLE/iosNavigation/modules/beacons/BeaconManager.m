
//
//  BeaconManager.m
//  iosNavigation
//
//  Created by Ievgen on 21.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "BeaconManager.h"
#import "ConfigHeader.h"
#import "BeaconModel.h"
#import "IndoorLocationManager.h"
#include <math.h>
#import "IndoorHeader.h"


@interface BeaconManager () <CLLocationManagerDelegate,IndoorLocationListener,ErrorListener>

@property (strong, nonatomic) CLLocationManager *SensoroLocationManager;
@property (strong, nonatomic) NSMutableData *jsonData;
@property (strong, nonatomic) NSMutableArray *beaconsArray;
@property (strong, nonatomic) NSMutableArray *positionArray;
@property (nonatomic, strong)IndoorLocationManager *manager;
@property (nonatomic, strong) NSMutableDictionary *config;
@end
//static  NSString *kSettingsframeOnLogs = @"kSettingsframeOnLogs";
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
        self.positionArray = [NSMutableArray new];
        self.manager = [[IndoorLocationManager alloc] init];
        self.manager.locationListener = self;
        self.manager.errorListener = self;
        [self prepare];
        }
    return self;
                     
}
-(NSArray*)getLogs{
    NSMutableArray *log = [NSMutableArray arrayWithArray:[self.manager getLog]];
    [log addObject:self.positionArray];
    
    return [log copy];
}
#pragma mark - Action

-(void) setMesh:(NSArray*)mesh and:(NSArray*)mask{
    
    [self.config setValue:[mesh objectAtIndex:0] forKey:@"nx"];
    [self.config setValue:[mesh objectAtIndex:1] forKey:@"ny"];
    [self.config setValue:[mesh objectAtIndex:2] forKey:@"dx"];
    [self.config setValue:[mesh objectAtIndex:3] forKey:@"dy"];
    [self.config setValue:[mesh objectAtIndex:4] forKey:@"x0"];
    [self.config setValue:[mesh objectAtIndex:5] forKey:@"y0"];
    [self.config setValue:mask forKey:@"mask"];
}

-(void) startBeacon{
    [self.manager setConfiguration:self.config];
    [self prepare];
    [self.manager prepare];
    [self.manager start];
}
-(void)prepare{
    if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLENavigationSwitch])
    {
        [self.manager addUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF"];
        [self.manager addProvider:BLE_PROVIDER];
    }
    if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorNavigationSwitch])
    {
        [self.manager addProvider:SENSOR_PROVIDER];
        if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorRSSIAveraging])
        {
            [self.manager addUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF"];
            [self.manager addProvider:BLE_PROVIDER];
            
        }
    }
    self.manager.isStartLog = YES;
    self.config = [NSMutableDictionary dictionaryWithObjectsAndKeys:@(0), @"useMesh",@(0), @"nx",@(0), @"ny",@(0), @"dx",@(0), @"dy",@(0), @"x0",@(0), @"y0",@(0), @"useGraph",[NSString new], @"graph",@(0.0), @"scale",@(0), @"bleCircleBuffers",@(0), @"bleTrilatiration",@(0), @"bleKalmanFilter",@(0), @"bleMap",@(0), @"bleMesh",@(0), @"bleWalls",@(0), @"sensorInitManual",@(0), @"x",@(0), @"y",@(0), @"sensorRSSIAveraging",@(0), @"sensorKalman",@(0), @"sensorMap",@(0), @"sensorMesh",@(0), @"sensorWalls",@(0), @"orientationAngle",@(0), @"useMask", [NSArray new], @"mask",nil];
    

}
-(void) stopBeacon{
    
    [self.manager stop];

}
-(void) releseBeacon{
        self.manager = nil;
}

#pragma mark - IndoorLocationListenerProtocol

-(void)onLocation:(NSArray *)coordinte{
    
    
    CGFloat x = [[coordinte objectAtIndex:0] floatValue];
    CGFloat y = [[coordinte objectAtIndex:1] floatValue];
    NSDictionary *pos = [NSDictionary dictionaryWithObjectsAndKeys:
                         
                         @(x),@"x",
                         @(y),@"y",
                         nil];
    [self.positionArray addObject:pos];
    
    if (isnan(x))
        
    {
        
        [self.delegate currentLocation:CGPointZero];
    }
    else{
        
        //NSLog(@"%f  %f",x,y);
        NSArray* routing = nil;
        if ( [[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRout"])
        {
            self.manager.isRouting = YES;
            routing = [[self.manager getRouting] copy];
        }
        
        [self.delegate currentRouting:routing];
        [self.delegate currentLocation:CGPointMake(x, y)];
//                        NSLog(@"X-----%f",x);
//                        NSLog(@"Y-----%f",y);
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
    if (beacons)
    {
      
    [beacons enumerateObjectsUsingBlock:^(BeaconModel*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        NSString* uuidUpperCase = [obj.uuid uppercaseString];
        BeaconConfig *beacon = [[BeaconConfig alloc] initWithUUID:uuidUpperCase major:obj.major minor:obj.minor txPower:obj.txpower damp:obj.damp andX:obj.x andY:obj.y andZ:obj.z];
        
        
        [self.manager setBeaconConfig:beacon];
    }];}
    else{
            NSLog(@"Beacons is nil");
        }
//        BeaconConfig *firstBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48049 txPower:-71.2 damp:2 andX:4.5 andY:0.0 andZ:2.3];
//        BeaconConfig *forthBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48050 txPower:-71.2 damp:2 andX:0.0 andY:3.7 andZ:2.6];
//    
//        BeaconConfig *thirdBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48051 txPower:-71.2 damp:2 andX:3 andY:12.8 andZ:2.3];
//        BeaconConfig *secondBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48052 txPower:-71.2 damp:2 andX:0.3 andY:9.9 andZ:2.6];
//        [self.manager setBeaconConfig:firstBeacon];
//        [self.manager setBeaconConfig:secondBeacon];
//        [self.manager setBeaconConfig:thirdBeacon];
//        [self.manager setBeaconConfig:forthBeacon];
}
#pragma mark - Set Graph -
-(void) setGraph:(FloorModel*)floor withGraph:(NSString*)gpaphJsonString{
    NSString* parsedString = [gpaphJsonString stringByReplacingOccurrencesOfString:@"\r" withString:@""];
    if (parsedString == nil)
    {
        NSLog(@"Graph is nil");
    }
    else{
        [self.config setValue:@(1) forKey:@"useGraph"];
        [self.config setValue:@(floor.pixelSize) forKey:@"scale"];
        [self.config setValue:parsedString forKey:@"graph"];
        self.manager.isRouting = true;
        
    }
}
-(void)setDestination:(CGPoint)destination{
    [self.manager setDectinationPosition:[NSArray arrayWithObjects:@(destination.x),@(destination.y),0, nil]];
}
-(void)setBeaconConfig:(NSString*)filter useMultilat:(BOOL)multilat useMap:(BOOL)map useMesh:(BOOL)mesh useWalls:(BOOL)walls{
    
    [self.manager setMode:BLE_MODE];
    
    if ([filter isEqualToString:@"CircleBuffers"])
    {
        [self.config setValue:@(1) forKey:@"bleCircleBuffers"];
        [self.config setValue:@(0) forKey:@"bleKalmanFilter"];
    }
    
    else if ([filter isEqualToString:@"KalmanFilter"])
    {
        [self.config setValue:@(0) forKey:@"bleCircleBuffers"];
        [self.config setValue:@(1) forKey:@"bleKalmanFilter"];
    }
    else
    {
        NSLog(@"Invalid filter type");
    }
    [self.config setValue:@(multilat) forKey:@"bleTrilatiration"];
    [self.config setValue:@(map) forKey:@"bleMap"];
    [self.config setValue:@(mesh) forKey:@"bleMesh"];
    [self.config setValue:@(walls) forKey:@"bleWalls"];
    
    
}
-(void)setSensorConfig:(NSString*)filter useMap:(BOOL)map useMesh:(BOOL)mesh useWalls:(BOOL)walls x:(double)x y:(double)y{
    [self.manager setMode:SENSOR_MODE];
    if ([filter isEqualToString:@"Manual"])
    {
        [self.config setValue:@(1) forKey:@"sensorInitManual"];
        [self.config setValue:@(x) forKey:@"x"];
        [self.config setValue:@(y) forKey:@"y"];
        [self.config setValue:@(0) forKey:@"sensorRSSIAveraging"];
        [self.config setValue:@(0) forKey:@"sensorKalman"];
    }
    
    else if ([filter isEqualToString:@"RSSIAveraging"])
    {
        [self.config setValue:@(0) forKey:@"sensorInitManual"];
        [self.config setValue:@(1) forKey:@"sensorRSSIAveraging"];
        [self.config setValue:@(0) forKey:@"sensorKalman"];
    }
    else if ([filter isEqualToString:@"KalmanFilter"])
    {
        [self.config setValue:@(0) forKey:@"sensorRSSIAveraging"];
        [self.config setValue:@(1) forKey:@"sensorKalman"];
    }
    else
    {
        NSLog(@"Invalid filter type");
    }
    [self.config setValue:@(x) forKey:@"x"];
    [self.config setValue:@(y) forKey:@"y"];
    [self.config setValue:@(map) forKey:@"sensorMap"];
    [self.config setValue:@(mesh) forKey:@"sensorMesh"];
    [self.config setValue:@(walls) forKey:@"sensorWalls"];
}
@end
