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
/*! @brief  UUID value of beacon */
@property (nonatomic, strong) NSString* uuid;
/*! @brief Major value of beacon */
@property (nonatomic, assign) NSUInteger major;
/*! @brief Minor value of beacon */
@property (nonatomic, assign) NSUInteger minor;
/*! @brief Signal power of beacon */
@property (nonatomic, assign) CGFloat txPower;
/*! @brief of beacon */
@property (nonatomic, assign) CGFloat damp;
/*! @brief X coordinate of beacon */
@property (nonatomic, assign) CGFloat x;
/*! @brief Y coordinate of beacon */
@property (nonatomic, assign) CGFloat y;
/*! @brief Z coordinate of beacon */
@property (nonatomic, assign) CGFloat z;


-(instancetype)initWithUUID:(NSString*)uuid major:(NSUInteger)major minor:(NSUInteger)minor txPower:(CGFloat)txPower damp:(CGFloat)damp andX:(CGFloat)x andY:(CGFloat)y andZ:(CGFloat)z;


@end
