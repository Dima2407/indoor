//
//  StreamInDoorController.m
//  iosNavigation
//
//  Created by Ievgen on 22.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "IndoorStreamController.h"
#import <AVFoundation/AVFoundation.h>

@interface IndoorStreamController() <UIScrollViewDelegate>

@property (weak, nonatomic) IBOutlet UIBarButtonItem *menuButton;
@property (weak, nonatomic) IBOutlet UIImageView *mapView;
@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
@property (strong, nonatomic) DrawingMapView *drawView;
@property (weak, nonatomic) IBOutlet UIView *routeInfoMenu;
@property (weak, nonatomic) IBOutlet RouteInfoView *routeInfoView;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *clearRouteButton;
@property (strong, nonatomic) UIImageView *currentPositionView;
@property (strong, nonatomic) NSArray *maneuversArray;

@end

@implementation IndoorStreamController

-(void) viewDidLoad{
    [super viewDidLoad];
    
    
    //////////////////////TODO//////////////////////////////
//    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRadar"])
//    {
//        [self createRadarView];
//    }
//    else{
//        self.scrollView.hidden = YES;
//    }
//    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRout"])
//    {
//        self.routeInfoView = [self createCustomRouteInfoView:self.routeInfoView];
//    }
    /////////////////////////////////////////////////////////
    [self createRadarView];
     self.routeInfoView = [self createCustomRouteInfoView:self.routeInfoView];
    self.routeInfoView.hidden = YES;
    self.clearRouteButton.enabled = NO;
    [self addTapGestureOnView:self.mapView selector:@selector(didTap:)];
    [self addTapGestureOnView:self.routeInfoMenu selector:@selector(tapRouteInfoAction:)];
    [self createDropdownMenuWihtMenuButton:self.menuButton view:self.view];
    [self getFloorMapData:self.floor.mapPath fileType:@"map" mapModel:self.floor completionBlock:^(FloorModel *map) {
        [self setMapImage:map.mapImage];
    }];
//    [self getFloorMapData:self.map.mapID floor:@"5" fileType:@"map" mapModel:self.floor mapModel:self.map completionBlock:^(FloorModel *map) {
//        [self setMapImage:map.mapImage];
//    }];
//    [self getFloorMapData:self.map.mapID floor:@"5" fileType:@"graph" mapModel:self.floor mapModel:self.map completionBlock:^(FloorModel *map) {
//        [self setMapImage:map.mapImage];
//    }];
    
    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithRed:0.376f green:0.325f blue:1.f alpha:0.8f];
}
#pragma mark - Set Map Image -
-(void) setMapImage:(NSData*)imgData{
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        self.mapView.image = [UIImage imageWithData:imgData];
        [[BeaconManager sharedManager] startBeacon];
        [BeaconManager sharedManager].delegate = self;
        [[BeaconManager sharedManager] setBeaconMap:self.floor withBeaconData:self.floor.beacons];
        CGPoint p = convertPixelToPoint(self.startPoint, self.mapView.image.size, self.drawView.frame.size);
        
       self.drawView = [self createDrawViewWithStartPoint:p withSizeView:self.mapView];
       [self centerScrolViewOnCurrentLocationWithPoint:p];
        
        self.currentPositionView = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"map_pin_icn"]];
        self.currentPositionView.frame = CGRectMake(0, 0, 12.5, 20);
        [self.drawView addSubview:self.currentPositionView];
    
        if(self.tapPoint.x > 0 && self.tapPoint.y > 0){
            
            dispatch_async(dispatch_get_main_queue(), ^{
                
                [self drawRouteWithStartPoint:self.startPoint endPoint:self.tapPoint];
                [self centerScrolViewOnCurrentLocationWithPoint:p];
            });
        }
    });
}
#pragma mark - Tap Gesture -
-(void) didTap:(UITapGestureRecognizer*)gesture{
    
    CGPoint point = [self tapDetection:gesture onView:self.drawView];
    
    if(point.x > 0 && point.y > 0){
        CGPoint convertPoint = convertPointToPixel(point, self.mapView.image.size, self.drawView.frame.size);
        dispatch_async(dispatch_get_main_queue(), ^{
            [self drawRouteWithStartPoint:self.startPoint endPoint:convertPoint];
        });
    }
}
#pragma mark - Create radar view -
-(void) createRadarView{
    
    self.scrollView.layer.cornerRadius = self.scrollView.frame.size.height / 2;
    self.scrollView.layer.borderWidth = 4.f;
    self.scrollView.layer.borderColor = [UIColor lightGrayColor].CGColor;
}
#pragma mark - Actions -
-(IBAction) mapButtonAction:(id)sender{
    [self.delegate refreshRouteWihtStartPoint:self.startPoint tapPint:self.tapPoint];
    [self.navigationController popViewControllerAnimated:YES];
}

-(void) tapRouteInfoAction:(UITapGestureRecognizer*)gesture{
    
    RouteInfoListController *vc = [self.storyboard instantiateViewControllerWithIdentifier:@"RouteInfoListController"];
    
    if(self.isRoute){
        vc.routePoints = self.maneuversArray;
    }
    
    UINavigationController *nav = [[UINavigationController alloc]initWithRootViewController:vc];
    [self presentViewController:nav animated:YES completion:nil];
}

-(IBAction) clearRouteAction:(id)sender{
    [self clearRouteAlertWithComplitionBlock:^{
        [self clearMapInfoContent];
    }];
}

-(IBAction) mapList:(id)sender{
    NSArray *viewControllers = self.navigationController.viewControllers;
    UIViewController *rootViewController = [viewControllers objectAtIndex:viewControllers.count - 4];
    [self.navigationController popToViewController:rootViewController animated:YES];
}
#pragma mark - UIScrollViewDelegate -
-(UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView{
    return self.mapView;
}
#pragma mark - Draw Route -
-(void) drawRouteWithStartPoint:(CGPoint)startPoint endPoint:(CGPoint)endPoint{
    
    NSArray *pointsList = [self getPointsFromGraph:self.graph withStartPoint:startPoint endPoint:endPoint];
    self.maneuversArray = [self getManeuverWithStartPoint:startPoint pointsArray:pointsList pixelSize:self.floor.pixelSize];
    self.isRoute = YES;
    dispatch_async(dispatch_get_main_queue(), ^{
        
        self.routeInfoView.hidden = NO;
        RoutePoint *point = [self.maneuversArray firstObject];
        self.routeInfoView = [self fillRouteInfoView:self.routeInfoView
                                            distance:point.tempDistance
                                            duration:point.tempDuration
                                                step:point.stepInstruction
                                            maneuver:[UIImage maneuverImage:point.maneuver]];
        [self setAllDistanceAndTime:self.maneuversArray];
    });
    NSArray *points = [self convertPoint:pointsList convertType:ConvertTypePoint image:self.mapView.image view:self.drawView];
    self.drawView = [self drawRouteFromPoints:points onDrawView:self.drawView withStartPoint:convertPixelToPoint(startPoint, self.mapView.image.size,self.drawView.frame.size)];
    self.tapPoint = endPoint;
    [self.drawView setNeedsDisplay];
    self.clearRouteButton.enabled = YES;
    [self centerScrolViewOnCurrentLocationWithPoint:convertPixelToPoint(startPoint, self.mapView.image.size,self.drawView.frame.size)];
}
#pragma mark - Set Distance and Time -
-(void) setAllDistanceAndTime:(NSArray*)array{
    
    CGFloat allDistance = 0;
    CGFloat allTime = 0;
    
    for(RoutePoint *point in array){
        
        allDistance += [point.tempDistance floatValue];
        allTime += [point.tempDistance floatValue];
    }
    
    self.title = [NSString stringWithFormat:@"Distance: %1.2fm  Time: %1.2fsec",allDistance,allTime];
    [self.navigationController.navigationBar setTitleTextAttributes:
     @{NSForegroundColorAttributeName:[UIColor whiteColor]}];
}
#pragma mark - Center ScrollView On Current Location -
-(void) centerScrolViewOnCurrentLocationWithPoint:(CGPoint)point{
    
   [self.scrollView setZoomScale:2.f];
    
    [self.scrollView scrollRectToVisible:
     CGRectMake(point.x - 30,
                point.y + 70,
                self.scrollView.frame.size.width,
                self.scrollView.frame.size.height) animated:YES];
}
#pragma mark - Clear Map Content -
-(void) clearMapInfoContent{
    
    self.isRoute = NO;
    self.routeInfoView.hidden = YES;
    self.tapPoint = CGPointMake(-1, -1);
    self.clearRouteButton.enabled = NO;
    self.drawView.pointsArray = nil;
    self.drawView.startPoint = CGPointZero;
    [self.drawView setNeedsDisplay];
}
#pragma mark - BeaconManagerDelegate -
-(void)currentLocation:(CGPoint)location{
    
    CGPoint p;
    p.x = self.mapView.image.size.width / 11 *location.x;
    p.y = self.mapView.image.size.height / 7 *location.y;
    
    self.startPoint = p;
    
    p = convertPixelToPoint(p, self.mapView.image.size, self.drawView.frame.size);
    self.currentPositionView.frame = CGRectMake(p.x, p.y, 12.5f, 20);
    
    self.drawView.startPoint = p;
    [self.drawView setNeedsDisplay];
    [self centerScrolViewOnCurrentLocationWithPoint:p];
}

@end
