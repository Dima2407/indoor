//
//  RoutePoint.h
//  iosNavigation
//
//  Created by Ievgen on 22.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface RoutePoint : NSObject

@property (strong, nonatomic) NSString *allDuration;
@property (strong, nonatomic) NSString *allDistance;

@property (strong, nonatomic) NSString *tempDuration;
@property (strong, nonatomic) NSString *tempDistance;

@property (strong, nonatomic) NSString *maneuver;
@property (strong, nonatomic) NSString *stepInstruction;
@property (assign, nonatomic) CLLocationCoordinate2D startLocationForMessage;

- (instancetype)initWithMainParameters:(NSDictionary*)params
                            additional:(NSDictionary*)addParams;

@end
