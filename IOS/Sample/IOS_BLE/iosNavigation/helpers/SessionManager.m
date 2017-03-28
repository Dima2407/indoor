//
//  SessionManager.m
//  iosNavigation
//
//  Created by Ievgen on 19.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "SessionManager.h"
#import "RoutePoint.h"
#import "IndoorPOI.h"
#import "PoiModel.h"
#import "Graph.h"
#import "ApiRoutes.h"
#import "AFNetworking.h"
#import "FloorModel.h"
#import "BuildingModel.h"

@interface SessionManager()

@property (strong, nonatomic) NSURLSession *session;
@property (nonatomic, strong) NSString *token;

@end

@implementation SessionManager

#pragma mark - Create Manager -
+(SessionManager*) sharedManager{
    
   static SessionManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[self alloc]init];
       
    });
    return manager;
}

-(instancetype)init{
  
    self = [super init];
    if(self){
        NSURLSessionConfiguration *configuration = [NSURLSessionConfiguration defaultSessionConfiguration];
        self.session = [NSURLSession sessionWithConfiguration:configuration];
  
     
        
        
        
    }
 
    return self;
}

#pragma marks - Get Poi from own Server -
-(void) getMarkersFromServerWithLatitude:(NSString*)lallitude Longitude:(NSString*)longitude complitionBlock:(void(^)(NSSet *poiModels))complitionBlock{

}
#pragma mark - Get map list from own server -
-(void) getMapListWithComplitionBlock:(void(^)(NSArray *buildingList))complitionBlock{
    
        NSURL *url = [NSURL URLWithString:@"http://185.86.76.206:8081/mob/building"];
        [self createRequestWith:url httpBody:nil complitionBlock:^(NSData *data) {
            
            if (!data) {
                complitionBlock(nil);
                return;
            }
            else{
            NSMutableArray *buildingArray = [NSMutableArray array];
            NSError *error = nil;
            NSDictionary *dataDictionary = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
              
               
            NSArray* dataArray = [dataDictionary objectForKey:@"data"];
            
            [dataArray enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                
                BuildingModel *map = [[BuildingModel alloc]initWithParameters:obj];
                [buildingArray addObject:map];
            }];
            complitionBlock(buildingArray);
                [[NSNotificationCenter defaultCenter] postNotificationName:@"LoadData" object:buildingArray];
                 }}];
        
}

-(void)loginToServer
{
  
    
 NSString* pathLogin = @"http://185.86.76.206:8081/mobile/login";
    NSDictionary* params = @{@"username" : @"test",
                             @"password" : @"test123user"};
    AFHTTPSessionManager *manager = [[AFHTTPSessionManager alloc]initWithSessionConfiguration:[NSURLSessionConfiguration defaultSessionConfiguration]];
    manager.requestSerializer = [AFJSONRequestSerializer serializer];
    [manager.requestSerializer setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [manager POST:pathLogin parameters:params progress:^(NSProgress * _Nonnull uploadProgress) {
        
    } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        if ([responseObject objectForKey:@"error"] == nil)
        {
            NSString* message = [[responseObject objectForKey:@"error"] objectForKey:@"message"];
            
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"ERROR" message:message delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
            [alert show];
        }
        else{
            self.token = [responseObject objectForKey:@"data"];
            NSLog(@"login!");
            [[NSNotificationCenter defaultCenter] postNotificationName:@"login" object:nil];
        }

    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        NSLog(@"error: %@", error);
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"" message:@"Request failed please check your internet connection" delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
        [alert show];
    }];
       
        
   
}

-(void) getFloorMap:(NSString*)path
           dataType:(NSString*)typefile
         floorModel:(FloorModel*)floor
 withCoplitionBlock:(void(^)(FloorModel *map))complitionBlock{
    
    NSString *urlStr = [NSString stringWithFormat:@"http://185.86.76.206:8081/mob%@",path];
    NSURL *url = [NSURL URLWithString:urlStr];
    
    [self createRequestWith:url httpBody:nil complitionBlock:^(NSData *data) {
        
        if([typefile isEqualToString:@"map"]){
            floor.mapImage = data;
        }
        else if([typefile isEqualToString:@"mask"]){
            floor.mapMask = data;
        }
        else if([typefile isEqualToString:@"config"]){
            floor.mapConfig = data;
        }
        else if([typefile isEqualToString:@"graph"]){
            floor.mapGraph = data;
        }
        complitionBlock(floor);
    }];
}
#pragma mark - Get google route points -
-(void) getRouteWithStartLocation:(CLLocationCoordinate2D)startLocation finishLocation:(CLLocationCoordinate2D)finishLocation complitionBlock:(void(^)(NSString *routeLine,NSArray *routePoints))complitionBlock{
}

#pragma mark - Create Request -
-(void) createRequestWith:(NSURL*)url httpBody:(NSString*)httpBody complitionBlock:(void(^)(NSData *data))complitionBlock{
  
   NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    
    if(httpBody != nil){
        request.HTTPMethod = @"POST";
        [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
  
      
        request.HTTPBody = [httpBody dataUsingEncoding:NSUTF8StringEncoding];
    }
    else{

        request.HTTPMethod = @"GET";
      
        [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
        
        
        [request setValue:self.token forHTTPHeaderField:@"Authorization"];
    }
    NSURLSessionDataTask *dataTask = [self.session dataTaskWithRequest:request completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
       
        if(data){
        complitionBlock(data);
        }
    }];
    
    [dataTask resume];
}
#pragma mark - Get Indoor POI-
-(void) getIndoorPoiForMapID:(NSString*)mapID complitionBlock:(void(^)(NSDictionary *poiDictionary))complitionBlock{
    
    
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"http://185.86.76.206:8081/mob/%@/inpoint",mapID]];
    [self createRequestWith:url httpBody:nil complitionBlock:^(NSData *data) {
    
        NSError *error = nil;
        if(data != nil){
        NSDictionary *dataDic = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
            NSMutableDictionary *poiDic = [NSMutableDictionary dictionary];
            NSArray* dataArray = [dataDic objectForKey:@"data"];
            
            [dataArray enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                
                IndoorPOI *poi = [[IndoorPOI alloc]initWithParams:obj];
                [poiDic setObject:poi forKey:[NSString stringWithFormat:@"%ld",(long)poi.poiID]];
           }];
            complitionBlock(poiDic);
        }
    }];
}
#pragma mark - Get Floor POI-
-(void) getIndoorPoiForFloorID:(NSString*)floorID complitionBlock:(void(^)(NSDictionary *poiDictionary))complitionBlock{
    
    
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"http://185.86.76.206:8081/mob/%@/inpoint",floorID]];
    [self createRequestWith:url httpBody:nil complitionBlock:^(NSData *data) {
        
        NSError *error = nil;
        if(data != nil){
            NSDictionary *dataDic = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
            NSMutableDictionary *poiDic = [NSMutableDictionary dictionary];
            NSArray* dataArray = [dataDic objectForKey:@"data"];
            
            [dataArray enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                
                IndoorPOI *poi = [[IndoorPOI alloc]initWithParams:obj];
                [poiDic setObject:poi forKey:[NSString stringWithFormat:@"%ld",(long)poi.poiID]];
            }];
            complitionBlock(poiDic);
        }
    }];
}

@end
