//
//  IndoorPOI.h
//  iosNavigation
//
//  Created by Ievgen on 10.10.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface IndoorPOI : NSObject

@property (assign, nonatomic) NSInteger poiID;
@property (strong, nonatomic) NSString *poiName;
@property (strong, nonatomic) NSString *poiDescription;
@property (assign, nonatomic) CGPoint  poiCoordinate;
@property (assign, nonatomic) CGPoint  poiCenterCoordinate;


- (instancetype)initWithParams:(NSDictionary*)params;

@end
