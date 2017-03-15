//
//  ViewController.m
//  IdoorSample
//
//  Created by AppleFace on 04.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "ViewController.h"
#import "GPSMeasurementProvider.h"
#import "BluetoothMeasurementProvider.h"
#import "BeaconConfig.h"
#import "BluethoothProviderConfiguration.h"

@interface ViewController ()
@property (nonatomic, strong)GPSMeasurementProvider *provider;
@property (nonatomic, strong) BluetoothMeasurementProvider *BLE;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //self.provider = [[GPSMeasurementProvider alloc]init ];
    self.BLE = [[BluetoothMeasurementProvider alloc] init];
    BeaconConfig *config1 = [[BeaconConfig alloc]initWithX:4.5 andY:0.3 andUUID:48049];
    BeaconConfig *config2 = [[BeaconConfig alloc]initWithX:4 andY:12.8 andUUID:48050];
    BeaconConfig *config3 = [[BeaconConfig alloc]initWithX:0.3 andY:9.9 andUUID:48051];
    BeaconConfig *config4 = [[BeaconConfig alloc]initWithX:0.3 andY:4.4 andUUID:48052];

    NSArray <BeaconConfig *> *beacons = [NSArray arrayWithObjects:config1,config2,config3, config4,nil];
    [BluethoothProviderConfiguration updateCinfiguration:beacons];
    
}

- (IBAction)start:(id)sender {
   //[self.provider start];
    [self.BLE start];
}
- (IBAction)stop:(id)sender {
   //[self.provider stop];
      [self.BLE stop];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
