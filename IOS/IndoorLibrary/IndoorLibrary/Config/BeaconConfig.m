//
//  BeaconConfig.m
//  IndoorLibrary
//
//  Created by AppleFace on 13.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "BeaconConfig.h"


@interface BeaconConfig()
@property (nonatomic, assign) CGFloat txPower;
@property (nonatomic, assign) CGFloat damp;
@property (nonatomic, strong) NSString* uuid;
@property (nonatomic, assign) NSUInteger major;


@property (nonatomic, assign) CGFloat z;
@property (nonatomic, strong) NSArray *position;

@end


@implementation BeaconConfig

-(instancetype)initWithX:(CGFloat)x andY:(CGFloat)y andUUID:(NSInteger)uuid{
    self = [super init];
    
    if(self){
        
     
        
        self.x = x ;
        self.y = y;
        self.minor = uuid;
  
       
    }
    return self;
}


@end
