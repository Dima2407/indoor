//
//  BuildingModel.h
//  iosNavigation
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UIKit/UIKit.h"

@interface BuildingModel : NSObject

@property (strong, nonatomic) NSString *buildingID;
@property (strong, nonatomic) NSData *buildingImage;
@property (strong, nonatomic) NSData *buildingGraph;
@property (strong, nonatomic) NSData *buildingMask;
@property (strong, nonatomic) NSData *buildingConfig;
@property (strong, nonatomic) NSArray *beaconData;
@property (strong, nonatomic) NSString *buildingTitle;
@property (strong, nonatomic) NSString *buildingSubtitle;
@property (assign, nonatomic) CGFloat buildingSizeCof;
@property (nonatomic, strong) NSMutableArray *froorsArray;
-(instancetype)initWithParameters:(NSDictionary*)params;

@end
