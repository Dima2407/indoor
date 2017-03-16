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

@property (nonatomic, assign) CGFloat x;
@property (nonatomic, assign) CGFloat y;
@property (nonatomic, assign) NSUInteger minor;

-(instancetype)initWithX:(CGFloat)x andY:(CGFloat)y andUUID:(NSInteger)uuid;


@end
