//
//  BeaconManager.h
//  iosNavigation
//
//  Created by Ievgen on 21.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "FloorModel.h"

@protocol BeaconManagerDelegate;

@interface BeaconManager : NSObject

@property (weak, nonatomic) id <BeaconManagerDelegate> delegate;

+(BeaconManager*) sharedManager;
-(void) setBeaconMap:(FloorModel*)map withBeaconData:(NSArray*)data;
-(void) startBeacon;

@end

@protocol BeaconManagerDelegate 

-(void) currentLocation:(CGPoint)location;

@end
