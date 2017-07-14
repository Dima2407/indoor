//
//  SensorMeasurementProvider.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//
#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / M_PI))
#define kCMDeviceMotionUpdateFrequency (0.02f)
#import "SensorMeasurementProvider.h"
#import <CoreMotion/CoreMotion.h>

@interface SensorMeasurementProvider();

@property (strong, nonatomic) CMMotionManager *motionManager;
@property (nonatomic, strong) MeasurementEvent *event;
@property (nonatomic, strong) IosMeasurementTransfer *transfer;
@property (nonatomic, assign) int32_t timestamp;
@end

@implementation SensorMeasurementProvider
@synthesize transfer;


-(instancetype)initWithTransfer: (IosMeasurementTransfer*) sensorTransfer{
    self = [super init];
    
    if(self){
        
        self.motionManager = [[CMMotionManager alloc] init];
        NSLog(@"Init CMMotionManager");
        self.transfer = sensorTransfer;
        self.type = SENSOR_PROVIDER;
        self.timestamp = [[NSDate date] timeIntervalSince1970];
    }
    return self;
}
#pragma mark - Action
-(void) start{
    self.timestamp = [[NSDate date] timeIntervalSince1970];
    [self.motionManager setAccelerometerUpdateInterval:kCMDeviceMotionUpdateFrequency];
    [self.motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue]
                        withHandler:^(CMAccelerometerData  *accelerometerData, NSError *error) {
                            [self outputData];
                            
                                             }];
    



    
    [self.motionManager setDeviceMotionUpdateInterval:kCMDeviceMotionUpdateFrequency];
    [self.motionManager startDeviceMotionUpdatesUsingReferenceFrame:CMAttitudeReferenceFrameXMagneticNorthZVertical toQueue:[NSOperationQueue currentQueue] withHandler:^(CMDeviceMotion *motion, NSError *error){
       
    }];
    
    
    
    
    
}
-(void)outputData{
    
     CMAccelerometerData  *accelerometerData = [self.motionManager accelerometerData];
    CMDeviceMotion *motion = [self.motionManager deviceMotion];
    MeasurementEvent * event =[[MeasurementEvent alloc] initWithAccelerometerData:accelerometerData andDeviceMotion:motion];
    event.timestamp = [[NSDate date] timeIntervalSince1970] - self.timestamp;
    [self.transfer deliver:event];
    
    
}




-(void)stop{
    
    [self.motionManager stopAccelerometerUpdates];
    [self.motionManager stopDeviceMotionUpdates];
    
    
    
}

@end
