//
//  MainInDoorController.m
//  iosNavigation
//
//  Created by Ievgen on 05.10.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//
#define kScreenWidth            [UIScreen mainScreen].bounds.size.width
#define kScreenHeight           [UIScreen mainScreen].bounds.size.height

#import "IndoorMainController.h"
#import "AOShortestPath.h"
#import "EKVertex.h"
#import "FloorModel.h"

@interface IndoorMainController ()

@end

@implementation IndoorMainController

-(void)viewDidLoad{
    [super viewDidLoad];
 

}

#pragma mark - Get Touch Location-
-(CGPoint) tapDetection:(UITapGestureRecognizer*)tap onView:(UIView*)view{
    
    CGPoint point = [tap locationInView:view];
    
    if([view pointInside:point withEvent:nil]){
        return point;
    }
    else{
        return CGPointMake(-1, -1);
    }

}
#pragma mark - Add Gesture On View -
-(void) addTapGestureOnView:(id)view selector:(SEL)selector{
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]
                                   initWithTarget:self action:selector];
    [view setUserInteractionEnabled:YES];
    [view addGestureRecognizer:tap];
}
#pragma mark - Get Route Points From Graph -
-(NSArray*) getPointsFromGraph:(Graph*)graph
                withStartPoint:(CGPoint)start endPoint:(CGPoint)end{
  
    NSArray *pointsList = [[NSArray alloc] init];
//    pointsList = [graph.pathManager getShortestPathFromPointX:start.x
//                                                               fromY:start.y
//                                                                 toX:end.x
//                                                                 toY:end.y];
    
    pointsList = [graph.graphManager dijkstraShortestPathFrom:start To:end];
    
    return pointsList;
}
#pragma mark - Convertor pixel and point -
-(NSArray*) convertPoint:(NSArray*)pointsList
             convertType:(ConvertType)type image:(UIImage*)img view:(UIView*)view{
    
    NSMutableArray *points = [NSMutableArray array];
    
    if ([[pointsList firstObject] isKindOfClass:[AOPathPoint class]]) {
        for(AOPathPoint *point in pointsList){
            
            CGPoint pOrigin;
            pOrigin.x = point.x;
            pOrigin.y = point.y;
            
            pOrigin = convertPixelToPoint(pOrigin, img.size, view.frame.size);
            
            [points addObject:[NSValue valueWithCGPoint:pOrigin]];
        }

    } else if ([[pointsList firstObject] isKindOfClass:[EKVertex class]]) {
        for(EKVertex *vertex in pointsList){
            
            CGPoint pOrigin;
            pOrigin.x = vertex->x;
            pOrigin.y = vertex->y;
            
            pOrigin = convertPixelToPoint(pOrigin, img.size, view.frame.size);
            
            [points addObject:[NSValue valueWithCGPoint:pOrigin]];
        }
    }
    return points;
}
#pragma mark - Get Map Data -
//-(void) getMapData:(NSString*)mapID floor:(NSString*)floorID fileType:(NSString*)type mapModel:(MapModel*)model completionBlock:(void(^)(MapModel *map))complitionBlock{
//    
//    [[SessionManager sharedManager] getMapDataWihtMapID:mapID floorID:floorID dataType:type mapModel:model withCoplitionBlock:^(MapModel *map) {
//        complitionBlock(map);
//    }];
//}
#pragma mark - Get Floor Data -
-(void) getFloorMapData:(NSString*)path fileType:(NSString*)type mapModel:(FloorModel*)model completionBlock:(void(^)(FloorModel *map))complitionBlock{
    
    [[SessionManager sharedManager] getFloorMap:path dataType:type floorModel:model  withCoplitionBlock:^(FloorModel *map) {
    
        complitionBlock(map);
       }];
}

#pragma mark - Create Image Rect -
-(CGRect) createRectSameImage:(UIImageView*)imgView{
    
    CGSize imgViewSize = imgView.frame.size;
    CGSize imgSize = imgView.image.size;
    
    CGFloat scaleW = imgViewSize.width / imgSize.width;
    CGFloat scaleH = imgViewSize.height / imgSize.height;
    CGFloat aspect=fmin(scaleW, scaleH);
    
    CGRect imageRect={ {0,0} , { imgSize.width*=aspect, imgSize.height*=aspect } };
    
    imageRect.origin.x=(imgViewSize.width-imageRect.size.width)/2;
    imageRect.origin.y=(imgViewSize.height-imageRect.size.height)/2;
    
    imageRect.origin.x += imgView.frame.origin.x;
    imageRect.origin.y += imgView.frame.origin.y;
    return imageRect;
}
#pragma mark - Create Drop Down Menu -
-(void) createDropdownMenuWihtMenuButton:(UIBarButtonItem*)button view:(UIView*)view{
    
    SWRevealViewController *revealViewController = self.revealViewController;
    if ( revealViewController )
    {
        self.revealViewController.rearViewRevealWidth = view.bounds.size.width * 0.8f;
        [button setTarget: self.revealViewController];
        [button setAction: @selector( revealToggle: )];
        [view addGestureRecognizer:self.revealViewController.panGestureRecognizer];
    }
}
#pragma mark - Create Draw View -
-(DrawingMapView*) createDrawViewWithStartPoint:(CGPoint)startPoint withSizeView:(UIImageView*)imgView{
    CGRect image = [self calculateClientRectOfImageInUIImageView:imgView];
    CGRect imageRect = CGRectMake(image.origin.x, image.origin.y, image.size.width, image.size.height);
    DrawingMapView *drawView = [[DrawingMapView alloc]initWithFrame:imageRect];
    drawView.backgroundColor = [UIColor clearColor];
    drawView.startPoint = convertPixelToPoint(startPoint,imgView.image.size, drawView.frame.size);
    [imgView addSubview:drawView];
    return drawView;
}
-(CGRect )calculateClientRectOfImageInUIImageView:(UIImageView *)imgView
{
    CGSize imgViewSize=imgView.frame.size;
    CGSize imgSize=imgView.image.size;
    
    CGFloat scaleW = imgViewSize.width / imgSize.width;
    CGFloat scaleH = imgViewSize.height / imgSize.height;
    CGFloat aspect=fmin(scaleW, scaleH);
    
    CGRect imageRect={ {0,0} , { imgSize.width*=aspect, imgSize.height*=aspect } };
  
    
    imageRect.origin.x=(imgViewSize.width-imageRect.size.width)/2;
    imageRect.origin.y=(imgViewSize.height-imageRect.size.height)/2;
    
    imageRect.origin.x+=imgView.frame.origin.x;
    imageRect.origin.y+=imgView.frame.origin.y;
    
    return(imageRect);
}
#pragma mark - Drawing route on map -
-(DrawingMapView*) drawRouteFromPoints:(NSArray *)points onDrawView:(DrawingMapView*)drawView withStartPoint:(CGPoint)startPoint{
    
    drawView.pointsArray = points;
    drawView.startPoint = startPoint;
    [drawView setNeedsDisplay];
    return drawView;
}
#pragma mark - Clear Route Alert -
-(void) clearRouteAlertWithComplitionBlock:(void(^)())complitionblock{
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Delete route" message:@"Are you shure want to delete route?" preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *deleteRouteAction = [UIAlertAction actionWithTitle:@"Delete" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        complitionblock();
    }];
    UIAlertAction *canselAction = [UIAlertAction actionWithTitle:@"Canсel" style:UIAlertActionStyleDestructive handler:nil];
    [alert addAction:deleteRouteAction];
    [alert addAction:canselAction];
    [self presentViewController:alert animated:YES completion:nil];
}
#pragma mark - Building Route Alert -
-(void) createRouteAlertWithTitle:(NSString*)title text:(NSString*)text complitionBlock:(void(^)())complitionBlock{
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title message:text preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *buildRoutAction = [UIAlertAction actionWithTitle:@"To point" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        complitionBlock();
    }];
    UIAlertAction *canselAction = [UIAlertAction actionWithTitle:@"Close" style:UIAlertActionStyleDestructive handler:nil];
    [alert addAction:buildRoutAction];
    [alert addAction:canselAction];
    [self presentViewController:alert animated:YES completion:nil];
}
#pragma mark - Get Indoor Maneuver -
-(NSArray*) getManeuverWithStartPoint:(CGPoint)start pointsArray:(NSArray*)points pixelSize:(CGFloat)pixSize{
    
    NSMutableArray *array = [NSMutableArray array];
    
    if ([[points firstObject] isKindOfClass:[EKVertex class]]) {
        for(EKVertex *vertex in points){
            
            CGPoint pOrigin;
            pOrigin.x = vertex->x;
            pOrigin.y = vertex->y;
            [array addObject:[NSValue valueWithCGPoint:pOrigin]];
        }
    } else {
        for(AOPathPoint *point in points){
            
            CGPoint pOrigin;
            pOrigin.x = point.x;
            pOrigin.y = point.y;
            [array addObject:[NSValue valueWithCGPoint:pOrigin]];
        }
    }
    NSArray *pointsArray = calculateManeuverWithStartPoint(start, array, pixSize);
    return pointsArray;
}
#pragma mark - Fill Route Info View -
-(RouteInfoView*) fillRouteInfoView:(RouteInfoView*)view distance:(NSString*)distance duration:(NSString*)duration step:(NSString*)step maneuver:(UIImage*)img{
    
    view.distance.text = distance;
    view.duration.text = duration;
    view.nextStep.text = step;
    view.imageView.image = img;
    return view;
}
#pragma mark - Create Route Info View -
-(RouteInfoView*) createCustomRouteInfoView:(RouteInfoView*)routeView{

    routeView.backgroundColor = [UIColor whiteColor];
    routeView.alpha = 0.8f;
    routeView.layer.shadowOffset = CGSizeMake(5, 5);
    routeView.layer.shadowColor = [UIColor blackColor].CGColor;
    [routeView.layer setShadowOpacity:0.5];
    routeView.imageView.image = [UIImage imageNamed:@"left"];
    return routeView;
}

@end
