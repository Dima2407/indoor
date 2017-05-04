//
//  ViewController.m
//  IdoorSample
//
//  Created by AppleFace on 04.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "ViewController.h"
#import "IndoorLocationManager.h"



@interface ViewController ()<IndoorLocationListener,ErrorListener>
@property (weak, nonatomic) IBOutlet UISwitch *loggerSwitch;
@property (nonatomic, strong)IndoorLocationManager *manager;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    BeaconConfig *firstBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48049 txPower:-71.2 damp:2 andX:4.5 andY:0.0 andZ:2.3];
    BeaconConfig *forthBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48050 txPower:-71.2 damp:2 andX:0.0 andY:3.7 andZ:2.6];

    BeaconConfig *thirdBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48051 txPower:-71.2 damp:2 andX:3 andY:12.8 andZ:2.3];
    BeaconConfig *secondBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48052 txPower:-71.2 damp:2 andX:0.3 andY:9.9 andZ:2.6];



    self.manager = [[IndoorLocationManager alloc] init];
    self.manager.locationListener = self;
    self.manager.errorListener = self;
    [self.manager addUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF"];
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
#pragma mark - ErrorListenerProtocol
-(void)getError:(IndoorError *)error{
    NSLog(@"error: %@", error.error.description);
}

#pragma mark - Action


- (IBAction)start:(UIButton *)sender {
    //[self.pr start];
  [self.manager start];
    if (self.loggerSwitch.on)
    {
        self.manager.isStartLog = YES;
    }
    else{
        self.manager.isStartLog = NO;
    }
}
- (IBAction)stop:(UIButton *)sender {
    [self.manager stop ];
    if (self.manager.isStartLog)
    {
        [self sendLogs];
    }
}

- (IBAction)record:(UISwitch *)sender {
    if (sender.on){
         self.manager.isStartLog = YES;
    }
    else{
         self.manager.isStartLog = NO;
    }
   
}



#pragma mark - Logging
-(void)sendLogs{
    NSError *error = nil;
   
    
    NSData *jsonIndoorData = [NSJSONSerialization dataWithJSONObject:[self.manager getLog] options:NSJSONReadingAllowFragments error:&error];
    
    NSString *documentsDirectory = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    
    
        NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
        [dateFormatter setDateFormat:@"yyyy-MM-dd_hh-mm-ss_"];
        NSDate *date = [NSDate date];
        [dateFormatter stringFromDate:date];
    
    
    
    NSString *path = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"/%@IndoorLogs.txt",[dateFormatter stringFromDate:date]]];
    [jsonIndoorData writeToFile:path atomically:YES];
    NSURL *filePath = [NSURL fileURLWithPath:path];
    NSArray *activity =[NSArray arrayWithObject:filePath];
    UIActivityViewController* activityViewController =
    [[UIActivityViewController alloc] initWithActivityItems:activity
                                      applicationActivities:nil];
    
 
    
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        NSLog(@"iPad");
        
        UIPopoverController* pop =  [[UIPopoverController alloc] initWithContentViewController:activityViewController];
        [pop presentPopoverFromRect:CGRectMake(0, self.view.frame.size.height - 100, self.view.frame.size.width, 100) inView:self.view permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
    }
    else
    {
        NSLog(@"iPhone");
        
        
        
        activityViewController.completionHandler = ^(NSString *activityType, BOOL completed) {
            [self dismissViewControllerAnimated:YES completion:nil];
            
        };
        [activityViewController setValue:@"IndoorLogs" forKey:@"subject"];
        [self presentViewController:activityViewController animated:YES completion:nil];
        
    }
    

}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
