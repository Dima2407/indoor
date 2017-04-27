//
//  IndoorPOI.m
//  iosNavigation
//
//  Created by Ievgen on 10.10.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "IndoorPOI.h"

@implementation IndoorPOI

-(instancetype)initWithParams:(NSDictionary*)params{
    self = [super init];
    if (self) {
        
        self.poiName = [params objectForKey:@"title"];
        self.poiDescription = [params objectForKey:@"description"];
        self.poiID = [[params objectForKey:@"id"] integerValue];
        
        float x = [[params objectForKey:@"x"] floatValue];
        float y = [[params objectForKey:@"y"] floatValue];
        self.poiCoordinate = CGPointMake(x, y);
        float xCenter = [[params objectForKey:@"x"] floatValue] + 12;
        float yCenter = [[params objectForKey:@"y"] floatValue] + 20;
        self.poiCenterCoordinate = CGPointMake(xCenter, yCenter);
    }
    return self;
}

-(NSString*) description{
    
    return [NSString stringWithFormat:@"%@ %ld %@",self.poiName,self.poiID, NSStringFromCGPoint(self.poiCoordinate)];
}

@end
