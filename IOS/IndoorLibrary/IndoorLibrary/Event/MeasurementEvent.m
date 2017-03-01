//
//  MeasurementEvent.m
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "MeasurementEvent.h"
#import "MeasurementProvider.h"


@interface MeasurementEvent()

@property (nonatomic, assign) NSInteger timestamp;
@property (nonatomic, strong) MeasurementProvider* type;
@property (nonatomic, strong) NSArray *values;

@end

@implementation MeasurementEvent


@end
