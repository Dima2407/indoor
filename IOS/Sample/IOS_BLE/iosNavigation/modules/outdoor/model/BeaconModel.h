//
//  BeaconModel.h
//  iosNavigation
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import  <UIKit/UIKit.h>

@interface BeaconModel : NSObject
@property (nonatomic, strong)  NSString *uuid;
@property (nonatomic, assign) CGFloat x;
@property (nonatomic, assign) CGFloat y;
@property (nonatomic, assign) CGFloat z;
@property (nonatomic, assign) NSInteger major;
@property (nonatomic, assign) NSInteger minor;
@property (nonatomic, assign) CGFloat damp;
@property (nonatomic, assign) NSInteger floorId;
@property (nonatomic, assign) NSInteger floorNumber;
@property (nonatomic, assign) NSInteger buildingId;
@property (nonatomic, strong) NSString *buildingTitle;
@property (nonatomic, assign) CGFloat txpower;


-(instancetype)initWithParameters:(NSDictionary*)params;

@end
