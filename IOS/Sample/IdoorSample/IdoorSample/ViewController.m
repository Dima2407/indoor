//
//  ViewController.m
//  IdoorSample
//
//  Created by AppleFace on 04.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "ViewController.h"
#import "GPSMeasurementProvider.h"

@interface ViewController ()
@property (nonatomic, strong)GPSMeasurementProvider *provider;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.provider = [[GPSMeasurementProvider alloc]init ];
 
}

- (IBAction)start:(id)sender {
    [self.provider start];
}
- (IBAction)stop:(id)sender {
    [self.provider stop];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
