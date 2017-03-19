//
//  IndoorLocationManager.h
//  IndoorLibrary
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementProvider.h"
#import "MeasurementEvent.h"
#import "IosMeasurementTransfer.h"
#import "IndoorLocationUpdateDelegate.h"

@interface IndoorLocationManager : NSObject

// @property (nonatomic, assign) TrilatBeaconNavigator* navigator;
@property (nonatomic, strong) NSMutableSet<MeasurementProvider*> *providers;
@property (nonatomic, strong) IosMeasurementTransfer *transfer;


-(void)prepare;
-(void)release;
-(void)addProvider: (MeasurementType) type;
-(void)removeProvider: (MeasurementType) type;
-(void)start;
-(void)stop;
-(void)process: (MeasurementEvent *) event;
@end
