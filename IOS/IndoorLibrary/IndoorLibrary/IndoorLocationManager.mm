//
//  IndoorLocationManager.m
//  IndoorLibrary
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//
#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / M_PI))
#import "IndoorLocationManager.h"
#import "BluetoothMeasurementProvider.h"
#import "GPSMeasurementProvider.h"
#import "SensorMeasurementProvider.h"
#import "BluetoothBridge.h"
#import "KalmanBridge.hpp"
#import "SensorBridge.h"
#import "IndoorError.h"
#include <iostream>
#include <vector>


@interface IndoorLocationManager()<IosMeasurementTransferDelegate>
@property (nonatomic, strong) NSMutableArray *acselLogs;
@property (nonatomic, strong) NSMutableArray *moutingLogs;
@property (nonatomic, strong) NSMutableArray *beaconLogs;
@property (nonatomic, strong) NSMutableSet *providers;
@property (nonatomic, strong) IosMeasurementTransfer* transfer;
@property (nonatomic, strong) NSMutableArray* beaconsUUIDs;
@property (nonatomic, assign) NSTimeInterval time;
@property (nonatomic, assign) BOOL startProviderFlag;
@property (nonatomic, assign) IndoorLocationManagerMode managerMode;
@property (nonatomic, assign) BOOL initSensorNavigator;
@property (nonatomic, assign) double startTimestamp;
@property (nonatomic, strong) NSDictionary *config;
@end


@implementation IndoorLocationManager

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        self.providers = [NSMutableSet new];
        self.transfer = [[IosMeasurementTransfer alloc] init];
        self.transfer.delegate = self;
        self.beaconLogs = [NSMutableArray new];
        self.acselLogs = [NSMutableArray new];
        self.moutingLogs = [NSMutableArray new];
        self.time = 1;
        self.startProviderFlag = NO;
        self.beaconsUUIDs = [[NSMutableArray alloc] init];
        self.startTimestamp =  [[NSDate date] timeIntervalSince1970];
        _initSensorNavigator = NO;
        
        
    }
    return self;
}

#pragma mark - Logic

-(void)addProvider:(MeasurementProviderType)type{
    if (self.startProviderFlag)
    {
        NSLog(@"You can't add provider when IndoorLocationManager started");
    }
    else{
        MeasurementProvider * provider = nil;
        switch (type) {
            case GPS_PROVIDER:
                provider = [[GPSMeasurementProvider alloc] initWithTransfer: self.transfer];
                if(provider != nil){
                    
                    [self.providers addObject:provider];
                }
                
                break;
            case BLE_PROVIDER:
                if (self.beaconsUUIDs.count == 0)
                {
                    NSLog(@"Add UUID before start BLE_PROVIDER");
                }
                provider = [[BluetoothMeasurementProvider alloc] initWithTransfer:self.transfer andUUIDs:self.beaconsUUIDs];
                if(provider != nil){
                    
                    [self.providers addObject:provider];
                }
                
                break;
            case SENSOR_PROVIDER:
                provider = [[SensorMeasurementProvider alloc] initWithTransfer: self.transfer];
                if(provider != nil){
                    
                    [self.providers addObject:provider];
                }
                
                break;
            default:
                break;
        }
    }
}

-(void)removeProvider: (MeasurementProviderType) type{
    
    if (self.startProviderFlag)
    {
        NSLog(@"You can't remove provider when IndoorLocationManager started");
    }
    else{
        
        if (type == BLE_PROVIDER)
        {
            
            [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
                if (obj.type == BLE_PROVIDER)
                {
                    obj = nil;
                    [self.providers removeObject:obj];
                }
                
            }];
            
        }
        
        else if (type == GPS_PROVIDER){
            [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
                if (obj.type == BLE_PROVIDER)
                {
                    obj = nil;
                    [self.providers removeObject:obj];
                }
            }];
        }
        else if (type == SENSOR_PROVIDER){
            [self.providers enumerateObjectsUsingBlock:^(SensorMeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
                if (obj.type == SENSOR_PROVIDER)
                {
                    obj = nil;
                    [self.providers removeObject:obj];
                }
            }];
        }
        else{
            NSLog(@"Unrecognized provider type");
        }
    }
}




#pragma mark - Work with Beacon

-(void)addUUID:(NSString*)uuid{
    
    
    [self.beaconsUUIDs addObject:uuid];
    
    
}


-(void)setBeaconConfig:(BeaconConfig*) config{
    if([[self.config objectForKey:@"bleKalmanFilter"] boolValue]||[[self.config objectForKey:@"sensorKalman"] boolValue])
    {
        std::string uuid = std::string([config.uuid UTF8String]);
        KalmanBridge_initBeacon(uuid,(int) config.major, (int)config.minor, config.txPower, config.damp, config.x, config.y, config.z);
    }
    else{
        std::string uuid = std::string([config.uuid UTF8String]);
        BluetoothBridge_initBeacon(uuid,(int) config.major, (int)config.minor, config.txPower, config.damp, config.x, config.y, config.z);
    }
    
    
}
-(void)setMode:(IndoorLocationManagerMode)mode{
    self.managerMode = mode;
    
    
    
}

-(void)_createMesh:(IndoorLocationManagerMode)type{
    double nx = [[self.config objectForKey:@"nx"] floatValue], ny = [[self.config objectForKey:@"ny"] floatValue];
    double dx = [[self.config objectForKey:@"dx"] floatValue], dy =  [[self.config objectForKey:@"dy"] floatValue];
    double x0 =  [[self.config objectForKey:@"x0"] floatValue], y0 =  [[self.config objectForKey:@"y0"] floatValue];
    
    
    NSArray *masktableOut = [self.config objectForKey:@"mask"];
    std::vector<int> buffer(masktableOut.count);
    for (int i = 0; i < masktableOut.count; i++) {
        buffer[i] = [[masktableOut objectAtIndex:i] intValue];
    }
    if (type == SENSOR_MODE)
    {
        SensorBridge_createMesh(nx, ny, dx, dy, x0, y0);
        SensorBridge_setMaskTable(buffer);
    }
    else if (type == BLE_MODE){
        BluetoothBridge_createMesh(nx, ny, dx, dy, x0, y0);
        BluetoothBridge_setMaskTable(buffer);
    }
    
}
-(void)setGraph:(IndoorLocationManagerMode)type{
    
    if (type == BLE_MODE)
    {
        std::string graphConfig = std::string([[self.config objectForKey:@"graph"] UTF8String]);
        double scale = [[self.config objectForKey:@"scale"] floatValue];
        try {
            BluetoothBridge_readGraph(graphConfig, scale);
        } catch (const std::runtime_error& error) {
            NSLog(@"Exception: invalid  Graph");
        }
    }
    if (type == SENSOR_MODE)
    {
        std::string graphConfig = std::string([[self.config objectForKey:@"graph"] UTF8String]);
        double scale = [[self.config objectForKey:@"scale"] floatValue];
        try {
            SensorBridge_readGraph(graphConfig, scale);
        } catch (const std::runtime_error& error) {
            NSLog(@"Exception: invalid  Graph");
        }
    }
}
#pragma Set Config
-(void)setConfiguration:(NSDictionary*) config{
    self.config = config;
    
}

#pragma mark - Get Coordinates
-(void)getCoordinates{
    
    NSMutableArray *coordinates = [NSMutableArray new];
    double outPosition[] = {0.0, 0.0, 0.0};
    if (self.managerMode == SENSOR_MODE)
    {
        
        if([[self.config objectForKey:@"sensorRSSIAveraging"] boolValue])
        {
            if (!_initSensorNavigator)
            {
                for (int i = 0; i < 3; i++)
                {
                    [coordinates addObject:@(outPosition[i])];
                    
                }
                [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
                BOOL initialise = BluetoothBridge_isInitialise();
                if (initialise)
                {
                    
                    double output[] = {-1.0, -1.0};
                    BluetoothBridge_getInitialisePosition(output);
                    
                    if(output[0] != -1.0 && output[1] != -1.0){
                        SensorBridge_init(output[0], output[1]);
                        self.initSensorNavigator = YES;
                        
                    }
                }
            }
            else{
                SensorBridge_getLastPosition(outPosition);
                for (int i = 0; i < 3; i++)
                {
                    [coordinates addObject:@(outPosition[i])];
                    
                }
                [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
            }
        }
        else if([[self.config objectForKey:@"sensorKalman"] boolValue])
        {
            if (!_initSensorNavigator)
            {
                for (int i = 0; i < 3; i++)
                {
                    [coordinates addObject:@(outPosition[i])];
                    
                }
                [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
                BOOL initialise = KalmanBridge_isInitialise();
                if (initialise)
                {
                    
                    double output[] = {-1.0, -1.0};
                    KalmanBridge_getInitialisePosition(output);
                    
                    if(output[0] != -1.0 && output[1] != -1.0){
                        SensorBridge_init(output[0], output[1]);
                        self.initSensorNavigator = YES;
                        
                    }
                }
            }
            else{
                SensorBridge_getLastPosition(outPosition);
                for (int i = 0; i < 3; i++)
                {
                    [coordinates addObject:@(outPosition[i])];
                    
                }
                [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
            }

        }
        else{
            SensorBridge_getLastPosition(outPosition);
            for (int i = 0; i < 3; i++)
            {
                [coordinates addObject:@(outPosition[i])];
                
            }
            [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
        }
    }
    else if (self.managerMode == BLE_MODE){
        if([[self.config objectForKey:@"bleKalmanFilter"] boolValue]){
            
            KalmanBridge_getLastPosition(outPosition);
            
            for (int i = 0; i < 3; i++)
            {
                [coordinates addObject:@(outPosition[i])];
                
            }
            [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
        }
        else
        {
            BluetoothBridge_getLastPosition(outPosition);
            
            for (int i = 0; i < 3; i++)
            {
                [coordinates addObject:@(outPosition[i])];
                
            }
            [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
        }
    }
    //    else if (self.managerMode == FILTER_MODE){
    //
    //    }
    
    
    
}


#pragma mark - Get Routing
-(void)setDectinationPosition:(NSArray*)destination
{
    if([[self.config objectForKey:@"bleKalmanFilter"] boolValue]){
        
        if (_isRouting)
        {
            kalmanPosition p;
            p.x = [[destination objectAtIndex:0] doubleValue];
            p.y = [[destination objectAtIndex:1] doubleValue];
            //p.z = [[destination objectAtIndex:2] doubleValue];
            KalmanBridge_setDestination(p);
        }
        
        else{
            NSLog(@"Set isRouting first");
        }
    }
    else{
        if (_isRouting)
        {
            IndoorPosition p;
            p.x = [[destination objectAtIndex:0] doubleValue];
            p.y = [[destination objectAtIndex:1] doubleValue];
            //p.z = [[destination objectAtIndex:2] doubleValue];
            BluetoothBridge_setDestination(p);
        }
        
        else{
            NSLog(@"Set isRouting first");
        }
    }
}
-(NSMutableArray*)getRouting{
    if (_isRouting)
    {
        if (self.managerMode == BLE_MODE)
        {
            if([[self.config objectForKey:@"bleKalmanFilter"] boolValue])
            {
                NSMutableArray *routCoordinates = [NSMutableArray new];
                
                std::vector<IndoorPosition> way;
                
                for (int i = 0; i < way.size(); i++)
                {
                    IndoorPosition p = way[i];
                    NSDictionary* coordinate = [NSDictionary dictionaryWithObjectsAndKeys:
                                                @(p.x),@"x",
                                                @(p.y),@"y",
                                                @(p.z),@"z",nil];
                    
                    [routCoordinates addObject:coordinate];
                }
                
                return routCoordinates;
            }
            
            else {
                
                
                NSMutableArray *routCoordinates = [NSMutableArray new];
                
                std::vector<IndoorPosition> way;
                
                
                BluetoothBridge_getPositionFromGraph(way);
                for (int i = 0; i < way.size(); i++)
                {
                    IndoorPosition p = way[i];
                    NSDictionary* coordinate = [NSDictionary dictionaryWithObjectsAndKeys:
                                                @(p.x),@"x",
                                                @(p.y),@"y",
                                                @(p.z),@"z",nil];
                    
                    [routCoordinates addObject:coordinate];
                }
                
                return routCoordinates;
            }
        }
        else if(self.managerMode == SENSOR_MODE)
        {
            NSMutableArray *routCoordinates = [NSMutableArray new];
            
            std::vector<position> way;
            
            
            SensorBridge_getPositionFromGraph(way);
            for (int i = 0; i < way.size(); i++)
            {
                position p = way[i];
                NSDictionary* coordinate = [NSDictionary dictionaryWithObjectsAndKeys:
                                            @(p.x),@"x",
                                            @(p.y),@"y",
                                            @(p.z),@"z",nil];
                
                [routCoordinates addObject:coordinate];
            }
            return routCoordinates;
        }
        else
        {
            return nil;
        }
    }
    
    else
    {
        NSLog(@"Set isRouting first");
        
        return nil;
    }
}
-(CGFloat)getDistance{
    double dist = BluetoothBridge_getDistance();
    return dist;
}
#pragma mark - Action

-(void) prepare{
    if (self.managerMode == SENSOR_MODE)
    {
        [self setGraph:SENSOR_MODE];
        [self _createMesh:SENSOR_MODE];
        
        if ([[self.config objectForKey:@"sensorInitManual"] boolValue])
        {
            
            SensorBridge_setAccelConfig([[self.config objectForKey:@"orientationAngle"] intValue], true, [[self.config objectForKey:@"sensorMap"] boolValue], [[self.config objectForKey:@"sensorWalls"] boolValue], [[self.config objectForKey:@"sensorMesh"] boolValue]);
            double x = [[self.config objectForKey:@"x"] floatValue];
            double y = [[self.config objectForKey:@"y"] floatValue];
            NSLog(@"sensorInitManual Init X ---- %f",x);
            NSLog(@"sensorInitManual Init Y ----%f",y);
            SensorBridge_init(x, y);
            
        }
        
        else if([[self.config objectForKey:@"sensorRSSIAveraging"] boolValue]){
            SensorBridge_setAccelConfig([[self.config
                                          objectForKey:@"orientationAngle"] intValue], true, [[self.config objectForKey:@"sensorMap"] boolValue], [[self.config objectForKey:@"sensorWalls"] boolValue], [[self.config objectForKey:@"sensorMesh"] boolValue]);
            
            BluetoothBridge_setConfig(true, false, true, false);
            BluetoothBridge_init();
            
        }
        else if([[self.config objectForKey:@"sensorKalman"] boolValue]){
            SensorBridge_setAccelConfig([[self.config
                                          objectForKey:@"orientationAngle"] intValue], true, [[self.config objectForKey:@"sensorMap"] boolValue], [[self.config objectForKey:@"sensorWalls"] boolValue], [[self.config objectForKey:@"sensorMesh"] boolValue]);
            
            KalmanBridge_setConfig(true, false, true, false);
            KalmanBridge_init();
        }
        
    }
    else if (self.managerMode == BLE_MODE){
        [self setGraph:BLE_MODE];
        [self _createMesh:BLE_MODE];
        if([[self.config objectForKey:@"bleKalmanFilter"] boolValue])
        {

        KalmanBridge_setConfig([[self.config objectForKey:@"bleCircleBuffers"] boolValue], [[self.config objectForKey:@"bleTrilatiration"] boolValue], [[self.config objectForKey:@"bleMap"] boolValue], [[self.config objectForKey:@"bleMesh"] boolValue]);
        KalmanBridge_init();
        }
        
      else {
            
            BluetoothBridge_setConfig([[self.config objectForKey:@"bleCircleBuffers"] boolValue], [[self.config objectForKey:@"bleTrilatiration"] boolValue], [[self.config objectForKey:@"bleMap"] boolValue], [[self.config objectForKey:@"bleMesh"] boolValue]);
            BluetoothBridge_init();
        }
    }
    else if (self.managerMode == FILTER_MODE){
        BluetoothBridge_init();
    }
    
    
}

-(void) start{
    if(self.providers.count > 0){
        self.startProviderFlag = YES;
        [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
            [obj start];
            if (obj.type == BLE_PROVIDER)
            {
                
                
                
                self.timer = [NSTimer scheduledTimerWithTimeInterval:self.time
                                                              target:self
                                                            selector:@selector(getCoordinates)
                                                            userInfo:nil
                                                             repeats:YES];
            }
            else  if (obj.type == SENSOR_PROVIDER)
            {
                
                
                
                self.timer = [NSTimer scheduledTimerWithTimeInterval:self.time
                                                              target:self
                                                            selector:@selector(getCoordinates)
                                                            userInfo:nil
                                                             repeats:YES];
            }}];
    }
    else{
        
        NSLog(@"Add the provider before calls the start method");
    }
    
    
}

-(void) stop{
    self.initSensorNavigator = NO;
    self.startProviderFlag = NO;
    [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
        [obj stop];
        if (obj.type == BLE_PROVIDER)
        {
            [self.timer  invalidate];
            self.timer = nil;
        }
        if (obj.type == SENSOR_PROVIDER)
        {
            [self.timer  invalidate];
            self.timer = nil;
            if([[self.config objectForKey:@"sensorRSSIAveraging"] boolValue]||[[self.config objectForKey:@"sensorKalman"] boolValue]){
                BluetoothBridge_stop();
                KalmanBridge_stop();
            }
        }
    }];
    
}

-(void)deleteMesh{
    
    
    BluetoothBridge_realeseMesh();
}

#pragma mark - IosMeasurementTransferDelegate



-(void)processEvent: (MeasurementEvent *) event{
    if (event.type == BLE_VALUE)
    {
        
        if([[self.config objectForKey:@"bleKalmanFilter"] boolValue]||[[self.config objectForKey:@"sensorKalman"] boolValue])
        {
            double timestamp = event.timestamp;
            __block std::vector<Navigator::Beacons::BeaconReceivedData> bleBeacons;
            [event.beacons enumerateObjectsUsingBlock:^(CLBeacon*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                std::string uuid = std::string([[NSString stringWithFormat:@"%@", obj.proximityUUID] UTF8String]);
                Navigator::Beacons::BeaconUID uidStr(uuid,[obj.major intValue],[obj.minor intValue]);
                Navigator::Beacons::BeaconReceivedData brd(timestamp, uidStr,obj.rssi);
                bleBeacons.push_back(brd);
            }];
            KalmanBridge_process(bleBeacons);
            
        }
        else
        {
            double timestamp = event.timestamp;
            __block std::vector<Navigator::Beacons::BeaconReceivedData> bleBeacons;
            [event.beacons enumerateObjectsUsingBlock:^(CLBeacon*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                std::string uuid = std::string([[NSString stringWithFormat:@"%@", obj.proximityUUID] UTF8String]);
                Navigator::Beacons::BeaconUID uidStr(uuid,[obj.major intValue],[obj.minor intValue]);
                
                    Navigator::Beacons::BeaconReceivedData brd(timestamp, uidStr,obj.rssi);
                    bleBeacons.push_back(brd);

                
            }];
            BluetoothBridge_process(bleBeacons);
            
            
        }
        
        
        
        if (self.isStartLog)
        {
            double timestamp = event.timestamp;
            NSString *time = [NSString stringWithFormat:@"%.3f",(timestamp -  self.startTimestamp)];
            
            NSDictionary *data = [NSDictionary dictionaryWithObjectsAndKeys:
                                  @([time floatValue]),@"timestamp",
                                  @([event.beacon.major intValue]),@"major",
                                  @([event.beacon.minor intValue]),@"minor",
                                  @(event.beacon.proximity),@"proximity",
                                  [event.beacon.proximityUUID UUIDString],@"proximityUUID",
                                  @(event.beacon.accuracy),@"accuracy",
                                  @(event.beacon.rssi),@"rssi",nil];
            if(data){
                [self.beaconLogs addObject:data];
            }
        }
    }
    if (event.type == SENSOR_VALUE)
    {
        
        float azimuth = (RADIANS_TO_DEGREES(event.motion.attitude.yaw))-0 +90;
        
        if (azimuth > 180) {
            azimuth =  -360 +azimuth;
        }
        else if (azimuth < -180){
            azimuth =  360 +azimuth;
        }
        
        SensorBridge_process(event.timestamp, (event.accelerometerData.acceleration.x * -1), (event.accelerometerData.acceleration.y * -1), (event.accelerometerData.acceleration.z * -1), RADIANS_TO_DEGREES(event.motion.attitude.pitch),  azimuth,  RADIANS_TO_DEGREES(event.motion.attitude.roll));
        if (self.isStartLog)
            
        {
            if(self.initSensorNavigator){
                NSDictionary *data = [NSDictionary dictionaryWithObjectsAndKeys:
                                      @(event.timestamp),@"timestamp",
                                      @(event.accelerometerData.acceleration.x),@"x",
                                      @(event.accelerometerData.acceleration.y),@"y",
                                      @(event.accelerometerData.acceleration.z),@"z",
                                      nil];
                if(data){
                    [self.acselLogs addObject:data];
                }
                
                
                
                NSDictionary *dataMouting = [NSDictionary dictionaryWithObjectsAndKeys:
                                             @(event.timestamp),@"timestamp",
                                             @( RADIANS_TO_DEGREES(event.motion.attitude.pitch)),@"pitch",
                                             @(azimuth),@"yaw",
                                             @( RADIANS_TO_DEGREES(event.motion.attitude.roll)),@"roll",nil];
                if(dataMouting){
                    [self.moutingLogs addObject:dataMouting];
                }
            }
        }
        
    }
}


#pragma mark - Error


-(void)processError:(IndoorError *)error{
    
    [self.errorListener getError:error];
    
    
}


#pragma mark - Logger

-(NSArray*)getLog{
    
    NSArray *indoorLogs = [NSArray arrayWithObjects:[self.acselLogs copy],[self.moutingLogs copy],[self.beaconLogs copy],nil];
    [self.acselLogs removeAllObjects];
    [self.moutingLogs removeAllObjects];
    [self.beaconLogs removeAllObjects];
    
    return indoorLogs;
}




@end
