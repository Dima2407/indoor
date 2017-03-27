//
//  MapModel.m
//  iosNavigation
//
//  Created by Ievgen on 27.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "MapModel.h"
#import "FloorModel.h"
//@interface MapModel ()
//
//@property (nonatomic, assign)NSData* dataBeacon;
//
//@end


@implementation MapModel

- (instancetype)initWithParameters:(NSDictionary*)params{
    self = [super init];
    self.froorsArray = [NSMutableArray new];
    if (self) {
        
        self.mapID = [params objectForKey:@"id"];
        self.mapTitle = [params objectForKey:@"title"];
        self.mapSizeCof = [[params objectForKey:@"pixelSize"] floatValue];
        NSString *stringData = [params objectForKey:@"data"];
        self.beaconData = [[self _getBeaconsFromJson:stringData]objectForKey:@"beacons"];
        self.mapSizeCof = [self _getPixelSizeFromJson:stringData];
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
