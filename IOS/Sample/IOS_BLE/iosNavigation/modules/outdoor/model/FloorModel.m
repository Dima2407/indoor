//
//  FloorModel.m
//  iosNavigation
//
//  Created by AppleFace on 21.02.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import "FloorModel.h"
#import "BeaconModel.h"

@implementation FloorModel

- (instancetype)initWithParameters:(NSDictionary*)params{
    self = [super init];
    if (self) {
        
        self.idFloor = [[params objectForKey:@"id"] integerValue];
        self.configPath = [params objectForKey:@"configPath"];
        self.mapPath = [params objectForKey:@"mapPath"] ;
        self.graphPath = [params objectForKey:@"graphPath"] ;
        self.maskPath = [params objectForKey:@"maskPath"];
        self.subtitle = [params objectForKey:@"subtitle"];
        self.buildingId = [[params objectForKey:@"buildingId"] integerValue];
        self.mapSizeCof = [[params objectForKey:@"mapSizeCof"] integerValue];
        self.buildingTitle = [params objectForKey:@"buildingTitle"];
        self.inpointIdList = [params objectForKey:@"inpointIdList"];
        self.pixelSize = [[params objectForKey:@"pixelSize"] floatValue];
        self.height = [[params objectForKey:@"height"] floatValue];
        self.widht = [[params objectForKey:@"width"] floatValue];
        self.number = [[params objectForKey:@"number"] integerValue];
        self.beacons = [self _getBeaconsFromJson:[params objectForKey:@"beaconList"]];
     
    }
    return self;
}

-(NSMutableArray*)_getBeaconsFromJson:(NSArray*)array
{
    NSMutableArray* beacons = [NSMutableArray new];
    //NSArray* floorsData = [dic objectForKey:@"floor_list"];
    [array enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        
        BeaconModel *beacon = [[BeaconModel alloc]initWithParameters:obj];
        [beacons addObject:beacon];
    }];
    
    
    
    
    return beacons;
}


@end
