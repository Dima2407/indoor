//
//  MapModel.h
//  iosNavigation
//
//  Created by Ievgen on 27.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UIKit/UIKit.h"

@interface MapModel : NSObject

@property (strong, nonatomic) NSString *mapID;
@property (strong, nonatomic) NSData *mapImage;
@property (strong, nonatomic) NSData *mapGraph;
@property (strong, nonatomic) NSData *mapMask;
@property (strong, nonatomic) NSData *mapConfig;
@property (strong, nonatomic) NSArray *beaconData;
@property (strong, nonatomic) NSString *mapTitle;
@property (assign, nonatomic) CGFloat mapSizeCof;
@property (nonatomic, strong) NSMutableArray *froorsArray;
-(instancetype)initWithParameters:(NSDictionary*)params;

@end
