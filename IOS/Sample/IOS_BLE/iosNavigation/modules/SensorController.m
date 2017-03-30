//
//  SensorController.m
//  iosNavigation
//
//  Created by Ievgen on 29.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "SensorController.h"

@implementation SensorController

+(SensorController*) sharedController{
    
    static SensorController *controller = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        controller = [[SensorController alloc]init];
    });
    return controller;
}

@end
