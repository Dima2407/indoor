//
//  BeaconConfig.h
//  IndoorLibrary
//
//  Created by AppleFace on 13.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TConfig.h"
#import <UIKit/UIKit.h>

@interface BeaconConfig : NSObject<TConfig>
@property (nonatomic, strong) NSString* uuid;
@property (nonatomic, assign) NSUInteger major;
@property (nonatomic, assign) NSUInteger minor;
@property (nonatomic, assign) CGFloat txPower;
@property (nonatomic, assign) CGFloat damp;
@property (nonatomic, assign) CGFloat x;
@property (nonatomic, assign) CGFloat y;
@property (nonatomic, assign) CGFloat z;


-(instancetype)initWithUUID:(NSString*)uuid major:(NSUInteger)major minor:(NSUInteger)minor txPower:(CGFloat)txPower damp:(CGFloat)damp andX:(CGFloat)x andY:(CGFloat)y andZ:(CGFloat)z;


@end
