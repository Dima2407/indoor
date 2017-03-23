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
#import "PrefixHeader.pch"

//#import "IosMeasurementTransfer.h"

@interface ViewController ()<IndoorLocationListener,ErrorListener>
@property (nonatomic, strong)IndoorLocationManager *manager;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    BeaconConfig *firstBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48049 txPower:-68.3 damp:0.2 andX:4.5 andY:0.0 andZ:2.3];
    BeaconConfig *forthBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48050 txPower:-68.3 damp:0.2 andX:0.0 andY:3.7 andZ:2.6];

    BeaconConfig *thirdBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48051 txPower:-68.3 damp:0.2 andX:3 andY:12.8 andZ:2.3];
    BeaconConfig *secondBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48052 txPower:-68.3 damp:0.2 andX:0.3 andY:9.9 andZ:2.6];



    self.manager = [[IndoorLocationManager alloc] init];
    self.manager.locationListener = self;
   self.manager.errorListener = self;
    [self.manager addProvider:BLE_PROVIDER];
    [self.manager setBeaconConfig:firstBeacon];
    [self.manager setBeaconConfig:secondBeacon];
    [self.manager setBeaconConfig:thirdBeacon];
     [self.manager setBeaconConfig:forthBeacon];


    


    
}

#pragma mark - IndoorLocationListenerProtocol

-(void)onLocation:(NSArray *)coordinte{
    
    NSLog(@"%@",coordinte);
}
-(void)getError:(IndoorError *)error{
    NSLog(@"error: %@", error.error.description);
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
