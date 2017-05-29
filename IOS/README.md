IndoorLibrary
 
Follow this step by step guide to build IndoorLibrary for iOS.
Open IndoorLibrary  XCode project.
 
Download the library of mathematical calculations Eigen. (For detailed instructions, see the official documentation http://eigen.tuxfamily.org/index.php?title=Main_Page#Download) Currently Eigen version 3.3.3 is used. The Eigen library files should be located on the path/usr/local/include/eigen3/, if they are in another directory, you need to specify the path to it in the project settings: “Header search paths" and "Other c ++ flags"
 

 
Running the app
To run the app. Now  build path  is Build/Products. If you want to change build path of your project you can change using following steps.
1) Choose Xcode > Preferences, and click Locations.
2) Click the Advanced button for the Derived Data setting.
3) Select a build location from the available options, and click Done.
 
 
BluetoothBridge
 
To connect IOS Wrapper and the library core, BluetoothBridge class is used. It contains such methods:
1) void BluetoothBridge_init (); - the method in which Navigator object is initialized. It is called in addProvider, if the provider type corresponds to BLE_PROVIDER.
2) BluetoothBridge_initBeacon (); - sets the beacons for the map. Converts BeaconConfig object to Beacon core object.
3) BluetoothBridge_proces (); - in this method the records from the beacons is transmitted.
4) BluetoothBridge_getLastPosition (); - the method that returns the coordinates of the position.
 
Including Idoor library in your iOS project
 
Open project
	1.	Now we need to link libIndoorLibrary.a with Xcode. Select the project Navigator in the left hand panel and click on project name.
	2.	Under the TARGETS click on Build Phases. Expand Link Binary With Libraries option.
	3.	Click on Add others and go to directory where libIndoorLibrary.a is located and click open. 
 
Now we need to link header files to your project. You can do it two ways: drag and drop folder IndoorLibrary to project structure or open Build settings and add path to that folder to «Header search paths».
 



Usage
 
IndoorLocationManager


IndoorLocationManager creates and manages an MeasurementProvider object based on a specified MeasurementProviderType
For getting coordinate you mast create object, which conforms to <IndoorLocationListener>, <ErrorListener> protocols.


Import IndoorLocationManager


#import "IndoorLocationManager.h"
 
 
Create IndoorLocationManager object


IndoorLocationManager *manager = [[IndoorLocationManager alloc] init];
 
//Add UUID your beacons
  [manager addUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF"];
 
//Add BLE Provider
[manager addProvider:BLE_PROVIDER];
 
Create BeaconConfig to all beacons and add its to the IndoorLocationManager
 
    BeaconConfig *firstBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48049 txPower:-71.2 damp:2 andX:4.5 andY:0.0 andZ:2.3];
    BeaconConfig *forthBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48050 txPower:-71.2 damp:2 andX:0.0 andY:3.7 andZ:2.6];
 
    BeaconConfig *thirdBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48051 txPower:-71.2 damp:2 andX:3 andY:12.8 andZ:2.3];
    BeaconConfig *secondBeacon = [[BeaconConfig alloc] initWithUUID:@"23A01AF0-232A-4518-9C0E-323FB773F5EF" major:61902 minor:48052 txPower:-71.2 damp:2 andX:0.3 andY:9.9 andZ:2.6];
 
    [manager setBeaconConfig:firstBeacon];
    [manager setBeaconConfig:secondBeacon];
    [manager setBeaconConfig:thirdBeacon];
    [manager setBeaconConfig:forthBeacon];
 
Implements IndoorLocationListenerProtocol
 
@interface ViewController ()<IndoorLocationListener,ErrorListener>
 manager.locationListener = self;
 manager.errorListener = self;


//IndoorLocationListenerProtocol
-(void)onLocation:(NSArray *)coordinte{
 NSLog(@"%@",coordinte);
}


//ErrorListenerProtocol


-(void)getError:(IndoorError *)error{
   NSLog(@"error: %@", error.error.description);
}
 
 
Credits
IndoorLibrary is owned and maintained by the KAA-Solutions.
IndoorLibrary was originally created by TODO.
License
IndoorLibrary is released under the TODO license. See LICENSE for details.
