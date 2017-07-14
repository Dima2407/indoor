//
//  MenuViewController.m
//  iosNavigation
//
//  Created by Ievgen on 16.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "MenuViewController.h"
#import "BeaconManager.h"

@interface MenuViewController () <UITableViewDelegate, UITableViewDataSource>


@end
static  NSString *kSettingsShowRadar = @"kSettingsShowRadar";
static  NSString *kSettingsShowPoi = @"kSettingsShowPoi";
static  NSString *kSettingsUseMesh = @"kSettingsUseMesh";
static  NSString *kSettingsframeOnLogs = @"kSettingsframeOnLogs";

@implementation MenuViewController


#pragma mark - Viewcontroller life cycle
-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [[BeaconManager sharedManager] stopBeacon];
    
    
    BOOL radar= [[NSUserDefaults standardUserDefaults] boolForKey:kSettingsShowRadar];
    [self.showRadar setOn:radar animated:YES];
    BOOL mesh= [[NSUserDefaults standardUserDefaults] boolForKey:kSettingsUseMesh];
    [self.useMesh setOn:mesh animated:YES];
    BOOL poi= [[NSUserDefaults standardUserDefaults] boolForKey:kSettingsShowPoi];
    [self.showPOI setOn:poi animated:YES];
    BOOL log= [[NSUserDefaults standardUserDefaults] boolForKey:kSettingsframeOnLogs];
    [self.onLogs setOn:log animated:YES];
    self.sendLogButton.userInteractionEnabled = log;
    
}
//-(void)viewWillDisappear:(BOOL)animated{
//    [super viewWillDisappear:animated];
//    if ([[BeaconManager sharedManager] status])
//    {
//         [[BeaconManager sharedManager] startBeacon];
//    }
//}

-(void)viewDidLoad{
    [super viewDidLoad];
    
}
#pragma mark - Action
- (IBAction)sendLogs:(UIButton *)sender {
    NSError *error = nil;
     NSArray *log = [[BeaconManager sharedManager] getLogs];
    NSData *jsonSensorsAccelerometer = [NSJSONSerialization dataWithJSONObject:[log objectAtIndex:0] options:NSJSONWritingPrettyPrinted error:&error];
   
    NSData *anglesSensors = [NSJSONSerialization dataWithJSONObject:[log objectAtIndex:1] options:NSJSONWritingPrettyPrinted error:&error];
    
    NSData *position = [NSJSONSerialization dataWithJSONObject:[log objectAtIndex:3] options:NSJSONWritingPrettyPrinted error:&error];
    NSData *beacons = [NSJSONSerialization dataWithJSONObject:[self _sortBeacons:[log objectAtIndex:2]] options:NSJSONWritingPrettyPrinted error:&error];
 
    NSString *documentsDirectory = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd_hh-mm-ss_"];
    NSDate *date = [NSDate date];
    [dateFormatter stringFromDate:date];
    
    
    
    NSString *path = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@iOS_accelerometer.json",[dateFormatter stringFromDate:date]]];
    NSString *pathAngles = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@iOS_angles.json",[dateFormatter stringFromDate:date]]];
    NSString *pos = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@iOS_posotion.json",[dateFormatter stringFromDate:date]]];
    NSString *bea = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@iOS_beacon.json",[dateFormatter stringFromDate:date]]];
    [jsonSensorsAccelerometer writeToFile:path atomically:YES];
    NSURL *filePath = [NSURL fileURLWithPath:path];
    [anglesSensors writeToFile:pathAngles atomically:YES];
    NSURL *filePath1 = [NSURL fileURLWithPath:pathAngles];
    [position writeToFile:pos atomically:YES];
    NSURL *filePath2 = [NSURL fileURLWithPath:pos];
    [beacons writeToFile:bea atomically:YES];
    NSURL *filePath3 = [NSURL fileURLWithPath:bea];
    NSArray *activity =[NSArray arrayWithObjects:filePath1, filePath, filePath2,filePath3, nil];
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
-(NSArray*)_sortBeacons:(NSArray*)beacons{
    NSMutableDictionary *arrays = [NSMutableDictionary new];
    for (NSDictionary *beacon in beacons)
    {
        NSString *beaconMinor = [beacon objectForKey:@"minor"];
        if (![arrays objectForKey:beaconMinor])
        {
            NSMutableArray *array = [[NSMutableArray alloc]initWithObjects:beacon,nil];
            [arrays setObject:array forKey:[beacon objectForKey:@"minor"]];
        }
        else
        {
            NSMutableArray *array = [arrays objectForKey:beaconMinor];
            [array addObject:beacon];
            [arrays setObject:array forKey:beaconMinor];
        }
        
    }

    NSMutableArray *ar = [NSMutableArray new];
    for (NSString * str in [arrays allKeys])
    {
        [ar addObject:[arrays objectForKey:str]];
    }
    return [ar copy];
}

- (IBAction) switchChanged:(UISwitch *)sender {
    if([sender isEqual:self.showRadar]){
        
       
    [[NSUserDefaults standardUserDefaults] setBool:self.showRadar.on forKey:kSettingsShowRadar];
       
    }
    if([sender isEqual:self.useMesh]){
        [[NSUserDefaults standardUserDefaults] setBool:self.useMesh.on forKey:kSettingsUseMesh];
       
    }
    if([sender isEqual:self.showPOI]){
        
        [[NSUserDefaults standardUserDefaults] setBool:self.showPOI.on forKey:kSettingsShowPoi];
    }
    if([sender isEqual:self.onLogs]){
        
        [[NSUserDefaults standardUserDefaults] setBool:self.onLogs.on forKey:kSettingsframeOnLogs];
        self.sendLogButton.userInteractionEnabled = self.onLogs.on;
    }



}




@end
