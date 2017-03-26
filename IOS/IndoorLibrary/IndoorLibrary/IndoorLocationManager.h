//
//  IndoorLocationManager.h
//  IndoorLibrary
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.

#import "PrefixHeader.pch"



@interface IndoorLocationManager : NSObject

@property (nonatomic, strong) NSMutableSet<MeasurementProvider*> *providers;
@property (nonatomic, strong) IosMeasurementTransfer *transfer;
@property (nonatomic, strong) id<IndoorLocationListener> locationListener;
@property (nonatomic, strong) id<ErrorListener> errorListener;
@property (nonatomic, assign) BOOL logger;


-(void)addProvider: (MeasurementProviderType) type;
-(void)removeProvider: (MeasurementProviderType) type;
-(void)start;
-(void)stop;
-(void)setBeaconConfig:(BeaconConfig*) config;
@end
