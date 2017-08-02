//
//  MenuViewController.m
//  iosNavigation
//
//  Created by Ievgen on 16.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "MenuViewController.h"
#import "BeaconManager.h"
#import "IndoorHeader.h"

@interface MenuViewController () <UITableViewDelegate, UITableViewDataSource>
@property (weak, nonatomic) IBOutlet UISwitch *APPBLECircleSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *BLEKalmanSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *BLEMapSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *BLEMeshSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *BLEWallsSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *BLETrilatirationSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *BLECircleSwitch;
@property (weak, nonatomic) IBOutlet UIView *BLESettingsView;
@property (weak, nonatomic) IBOutlet UITextField *xSensorTextField;
@property (weak, nonatomic) IBOutlet UITextField *ySensorTextField;
@property (weak, nonatomic) IBOutlet UISwitch *BLENavigationSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *SensorNavigationSwitch;

@property (weak, nonatomic) IBOutlet UISwitch *SensorManual;
@property (weak, nonatomic) IBOutlet UISwitch *SensorRSSIAveraging;
@property (weak, nonatomic) IBOutlet UIView *SensorSettingsView;
@property (weak, nonatomic) IBOutlet UISwitch *SensorMapCorrectionSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *SensorMeshCorrectionSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *SensorWallsCorrectionSwitch;

@end

@implementation MenuViewController


#pragma mark - Viewcontroller life cycle
-(void)viewWillAppear:(BOOL)animated{
        [super viewWillAppear:animated];
        [[BeaconManager sharedManager] stopBeacon];
        [[NSUserDefaults standardUserDefaults] setDouble:0.0 forKey:kSensorX];
        [[NSUserDefaults standardUserDefaults] setDouble:0.0 forKey:kSensorY];
        
        [self onSwitch];
        [self.xSensorTextField setKeyboardType:UIKeyboardTypeNumberPad];
        [self.ySensorTextField setKeyboardType:UIKeyboardTypeNumberPad];
        
        
        self.sendLogButton.userInteractionEnabled = log;
        
    }
    -(void)onSwitch{
        ///UI Switch
        BOOL radar = [[NSUserDefaults standardUserDefaults] boolForKey:kSettingsShowRadar];
        [self.showRadar setOn:radar animated:YES];
        BOOL poi = [[NSUserDefaults standardUserDefaults] boolForKey:kSettingsShowPoi];
        [self.showPOI setOn:poi animated:YES];
        
        ///Navigation Switch
        BOOL ble =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLENavigationSwitch];
        [self.BLENavigationSwitch setOn:ble animated:YES];
        BOOL sensor =  [[NSUserDefaults standardUserDefaults] boolForKey:kSensorNavigationSwitch];
        [self.SensorNavigationSwitch setOn:sensor animated:YES];
        
        ///BLE Switch
        if (ble)
        {
            BOOL circle =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLECircleSwitch];
            [self.BLECircleSwitch setOn:circle animated:YES];
            self.BLESettingsView.hidden = NO;
            BOOL trilat =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLETrilatirationSwitch];
            [self.BLETrilatirationSwitch setOn:trilat animated:YES];
            //    BOOL kalman =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEKalmanSwitch];
            //    [self.BLEKalmanSwitch setOn:kalman animated:YES];
            BOOL bleMap =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEMapSwitch];
            [self.BLEMapSwitch setOn:bleMap animated:YES];
            BOOL bleWall =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEWallsSwitch];
            [self.BLEWallsSwitch setOn:bleWall animated:YES];
            BOOL bleMesh =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEMeshSwitch];
            [self.BLEMeshSwitch setOn:bleMesh animated:YES];
        }
        ///Sensor Switch
        if (sensor)
        {
            BOOL sensorManual =  [[NSUserDefaults standardUserDefaults] boolForKey:kSensorManual];
            [self.SensorManual setOn:sensorManual animated:YES];
            BOOL sensorRssi =  [[NSUserDefaults standardUserDefaults] boolForKey:kSensorRSSIAveraging];
            [self.SensorRSSIAveraging setOn:sensorRssi animated:YES];
            self.SensorSettingsView.hidden = NO;
            //    BOOL sensorKalman =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEKalmanSwitch];
            //    [self.BLEKalmanSwitch setOn:sensorKalman animated:YES];
            BOOL sensorMap =  [[NSUserDefaults standardUserDefaults] boolForKey:kSensorMapCorrectionSwitch];
            [self.SensorMapCorrectionSwitch setOn:sensorMap animated:YES];
            BOOL sensorWall =  [[NSUserDefaults standardUserDefaults] boolForKey:kSensorWallsCorrectionSwitch];
            [self.SensorWallsCorrectionSwitch setOn:sensorWall animated:YES];
            BOOL sensorMesh =  [[NSUserDefaults standardUserDefaults] boolForKey:kSensorMeshCorrectionSwitch];
            [self.SensorMeshCorrectionSwitch setOn:sensorMesh animated:YES];
        }
    }
    - (IBAction)setCoordinate:(UIButton *)sender {
        [[NSUserDefaults standardUserDefaults] setDouble:[self.xSensorTextField.text floatValue ] forKey:kSensorX];
        [[NSUserDefaults standardUserDefaults] setDouble:[self.ySensorTextField.text floatValue ] forKey:kSensorY];
    }
    
    
    - (IBAction)addedX:(UITextField *)sender {
        [[NSUserDefaults standardUserDefaults] setDouble:[self.xSensorTextField.text floatValue ] forKey:kSensorX];
    }
    - (IBAction)addedY:(UITextField *)sender {
        [[NSUserDefaults standardUserDefaults] setDouble:[self.ySensorTextField.text floatValue ] forKey:kSensorY];
    }
    
    -(void)viewDidLoad{
        [super viewDidLoad];
        
    }
#pragma mark - Action
    
    - (IBAction)BLESwitchAction:(UISwitch *)sender {
        if([sender isOn]){
            self.BLESettingsView.hidden = NO;
            //self.ApplicationFiltersView.hidden = YES;
            [self.SensorNavigationSwitch setOn:NO animated:YES];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorNavigationSwitch];
            self.SensorSettingsView.hidden = YES;
        }
        else{
            self.BLESettingsView.hidden = YES;
        }
        [[NSUserDefaults standardUserDefaults] setBool:self.BLENavigationSwitch.on forKey:kBLENavigationSwitch];
        
        
    }
    - (IBAction)SensorSwitchAction:(UISwitch *)sender {
        if([sender isOn]){
            self.SensorSettingsView.hidden = NO;
            self.BLESettingsView.hidden = YES;
            [self.BLENavigationSwitch setOn:NO animated:YES];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLENavigationSwitch];
            // self.ApplicationFiltersView.hidden = YES;
        }
        else{
            self.SensorSettingsView.hidden = YES;
        }
        [[NSUserDefaults standardUserDefaults] setBool:self.SensorNavigationSwitch.on forKey:kSensorNavigationSwitch];
        
    }
//    - (IBAction)AplicationFilterSwitchAction:(UISwitch *)sender {
//        if([sender isOn]){
//            self.ApplicationFiltersView.hidden = NO;
//            self.BLESettingsView.hidden = YES;
//            self.BLESettingsView.hidden = YES;
//        }
//        else{
//            self.ApplicationFiltersView.hidden = YES;
//        }
//        self.BLESettingsView.hidden = YES;
//    }

    - (IBAction)BLESwitchChanged:(UISwitch *)sender {
        if([sender isEqual:self.BLECircleSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.BLECircleSwitch.on forKey:kBLECircleSwitch];
            [self.BLETrilatirationSwitch setOn:NO];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLETrilatirationSwitch];
            //        [self.BLEKalmanSwitch setOn:NO];
            //        [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEKalmanSwitch];
            
        }
        else if([sender isEqual:self.BLETrilatirationSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.BLETrilatirationSwitch.on forKey:kBLETrilatirationSwitch];
            [self.BLECircleSwitch setOn:NO];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLECircleSwitch];
            [self.BLEKalmanSwitch setOn:NO];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEKalmanSwitch];
        }
        else if([sender isEqual:self.BLEKalmanSwitch]){
        }
        else if([sender isEqual:self.BLEMapSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.BLEMapSwitch.on forKey:kBLEMapSwitch];
        }
        else if([sender isEqual:self.BLEMeshSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.BLEMeshSwitch.on forKey:kBLEMeshSwitch];
        }
        else if([sender isEqual:self.BLEWallsSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.BLEWallsSwitch.on forKey:kBLEWallsSwitch];
        }
        
        
    }
    - (IBAction)SensorSwitchChanged:(UISwitch *)sender {
        
        if([sender isEqual:self.SensorManual]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorManual.on forKey:kSensorManual];
            [self.SensorRSSIAveraging setOn:NO];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorRSSIAveraging];
            //        [self.SensorKalmanSwitch setOn:NO];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorKalmanSwitch];
            
        }
        else if([sender isEqual:self.SensorRSSIAveraging]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorRSSIAveraging.on forKey:kSensorRSSIAveraging];
            [self.SensorManual setOn:NO];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorManual];
            //        [self.BLEKalmanSwitch setOn:NO];
            //        [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEKalmanSwitch];
        }
        else if([sender isEqual:self.BLEKalmanSwitch]){
        }
        else if([sender isEqual:self.SensorMapCorrectionSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorMapCorrectionSwitch.on forKey:kSensorMapCorrectionSwitch];
        }
        else if([sender isEqual:self.SensorMeshCorrectionSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorMeshCorrectionSwitch.on forKey:kSensorMeshCorrectionSwitch];
        }
        else if([sender isEqual:self.SensorWallsCorrectionSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorWallsCorrectionSwitch.on forKey:kSensorWallsCorrectionSwitch];
        }
        
        
    }
    - (IBAction)APPSwitchChanged:(UISwitch *)sender {
        
        
    }
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
        if([sender isEqual:self.SensorNavigationSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorNavigationSwitch.on forKey:kUseSensorNavigation];
            
        }
        if([sender isEqual:self.showPOI]){
            
            [[NSUserDefaults standardUserDefaults] setBool:self.showPOI.on forKey:kSettingsShowPoi];
        }
        
        
        
        
    }




@end
