//
//  FloorModel.h
//  iosNavigation
//
//  Created by AppleFace on 21.02.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface FloorModel : NSObject
@property (assign, nonatomic) NSInteger idFloor;
@property (nonatomic, strong) NSString *subtitle;
@property (strong, nonatomic) NSString *configPath;
@property (strong, nonatomic) NSString *mapPath;
@property (strong, nonatomic) NSString *graphPath;
@property (strong, nonatomic) NSString *maskPath;
@property (assign, nonatomic) NSInteger buildingId;
@property (strong, nonatomic) NSString *buildingTitle;
@property (strong, nonatomic) NSArray *inpointIdList;
@property (assign, nonatomic) NSInteger number;
@property (strong, nonatomic) NSData *mapImage;
@property (strong, nonatomic) NSData *mapGraph;
@property (strong, nonatomic) NSData *mapMask;
@property (strong, nonatomic) NSData *mapConfig;
@property (nonatomic, strong) NSArray *beacons;
@property (assign, nonatomic) NSInteger mapSizeCof;
@property (nonatomic, assign) CGFloat pixelSize;
@property (nonatomic, assign) CGFloat height;
@property (nonatomic, assign) CGFloat wight;



-(instancetype)initWithParameters:(NSDictionary*)params;

@end
