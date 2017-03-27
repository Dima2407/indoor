//
//  PoiModel.m
//  iosNavigation
//
//  Created by Ievgen on 26.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "PoiModel.h"

@implementation PoiModel

- (instancetype)initWithParameters:(NSDictionary*)params
{
    self = [super init];
    if (self) {
        
        self.position = CLLocationCoordinate2DMake([[params objectForKey:@"poiLatitude"] floatValue],
                                                       [[params objectForKey:@"poiLongitude"] floatValue]);
        self.title = [params objectForKey:@"poiName"];
        self.snippet = [params objectForKey:@"poiDescription"];
            
        if([params objectForKey:@"poiImage"] != nil){
            NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:[params objectForKey:@"poiImage"]]];
            self.icon = [UIImage imageWithData:data];
        }
    }
    return self;
}

@end
