//
//  ViewController.m
//  IdoorSample
//
//  Created by AppleFace on 04.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "ViewController.h"
#import "BeaconConfig.h"
#import "IndoorLocationManager.h"
#import "BluetoothMeasurementProvider.h"
#import "IosMeasurementTransfer.h"
#import "GPSMeasurementProvider.h"

@interface ViewController ()<IndoorLocationListener>
@property (nonatomic, strong)IndoorLocationManager *manager;
@property (nonatomic, strong) BluetoothMeasurementProvider *pr;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    BeaconConfig *firstBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48049 txPower:-25 damp:2 andX:4.5 andY:0.3 andZ:0];
     BeaconConfig *secondBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48052 txPower:-37.5 damp:2 andX:0.3 andY:9.9 andZ:0];
     BeaconConfig *thirdBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48051 txPower:-25 damp:2 andX:4 andY:12.8 andZ:0];

    self.manager = [[IndoorLocationManager alloc] init];
    self.manager.locationListener = self;
   // self.manager.errorListener = self;
    [self.manager addProvider:BLE_PROVIDER];
    [self.manager setBeaconConfig:firstBeacon];
    [self.manager setBeaconConfig:secondBeacon];
    [self.manager setBeaconConfig:thirdBeacon];

//   self.manager = [[GPSMeasurementProvider alloc] init:[[IosMeasurementTransfer alloc] init]];
//    self.pr =[[BluetoothMeasurementProvider alloc] init:[[IosMeasurementTransfer alloc] init]];
    


    
}

#pragma mark - IndoorLocationListenerProtocol

-(void)onLocation:(NSArray *)coordinte{
    
    NSLog(@"%@",coordinte);
}

#pragma mark - Action


- (IBAction)start:(id)sender {
    //[self.pr start];
  [self.manager start];
}
- (IBAction)stop:(id)sender {
    [self.manager stop ];
    //[self.pr stop];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
