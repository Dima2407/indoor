//
//  BeaconModel.m
//  iosNavigation
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import "BeaconModel.h"


@implementation BeaconModel

- (instancetype)initWithParameters:(NSDictionary*)params{
    self = [super init];
    if (self) {
        
        self.uuid = [params objectForKey:@"uuid"];
        self.x = [[params objectForKey:@"x"] floatValue];
        self.y = [[params objectForKey:@"y"] floatValue];
        self.z = [[params objectForKey:@"z"] floatValue];
        self.major = [[params objectForKey:@"major"] integerValue];
        self.minor = [[params objectForKey:@"minor"] integerValue];
        self.damp = [[params objectForKey:@"damp"] floatValue];
        self.floorId = [[params objectForKey:@"floorId"] integerValue];
        self.floorNumber = [[params objectForKey:@"floorNumber"] integerValue];
        self.buildingId = [[params objectForKey:@"buildingId"] integerValue];
        self.buildingTitle = [params objectForKey:@"buildingTitle"];
        self.txpower = [[params objectForKey:@"txpower"] floatValue];
        
    }
    return self;
}


@end
