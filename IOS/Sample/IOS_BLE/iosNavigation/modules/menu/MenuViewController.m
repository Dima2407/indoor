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
@property (weak, nonatomic) IBOutlet UISwitch *SensorKalmanSwitch;

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
    BOOL sensorRssi =  [[NSUserDefaults standardUserDefaults] boolForKey:kSensorRSSIAveraging];
    if (sensorRssi)
    {
        self.xSensorTextField.userInteractionEnabled = NO;
        self.ySensorTextField.userInteractionEnabled = NO;
    }
    
    
    self.sendLogButton.userInteractionEnabled = log;
    
}
-(void)viewWillDisappear:(BOOL)animated{
    if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorNavigationSwitch])
    {
        BOOL manual = [[NSUserDefaults standardUserDefaults] boolForKey:kSensorManual];
        BOOL rssi = [[NSUserDefaults standardUserDefaults] boolForKey:kSensorRSSIAveraging];
        BOOL kalman = [[NSUserDefaults standardUserDefaults] boolForKey:kSensorKalmanSwitch];
        if (!manual && !rssi && !kalman)
        {
            [self onSensor];
        }
    }
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
        BOOL kalman =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEKalmanSwitch];
        [self.BLEKalmanSwitch setOn:kalman animated:YES];
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
        self.xSensorTextField.userInteractionEnabled = YES;
        self.ySensorTextField.userInteractionEnabled = YES;
        BOOL sensorRssi =  [[NSUserDefaults standardUserDefaults] boolForKey:kSensorRSSIAveraging];
        if (sensorRssi)
        {
            self.xSensorTextField.userInteractionEnabled = NO;
            self.ySensorTextField.userInteractionEnabled = NO;
        }
        [self.SensorRSSIAveraging setOn:sensorRssi animated:YES];
        self.SensorSettingsView.hidden = NO;
        BOOL sensorKalman =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEKalmanSwitch];
       // if (sensorRssi || sensorKalman)
//        {
//            self.xSensorTextField.userInteractionEnabled = NO;
//            self.ySensorTextField.userInteractionEnabled = NO;
//        }
        [self.BLEKalmanSwitch setOn:sensorKalman animated:YES];
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
    self.xSensorTextField.text = 0;
    self.ySensorTextField.text = 0;
}


-(void)viewDidLoad{
    [super viewDidLoad];
    
}
#pragma mark - Action

- (IBAction)BLESwitchAction:(UISwitch *)sender {
    if([sender isOn]){
        [self onBLE];
        [self offSensor];
    }
    else{
        [self offBLE];
        [self onSensor];
    }
    [[NSUserDefaults standardUserDefaults] setBool:self.BLENavigationSwitch.on forKey:kBLENavigationSwitch];
    
    
}
- (IBAction)SensorSwitchAction:(UISwitch *)sender {
    if([sender isOn]){
        [self onSensor];
        [self offBLE];
    }
    else{
        [self offSensor];
        [self onBLE];
    }
    [[NSUserDefaults standardUserDefaults] setBool:self.SensorNavigationSwitch.on forKey:kSensorNavigationSwitch];
    
}


- (IBAction)BLESwitchChanged:(UISwitch *)sender {
    if (sender.isOn)
    {
        if([sender isEqual:self.BLECircleSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.BLECircleSwitch.on forKey:kBLECircleSwitch];
            [self.BLECircleSwitch setOn:YES];
            [self.BLEKalmanSwitch setOn:NO];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEKalmanSwitch];
            
        }
        else if([sender isEqual:self.BLETrilatirationSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.BLETrilatirationSwitch.on forKey:kBLETrilatirationSwitch];
        }
        else if([sender isEqual:self.BLEKalmanSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLECircleSwitch];
            [self.BLECircleSwitch setOn:NO];
            [self.BLEKalmanSwitch setOn:YES];
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kBLEKalmanSwitch];
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
    else{
        if([sender isEqual:self.BLECircleSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLECircleSwitch];
            [self.BLECircleSwitch setOn:NO];
            [self.BLEKalmanSwitch setOn:YES];
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kBLEKalmanSwitch];
            
        }
        else if([sender isEqual:self.BLETrilatirationSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:self.BLETrilatirationSwitch.on forKey:kBLETrilatirationSwitch];
        }
        else if([sender isEqual:self.BLEKalmanSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kBLECircleSwitch];
            [self.BLECircleSwitch setOn:YES];
            [self.BLEKalmanSwitch setOn:NO];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEKalmanSwitch];
        }
        else if([sender isEqual:self.BLEMapSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEMapSwitch];
        }
        else if([sender isEqual:self.BLEMeshSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEMeshSwitch];
        }
        else if([sender isEqual:self.BLEWallsSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEWallsSwitch];
        }

        
    }
    
}
- (IBAction)SensorSwitchChanged:(UISwitch *)sender {
    
    if (sender.isOn)
    {
        if([sender isEqual:self.SensorManual]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorManual.on forKey:kSensorManual];
            self.xSensorTextField.userInteractionEnabled = YES;
            self.ySensorTextField.userInteractionEnabled = YES;
            [self.SensorRSSIAveraging setOn:NO animated:YES];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorRSSIAveraging];
            [self.SensorKalmanSwitch setOn:NO animated:YES];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorKalmanSwitch];
            
        }
        else if([sender isEqual:self.SensorRSSIAveraging]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorRSSIAveraging.on forKey:kSensorRSSIAveraging];
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorManual];
            [self.SensorManual setOn:NO animated:YES];
            self.xSensorTextField.userInteractionEnabled = NO;
            self.ySensorTextField.userInteractionEnabled = NO;
            
              [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorKalmanSwitch];
            [self.SensorKalmanSwitch setOn:NO animated:YES];
          
        }
        else if([sender isEqual:self.SensorKalmanSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorManual];
            [self.SensorManual setOn:NO animated:YES];
            self.xSensorTextField.userInteractionEnabled = NO;
            self.ySensorTextField.userInteractionEnabled = NO;
            
             [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorRSSIAveraging];
            [self.SensorRSSIAveraging setOn:NO animated:YES];
           
        
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kSensorKalmanSwitch];
            
        }
        else if([sender isEqual:self.SensorMapCorrectionSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kSensorMapCorrectionSwitch];
        }
        else if([sender isEqual:self.SensorMeshCorrectionSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kSensorMeshCorrectionSwitch];
        }
        else if([sender isEqual:self.SensorWallsCorrectionSwitch]){
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kSensorWallsCorrectionSwitch];
        }
    }
    else{
        if([sender isEqual:self.SensorManual]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorManual.on forKey:kSensorManual];
            
        }
        else if([sender isEqual:self.SensorRSSIAveraging]){
            [[NSUserDefaults standardUserDefaults] setBool:self.SensorRSSIAveraging.on forKey:kSensorRSSIAveraging];
        }
         else if([sender isEqual:self.SensorKalmanSwitch]){
        [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorKalmanSwitch];
         }
         else if([sender isEqual:self.SensorMapCorrectionSwitch]){
             [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorMapCorrectionSwitch];
         }
         else if([sender isEqual:self.SensorMeshCorrectionSwitch]){
             [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorMeshCorrectionSwitch];
         }
         else if([sender isEqual:self.SensorWallsCorrectionSwitch]){
             [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorWallsCorrectionSwitch];
         }
    }
    
}
- (IBAction)APPSwitchChanged:(UISwitch *)sender {
    
    
}
- (IBAction)sendLogs:(UIButton *)sender {
    NSError *error = nil;
    NSArray *log = [[BeaconManager sharedManager] getLogs];
    
    if (log)
    {
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
    else{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"ERROR" message:@"Log is empty" delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
        [alert show];
        
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

-(void)onBLE{
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kBLENavigationSwitch];
    [self.BLENavigationSwitch setOn:YES animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kBLECircleSwitch];
    [self.BLECircleSwitch setOn:YES animated:YES];
    self.BLESettingsView.hidden = NO;
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLETrilatirationSwitch];
    [self.BLETrilatirationSwitch setOn:NO animated:YES];
    BOOL kalman =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEKalmanSwitch];
    [self.BLEKalmanSwitch setOn:kalman animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kBLEMapSwitch];
    [self.BLEMapSwitch setOn:YES animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEWallsSwitch];
    [self.BLEWallsSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEMeshSwitch];
    [self.BLEMeshSwitch setOn:NO animated:YES];
    
    
    
}
-(void)offBLE{
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLENavigationSwitch];
    [self.BLENavigationSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLECircleSwitch];
    [self.BLECircleSwitch setOn:NO animated:YES];
    self.BLESettingsView.hidden = YES;
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLETrilatirationSwitch];
    [self.BLETrilatirationSwitch setOn:NO animated:YES];
    BOOL kalman =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEKalmanSwitch];
    [self.BLEKalmanSwitch setOn:kalman animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEMapSwitch];
    [self.BLEMapSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEWallsSwitch];
    [self.BLEWallsSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEMeshSwitch];
    [self.BLEMeshSwitch setOn:NO animated:YES];
    
    
}
-(void)onSensor{
    self.SensorSettingsView.hidden = NO;
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kSensorNavigationSwitch];
    [self.SensorNavigationSwitch setOn:YES animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorManual];
    [self.SensorManual setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kSensorRSSIAveraging];
    [self.SensorRSSIAveraging setOn:YES animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorKalmanSwitch];
    [self.SensorKalmanSwitch setOn:NO animated:YES];
    
    [[NSUserDefaults standardUserDefaults] setDouble:0.0 forKey:kSensorX];
    [[NSUserDefaults standardUserDefaults] setDouble:0.0 forKey:kSensorY];
    BOOL sensorKalman =  [[NSUserDefaults standardUserDefaults] boolForKey:kBLEKalmanSwitch];
    [self.BLEKalmanSwitch setOn:sensorKalman animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kSensorMapCorrectionSwitch];
    [self.SensorMapCorrectionSwitch setOn:YES animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorWallsCorrectionSwitch];
    [self.SensorWallsCorrectionSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorMeshCorrectionSwitch];
    [self.SensorMeshCorrectionSwitch setOn:NO animated:YES];
}
-(void)offSensor{
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorNavigationSwitch];
    [self.SensorNavigationSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorManual];
    [self.SensorManual setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorRSSIAveraging];
    [self.SensorRSSIAveraging setOn:NO animated:YES];
    self.SensorSettingsView.hidden = YES;
   [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kBLEKalmanSwitch];
    [self.BLEKalmanSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorMapCorrectionSwitch];
    [self.SensorMapCorrectionSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorWallsCorrectionSwitch];
    [self.SensorWallsCorrectionSwitch setOn:NO animated:YES];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:kSensorMeshCorrectionSwitch];
    [self.SensorMeshCorrectionSwitch setOn:NO animated:YES];
}

@end
