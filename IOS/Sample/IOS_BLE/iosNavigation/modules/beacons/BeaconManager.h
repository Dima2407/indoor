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
@property (nonatomic, assign) BOOL status;

+(BeaconManager*) sharedManager;
-(void) setBeaconMap:(FloorModel*)map withBeaconData:(NSArray*)data;
-(void) startBeacon;
-(void) stopBeacon;
-(void)setSensorConfig:(NSString*)filter useMap:(BOOL)map useMesh:(BOOL)mesh useWalls:(BOOL)walls x:(double)x y:(double)y;
-(void)setBeaconConfig:(NSString*)filter useMultilat:(BOOL)multilat useMap:(BOOL)map useMesh:(BOOL)mesh useWalls:(BOOL)walls;
-(NSArray*) getLogs;
-(void) setMesh:(NSArray*)mesh and:(NSArray*)mask;
-(void)setDestination:(CGPoint)destination;
-(void) setGraph:(FloorModel*)floor withGraph:(NSString*)gpaphJsonString;
-(CGFloat)getDistance;

@end

@protocol BeaconManagerDelegate

-(void) currentLocation:(CGPoint)location;
-(void) currentRouting:(NSArray*)way;
@end
