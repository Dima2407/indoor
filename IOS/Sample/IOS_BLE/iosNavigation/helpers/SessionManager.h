//
//  SessionManager.h
//  iosNavigation
//
//  Created by Ievgen on 19.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <GoogleMaps/GoogleMaps.h>
#import "MapModel.h"
#import "FloorModel.h"
#import "BuildingModel.h"

@interface SessionManager : NSObject


+(SessionManager*) sharedManager;
-(void)loginToServer;
-(void) getMarkersFromServerWithLatitude:(NSString*)lallitude Longitude:(NSString*)longitude complitionBlock:(void(^)(NSSet *poiModels))complitionBlock;
-(void) getRouteWithStartLocation:(CLLocationCoordinate2D)startLocation finishLocation:(CLLocationCoordinate2D)finishLocation complitionBlock:(void(^)(NSString *routeLine, NSArray *routePoints))complitionBlock;
-(void) getMapListWithComplitionBlock:(void(^)(NSArray *mapList))complitionBlock;
-(void) getIndoorPoiForMapID:(NSString*)mapID complitionBlock:(void(^)(NSDictionary *poiDictionary))complitionBlock;
-(void) getFloorMap:(NSString*)path dataType:(NSString*)typefile floorModel:(FloorModel*)floor withCoplitionBlock:(void(^)(FloorModel *map))complitionBlock;
-(void) getIndoorPoiForFloorID:(NSString*)floorID complitionBlock:(void(^)(NSDictionary *poiDictionary))complitionBlock;

@end
