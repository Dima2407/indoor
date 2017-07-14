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
#import "SensorBridge.h"
#import "IndoorError.h"



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
    std::string uuid = std::string([config.uuid UTF8String]);
    BluetoothBridge_initBeacon(uuid,(int) config.major, (int)config.minor, config.txPower, config.damp, config.x, config.y, config.z);
    
    
}
-(void)setMode:(IndoorLocationManagerMode)mode{
    self.managerMode = mode;
    

    
}

-(void)setMeshConfig:(NSArray*)meshIn andOut:(NSArray*) masktableOut{
    switch (self.managerMode) {
        case STANDART_MODE:
            NSLog(@"You can't add config in STANDART_MODE");
            
            break;
            
            case MESH_MODE:
            [self _createMesh:meshIn andOut:masktableOut type:MESH_MODE];
            break;
        case SENSOR_MODE:
             [self _createMesh:meshIn andOut:masktableOut type:SENSOR_MODE];
            
            break;


    }

}
-(void)_createMesh:(NSArray*)meshIn andOut:(NSArray*) masktableOut type:(IndoorLocationManagerMode)type{
    double nx = [[meshIn objectAtIndex:0] intValue], ny = [[meshIn objectAtIndex:1] intValue];
    double dx =[[meshIn objectAtIndex:2] doubleValue], dy = [[meshIn objectAtIndex:3] doubleValue];
    double x0 = [[meshIn objectAtIndex:4] doubleValue], y0 = [[meshIn objectAtIndex:5] doubleValue];
    if (type == SENSOR_MODE)
    {
        SensorBridge_createMesh(nx, ny, dx, dy, x0, y0);
    }
    else if (type == MESH_MODE){
        BluetoothBridge_createMesh(nx, ny, dx, dy, x0, y0);
    }
    
    
    std::vector<int> buffer(masktableOut.count);
    for (int i = 0; i < masktableOut.count; i++) {
        buffer[i] = [[masktableOut objectAtIndex:i] intValue];
    }
    if (type == SENSOR_MODE)
    {
      SensorBridge_setMaskTable(buffer);
    }
    else if (type == MESH_MODE){
        BluetoothBridge_setMaskTable(buffer);
    }
    
}
-(void)setGraph:(NSString*)graph and:(CGFloat) scale;{
    if (graph == nil)
    {
        NSLog(@" Graph is nil");
    }
    else{
    std::string graphConfig = std::string([graph UTF8String]);
        try {
            BluetoothBridge_readGraph(graphConfig, (double)scale);
        } catch (const std::runtime_error& error) {
             NSLog(@"Exception: invalid  Graph");
        }
    }
}

#pragma mark - Get Coordinates
-(void)getCoordinates{
    
    NSMutableArray *coordinates = [NSMutableArray new];
    double outPosition[] = {0.0, 0.0, 0.0};
    if (self.managerMode == SENSOR_MODE)
    {
        if (!_initSensorNavigator)
        {
        BOOL initialise = BluetoothBridge_isInitialise();
        if (initialise)
        {
            SensorBridge_setAccelConfig(0, true);
            double output[] = {-1.0, -1.0};
            BluetoothBridge_getInitialisePosition(output);
            if(output[0] != -1.0 && output[1] != -1.0){
               // SensorBridge_init(output[0], output[1]);
                SensorBridge_init(3, 13);
                self.initSensorNavigator = YES;
            }
        }
        }
        else{
        SensorBridge_getLastPosition(outPosition);
        }
    }
    else if (self.managerMode == MESH_MODE){
        BluetoothBridge_getLastPosition(outPosition);
    }
    else if (self.managerMode == STANDART_MODE){
        BluetoothBridge_getLastPosition(outPosition);
    }
    for (int i = 0; i < 3; i++)
    {
        [coordinates addObject:@(outPosition[i])];
        
        
    }
    [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
    
}


#pragma mark - Get Routing
-(void)setDectinationPosition:(NSArray*)destination
{
    if (_isRouting)
    {
        position p;
        p.x = [[destination objectAtIndex:0] doubleValue];
        p.y = [[destination objectAtIndex:1] doubleValue];
        //p.z = [[destination objectAtIndex:2] doubleValue];
        BluetoothBridge_setDestination(p);
          }
    
    else{
        NSLog(@"Set isRouting first");
    }
}
-(NSMutableArray*)getRouting{
    if (_isRouting)
    {
    NSMutableArray *routCoordinates = [NSMutableArray new];
   
    std::vector<position> way;
    
    
    BluetoothBridge_getPositionFromGraph(way);
    for (int i = 0; i < way.size(); i++) {
        position p = way[i];
        NSDictionary* coordinate = [NSDictionary dictionaryWithObjectsAndKeys:
                              @(p.x),@"x",
                              @(p.y),@"y",
                              @(p.z),@"z",nil];

        [routCoordinates addObject:coordinate];
    }

    return routCoordinates;
    }
    
    else{
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
        BluetoothBridge_init();
    }
    else if (self.managerMode == MESH_MODE){
         BluetoothBridge_init();
    }
    else if (self.managerMode == STANDART_MODE){
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
                }}];
    }
    else{
        
        NSLog(@"Add the provider before calls the start method");
    }
   
    
}

-(void) stop{
    
    self.startProviderFlag = NO;
    [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
        [obj stop];
        if (obj.type == BLE_PROVIDER)
        {
            [self.timer  invalidate];
            self.timer = nil;
     
        }}];
}

-(void)deleteMesh{
    
    
    BluetoothBridge_realeseMesh();
}

#pragma mark - IosMeasurementTransferDelegate



-(void)processEvent: (MeasurementEvent *) event{
    if (event.type == BLE_VALUE)
    {
        std::string uuid = std::string([[NSString stringWithFormat:@"%@", event.beacon.proximityUUID] UTF8String]);
        double timestamp = event.timestamp;
        BluetoothBridge_proces(timestamp, uuid, [event.beacon.major intValue], [event.beacon.minor intValue], event.beacon.rssi);
        
        
    if (self.isStartLog)
    {
        NSString *time = [NSString stringWithFormat:@"%.3f",(timestamp -  self.startTimestamp)];

        NSDictionary *data = [NSDictionary dictionaryWithObjectsAndKeys:
                              @([time floatValue]),@"timestamp",
                              @([event.beacon.major intValue]),@"major",
                              @([event.beacon.minor intValue]),@"minor",
                              @(event.beacon.proximity),@"proximity",
                              [event.beacon.proximityUUID UUIDString],@"proximityUUID",
                              @(event.beacon.accuracy),@"accuracy",
                              @(event.beacon.rssi),@"rssi",nil];
        [self.beaconLogs addObject:data];
    }
  }
    if (event.type == SENSOR_VALUE)
    {
        float azimuth = (RADIANS_TO_DEGREES(event.motion.attitude.yaw))+90;
        
        if (azimuth > 180) {
            azimuth = azimuth -360;
        }
        SensorBridge_proces(event.timestamp, event.accelerometerData.acceleration.x, event.accelerometerData.acceleration.y, event.accelerometerData.acceleration.z, RADIANS_TO_DEGREES(event.motion.attitude.pitch),  azimuth,  RADIANS_TO_DEGREES(event.motion.attitude.roll));
        if (self.isStartLog)
            
        {
            if(self.initSensorNavigator){
            NSDictionary *data = [NSDictionary dictionaryWithObjectsAndKeys:
                                  @(event.timestamp),@"timestamp",
                                  @(event.accelerometerData.acceleration.x),@"x",
                                  @(event.accelerometerData.acceleration.y),@"y",
                                  @(event.accelerometerData.acceleration.z),@"z",
                                  nil];
            [self.acselLogs addObject:data];
           
            
          
            
            NSDictionary *dataMouting = [NSDictionary dictionaryWithObjectsAndKeys:
                                         @(event.timestamp),@"timestamp",
                                         @( RADIANS_TO_DEGREES(event.motion.attitude.pitch)),@"pitch",
                                         @(azimuth),@"yaw",
                                         @( RADIANS_TO_DEGREES(event.motion.attitude.roll)),@"roll",nil];
             [self.moutingLogs addObject:dataMouting];
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
