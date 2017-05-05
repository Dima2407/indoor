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
    
    NSData *jsonIndoorData = [NSJSONSerialization dataWithJSONObject:[[BeaconManager sharedManager] getLogs] options:NSJSONWritingPrettyPrinted error:&error];
    
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
