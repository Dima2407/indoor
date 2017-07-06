//
//  MainInDoorController.h
//  iosNavigation
//
//  Created by Ievgen on 05.10.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "Graph.h"
#import "MapModel.h"
#import "IndoorPOI.h"
#import "RoutePoint.h"
#import <UIKit/UIKit.h>
#import "RouteInfoView.h"
#import "BeaconManager.h"
#import "DrawingMapView.h"
#import "SessionManager.h"
#import "UIImage+ManeuverImage.h"
#import "ConverterPointAndPixel.h"
#import "SWRevealViewController.h"
#import "RouteInfoListController.h"

typedef enum{
    
    ConvertTypePoint,
    ConvertTypePixel
    
}ConvertType;

@interface IndoorMainController : UIViewController <UIScrollViewDelegate>

@property (assign, nonatomic) BOOL isRoute;

-(void) addTapGestureOnView:(id)view selector:(SEL)selector;
-(RouteInfoView*) createCustomRouteInfoView:(RouteInfoView*)routeView;
-(void) clearRouteAlertWithComplitionBlock:(void(^)())complitionblock;
-(CGPoint) tapDetection:(UITapGestureRecognizer*)tap onView:(UIView*)view;
-(NSArray*) getManeuverWithStartPoint:(CGPoint)start pointsArray:(NSArray*)points pixelSize:(CGFloat)pixSize;
-(RouteInfoView*) fillRouteInfoView:(RouteInfoView*)view distance:(NSString*)distance duration:(NSString*)duration step:(NSString*)step maneuver:(UIImage*)img;
-(void) createDropdownMenuWihtMenuButton:(UIBarButtonItem*)button view:(UIView*)view;
-(DrawingMapView*) createDrawViewWithStartPoint:(CGPoint)startPoint withSizeView:(UIImageView*)imgView;
-(DrawingMapView*) drawRouteFromPoints:(NSArray *)points onDrawView:(DrawingMapView*)drawView withStartPoint:(CGPoint)startPoint;
-(CGRect) createRectSameImage:(UIImageView*)imgView;
-(NSArray*) convertPoint:(NSArray*)pointsList
             convertType:(ConvertType)type image:(UIImage*)img view:(UIView*)view;
-(NSArray*) getPointsFromGraph:(Graph*)graph
                withStartPoint:(CGPoint)start endPoint:(CGPoint)end;

-(void) createRouteAlertWithTitle:(NSString*)title text:(NSString*)text complitionBlock:(void(^)())complitionBlock;
-(void) getFloorMapData:(NSString*)path fileType:(NSString*)type mapModel:(FloorModel*)model completionBlock:(void(^)(FloorModel *map))complitionBlock;

@end
