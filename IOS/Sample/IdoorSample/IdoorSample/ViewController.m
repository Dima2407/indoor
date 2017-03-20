//
//  ViewController.m
//  IdoorSample
//
//  Created by AppleFace on 04.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "ViewController.h"
//#import "GPSMeasurementProvider.h"
//#import "BluetoothMeasurementProvider.h"
//#import "BeaconConfig.h"
//#import "BluethoothProviderConfiguration.h"
#import "IndoorLocationManager.h"

@interface ViewController ()
//@property (nonatomic, strong)GPSMeasurementProvider *provider;
@property (nonatomic, strong) IndoorLocationManager *BLE;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
 // self.provider = [[GPSMeasurementProvider alloc]init ];
    self.BLE = [[IndoorLocationManager alloc] init];


    
}

- (IBAction)start:(id)sender {
  // [self.provider start];
   // [self.BLE prepare];
}
- (IBAction)stop:(id)sender {
  // [self.provider stop];
      //[self.BLE stop];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
