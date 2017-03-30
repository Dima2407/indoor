//
//  BuildingModel.m
//  iosNavigation
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import "BuildingModel.h"
#import "FloorModel.h"

@implementation BuildingModel

- (instancetype)initWithParameters:(NSDictionary*)params{
    self = [super init];
    self.froorsArray = [NSMutableArray new];
    if (self) {
        
        self.buildingID = [params objectForKey:@"id"];
        self.buildingSubtitle = [params objectForKey:@"subtitle"];
        self.buildingTitle = [params objectForKey:@"title"];
        self.buildingSizeCof = [[params objectForKey:@"pixelSize"] floatValue];
        self.beaconData = [params objectForKey:@"beacons"];
        self.froorsArray = [self _getFlorsFromJson:[params objectForKey:@"floor_list"]];
        
    }
    return self;
}
-(NSDictionary*)_getBeaconsFromJson:(NSString*)json
{
    
    NSString *firstString = [json substringFromIndex:1];
    NSString *lastString = [firstString substringToIndex:[firstString length] - 3];
    NSCharacterSet *doNotWant = [NSCharacterSet characterSetWithCharactersInString:@"/"];
    lastString = [[lastString componentsSeparatedByCharactersInSet: doNotWant] componentsJoinedByString: @""];
    lastString = [NSString stringWithFormat:@"%@}",lastString];
    
    NSData* data = [lastString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error = nil;
    NSDictionary* dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:&error];
    //NSArray* array = [dic objectForKey:@"beacons"];
    
    
    
    return dic;
}
-(CGFloat)_getPixelSizeFromJson:(NSString*)json
{
    
    NSString *firstString = [json substringFromIndex:1];
    NSString *lastString = [firstString substringToIndex:[firstString length] - 3];
    NSCharacterSet *doNotWant = [NSCharacterSet characterSetWithCharactersInString:@"/"];
    lastString = [[lastString componentsSeparatedByCharactersInSet: doNotWant] componentsJoinedByString: @""];
    lastString = [NSString stringWithFormat:@"%@}",lastString];
    
    NSData* data = [lastString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error = nil;
    NSDictionary* dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:&error];
    CGFloat pixelSize = [[dic objectForKey:@"pixelSize"] floatValue];
    return pixelSize;
}

-(NSMutableArray*)_getFlorsFromJson:(NSArray*)array
{
    NSMutableArray* floors = [NSMutableArray new];
    //NSArray* floorsData = [dic objectForKey:@"floor_list"];
    [array enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        
        FloorModel *map = [[FloorModel alloc]initWithParameters:obj];
        [floors addObject:map];
    }];
    
    
    
    
    return floors;
}

@end
