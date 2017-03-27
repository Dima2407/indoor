//
//  IndoorLocationManager.m
//  IndoorLibrary
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "IndoorLocationManager.h"
#import "MeasurementProvider.h"
#import "BluetoothMeasurementProvider.h"
#import "GPSMeasurementProvider.h"
#import "BluetoothBridge.h"
#import "IndoorError.h"




@interface IndoorLocationManager()<IosMeasurementTransferDelegate>
@property (nonatomic, strong) NSMutableArray *logs;
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
        self.logs = [NSMutableArray new];
        
    }
    return self;
}

#pragma mark - Logic
    
-(void)addProvider:(MeasurementProviderType)type{
    MeasurementProvider * provider = nil;
    switch (type) {
        case GPS_PROVIDER:
            provider = [[GPSMeasurementProvider alloc] initWithTransfer: self.transfer];
            if(provider != nil){
             
                [self.providers addObject:provider];
            }

            break;
        case BLE_PROVIDER:
            provider = [[BluetoothMeasurementProvider alloc] initWithTransfer: self.transfer];
            if(provider != nil){
                   BluetoothBridge_init();
                [self.providers addObject:provider];
            }
            
            break;
        default:
            break;
    }
   }

-(void)removeProvider: (MeasurementProviderType) type{
    
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
                else{
                    NSLog(@"Unrecognized type");
                }
    
    }




#pragma mark - Work with Beacon


-(void)setBeaconConfig:(BeaconConfig*) config{
    std::string uuid = std::string([config.uuid UTF8String]);
    BluetoothBridge_initBeacon(uuid,(int) config.major, (int)config.minor, config.txPower, config.damp, config.x, config.y, config.z);
    
    
}

#pragma mark - Action


-(void) start{
    
    [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
        [obj start];
    }];
}

-(void) stop{
    [self.providers enumerateObjectsUsingBlock:^(MeasurementProvider*  _Nonnull obj, BOOL * _Nonnull stop) {
        [obj stop];
    }];
}



#pragma mark - IosMeasurementTransferDelegate



-(void)processEvent: (MeasurementEvent *) event{
    if (event.type == BLE_VALUE)
    {
        std::string uuid = std::string([[NSString stringWithFormat:@"%@", event.beacon.proximityUUID] UTF8String]);
        double time = event.timestamp;
        double outPosition[] = {0.0, 0.0, 0.0};
        BluetoothBridge_proces(time, uuid, [event.beacon.major intValue], [event.beacon.minor intValue], event.beacon.rssi, outPosition);
        NSMutableArray *coordinates = [NSMutableArray new];
       
        for (int i = 0; i < 3; i++)
        {
            [coordinates addObject:@(outPosition[i])];
          
            
            
        }
        [self.locationListener onLocation:[NSArray arrayWithArray:coordinates]];
        if (self.logger)
        {
            NSDictionary *data = [NSDictionary dictionaryWithObjectsAndKeys:
                                  @(time),@"timestamp",
                                  @([event.beacon.minor intValue]),@"minor",
                                  @(event.beacon.rssi),@"rssi",
                                  [NSString stringWithFormat:@"%@",[coordinates objectAtIndex:0]],@"X",
                                   [NSString stringWithFormat:@"%@",[coordinates objectAtIndex:1]],@"Y",
                                  [NSString stringWithFormat:@"%@",[coordinates objectAtIndex:2]],@"Z",
                                  nil];
            [self.logs addObject:data];
        }
    }
}


#pragma mark - Error


-(void)processError:(IndoorError *)error{
    
    [self.errorListener getError:error];
    
    
}


#pragma mark - Logger

-(NSMutableArray*)logging{
    
    
    return self.logs;
}




@end
