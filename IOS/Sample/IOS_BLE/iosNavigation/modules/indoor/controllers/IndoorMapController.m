//
//  IndoorMapViewController.m
//  iosNavigation
//
//  Created by Ievgen on 27.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "IndoorMapController.h"
#import "IndoorStreamController.h"
#import "UIColor+HEX.h"

@interface IndoorMapController () <IndoorStreamControllerDelegate>

@property (nonatomic, strong) Graph *graph;
@property (assign, nonatomic) CGPoint tapPoint;
@property (assign, nonatomic) CGPoint startPoint;
@property (strong, nonatomic) UIImageView *mapView;
@property (strong, nonatomic) DrawingMapView *drawView;
@property (strong, nonatomic) NSDictionary *poisDictionary;
@property (weak, nonatomic) IBOutlet UIView *routeInfoMenu;
@property (weak, nonatomic) IBOutlet UILabel *duratoinLabel;
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;
@property (weak, nonatomic) IBOutlet UIButton *deleteRouteButton;
@property (strong, nonatomic) NSMutableArray *viewOfPoiArray;
@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
@property (strong, nonatomic) UIImageView *currentPositionView;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *menuButton;
@property (weak, nonatomic) IBOutlet RouteInfoView *routeInfoView;
@property (strong, nonatomic) NSArray *maneuversArray;
@property (nonatomic, strong) SessionManager* manager;

@end

@implementation IndoorMapController

- (void)viewDidLoad {
    [super viewDidLoad];
 
    self.routeInfoView = [self createCustomRouteInfoView:self.routeInfoView];
    self.routeInfoView.hidden = YES;
    [self.routeInfoView.layer setShadowOffset:CGSizeMake(5, 5)];
    [self.routeInfoView.layer setShadowColor:[[UIColor blackColor] CGColor]];
    [self.routeInfoView.layer setShadowOpacity:0.5];
    self.routeInfoMenu.backgroundColor = [UIColor colorWithHexString:@"#4154B2"];
    self.routeInfoMenu.hidden = YES;
    self.startPoint = CGPointZero;
    self.viewOfPoiArray = [NSMutableArray array];
    self.poisDictionary = [NSMutableDictionary dictionary];
    _deleteRouteButton.layer.cornerRadius = 22;
    _deleteRouteButton.backgroundColor = [UIColor colorWithHexString:@"#498DFC"];
    [_deleteRouteButton.layer setShadowOffset:CGSizeMake(5, 5)];
    [_deleteRouteButton.layer setShadowColor:[[UIColor blackColor] CGColor]];
    [_deleteRouteButton.layer setShadowOpacity:0.5];
    self.duratoinLabel.text = @"Total duration 0.0 sec";
    self.duratoinLabel.font = [UIFont systemFontOfSize:20];
    self.distanceLabel.text = @"Total distance 0.0 m";
    self.distanceLabel.font = [UIFont systemFontOfSize:14];

    [self createDropdownMenuWihtMenuButton:self.menuButton view:self.view];
    [self addTapGestureOnView:self.mapView selector:@selector(didTap:)];
    [self addTapGestureOnView:self.routeInfoMenu selector:@selector(tapRouteInfoAction:)];
    [[SessionManager sharedManager] getFloorMap:self.floor.mapPath dataType:@"map" floorModel:self.floor withCoplitionBlock:^(FloorModel *map) {
        if(map.mapImage != nil){
            [self setMapImage:map.mapImage];
        }
        else{
        }
    }];
   

    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithHexString:@"#4154B2"];
}
#pragma mark - Create POI Markers -
-(void) createPoiMarkers:(NSDictionary*)poisDic{
 
    NSArray *values = [poisDic allValues];
    
    for(IndoorPOI *poi in values){
        
        CGPoint p = convertPixelToPoint(poi.poiCoordinate, self.mapView.image.size, self.drawView.frame.size);
        UIImageView *poiView = [[UIImageView alloc]initWithFrame:CGRectMake(p.x, p.y, 40, 40)];
        poiView.image = [UIImage imageNamed:@"map_point_icn"];
        poiView.tag = poi.poiID;
        [self addTapGestureOnView:poiView selector:@selector(poiInfo:)];
        [self.viewOfPoiArray addObject:poiView];
        [self.drawView addSubview:poiView];
    }
}
#pragma mark - Call BeaconManager -
-(void) callBeaconManager{
    [[BeaconManager sharedManager] setBeaconMap:self.floor withBeaconData:self.floor.beacons];
    [[BeaconManager sharedManager] startBeacon];
    [BeaconManager sharedManager].delegate = self;
}
#pragma mark - IndoorStreamControllerDelegate -
-(void) refreshRouteWihtStartPoint:(CGPoint)startPoint tapPint:(CGPoint)tapPoint{
    
    [self callBeaconManager];
    if(tapPoint.x > 0 && tapPoint.y > 0){
        dispatch_async(dispatch_get_main_queue(), ^{
            [self drawRouteWithStartPoint:startPoint endPoint:tapPoint];
            self.startPoint = startPoint;
        });
    }
    else{

        self.drawView.pointsArray = nil;
        [self.drawView setNeedsDisplay];
    }
}
#pragma mark - Draw Route -
-(void) drawRouteWithStartPoint:(CGPoint)startPoint endPoint:(CGPoint)endPoint{

    NSArray *pointsList = [self getPointsFromGraph:self.graph withStartPoint:startPoint endPoint:endPoint];
   self.maneuversArray = [self getManeuverWithStartPoint:startPoint pointsArray:pointsList pixelSize:self.floor.mapSizeCof];
    self.isRoute = YES;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        self.routeInfoView.hidden = YES;
        self.routeInfoMenu.hidden = YES;
//        RoutePoint *point = [self.maneuversArray firstObject];
//        self.routeInfoView = [self fillRouteInfoView:self.routeInfoView
//                                            distance:point.tempDistance
//                                            duration:point.tempDuration
//                                                step:point.stepInstruction
//                                            maneuver:[UIImage maneuverImage:point.maneuver]];
//        [self setAllDistanceAndTime:self.maneuversArray];
  });
//
//    NSArray *points = [self convertPoint:pointsList convertType:ConvertTypePoint image:self.mapView.image view:self.drawView];
//    self.drawView = [self drawRouteFromPoints:points onDrawView:self.drawView withStartPoint:startPoint];
//    self.tapPoint = endPoint;
   // CGPoint point = [self tapDetection:gesture onView:self.drawView];
    CGPoint start = {self.drawView.frame.origin.x,self.drawView.frame.origin.y };
    CGPoint destination  = endPoint;

    self.drawView.view = self.drawView;
    self.drawView.img = self.mapView;
    self.drawView.startPoint = start;
    self.drawView.destinationPoint = destination;
    [self.drawView setNeedsDisplay];
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
#pragma mark - Set Map Image -
-(void) setMapImage:(NSData*)imgData{
    
    dispatch_async(dispatch_get_main_queue(), ^{

        self.mapView.image = [UIImage imageWithData:imgData];
        [self callBeaconManager];
        self.drawView = [self createDrawViewWithStartPoint:CGPointZero withSizeView:self.mapView];
             [[SessionManager sharedManager] getIndoorPoiForFloorID:[NSString stringWithFormat:@"%zd", self.floor.idFloor] complitionBlock:^(NSDictionary *poiDictionary) {
            self.poisDictionary = poiDictionary;
            dispatch_async(dispatch_get_main_queue(), ^{
                [self createPoiMarkers:poiDictionary];
                
                self.currentPositionView = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"map_pin_icn"]];
                self.currentPositionView.frame = CGRectMake(0, 0, 25, 40);
                [self.drawView addSubview:self.currentPositionView];
            });
        }];
    });
}
#pragma mark - Tap Gesture -
-(void) didTap:(UITapGestureRecognizer*)gesture{
    
    CGPoint point = [self tapDetection:gesture onView:self.drawView];
    CGPoint start = {self.drawView.frame.origin.x,self.drawView.frame.origin.y };
    CGPoint destination  =  [gesture locationInView:self.drawView];
    
    if(point.x > 0 && point.y > 0){
        self.routeInfoView.hidden = NO;
        self.routeInfoMenu.hidden = NO;
        self.drawView.isDrawRoute = YES;
        self.drawView.view = self.drawView;
        self.drawView.img = self.mapView;
        self.drawView.startPoint = start;
        self.drawView.destinationPoint = destination;
        [self.drawView setNeedsDisplay];

    }
    else{
    
    }

}
#pragma mark - Actions -
-(IBAction) streamButtonAction:(id)sender{
 
    IndoorStreamController *vc = [self.storyboard instantiateViewControllerWithIdentifier:@"IndoorStreamController"];
    vc.floor = self.floor;
    vc.startPoint = self.startPoint;
    if(self.tapPoint.x > 0 && self.tapPoint.y > 0){
    vc.tapPoint = self.tapPoint;
    }
    vc.delegate = self;
    [self.navigationController pushViewController:vc animated:YES];
    self.tapPoint = CGPointZero;
}

-(void) tapRouteInfoAction:(UITapGestureRecognizer*)gesture{
    
    RouteInfoListController *vc = [self.storyboard instantiateViewControllerWithIdentifier:@"RouteInfoListController"];
    
    if(self.isRoute){
        vc.routePoints = self.maneuversArray;
    }

    UINavigationController *nav = [[UINavigationController alloc]initWithRootViewController:vc];
    [self presentViewController:nav animated:YES completion:nil];
}

-(void) poiInfo:(UITapGestureRecognizer*)gesture{
    
    for(UIView *poiView in self.viewOfPoiArray){
      
        CGPoint p = [self tapDetection:gesture onView:poiView];
        
        if([poiView pointInside:p withEvent:nil]){
        
            IndoorPOI *poi = [self.poisDictionary objectForKey:[NSString stringWithFormat:@"%ld",(long)poiView.tag]];
            
            [self createRouteAlertWithTitle:poi.poiName text:poi.poiDescription complitionBlock:^{
                self.drawView.isDrawRoute = YES;
                [self drawRouteWithStartPoint:self.startPoint endPoint:poi.poiCenterCoordinate];
            }];
        }
    }
}

- (IBAction)deleteRouteAction:(UIButton *)sender {
    [self clearRouteAlertWithComplitionBlock:^{
        self.drawView.isDrawRoute = NO;
        [self clearMapInfoContent];
    }];
}
#pragma mark - BeaconManagerDelegate -
-(void)currentLocation:(CGPoint)location{
    
    CGPoint p;
    if (self.floor.widht>0)
    {
        p.x = self.mapView.image.size.width / self.floor.widht *location.x;
    }
    else{
        NSLog(@"Invalid floor width");
           p.x = self.mapView.image.size.width *location.x;
    }
    if (self.floor.height)
    {
        p.y = self.mapView.image.size.height / self.floor.height *location.y;
    }
    else{
        
         NSLog(@"Invalid floor heigth");
         p.y = self.mapView.image.size.height *location.y;
    }


    self.startPoint = p;
    
    p = convertPixelToPoint(p, self.mapView.image.size, self.drawView.frame.size);
    self.currentPositionView.frame = CGRectMake(p.x, p.y, 25, 40);
    
    self.drawView.startPoint = p;
    [self.drawView setNeedsDisplay];
}
#pragma mark - UIScrollViewDelegate -
-(UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView{
    return self.mapView;
}

#pragma mark - Clear Map Content -
-(void) clearMapInfoContent{

    self.isRoute = NO;
    self.routeInfoView.hidden = YES;
    self.routeInfoMenu.hidden = YES;
    self.tapPoint = CGPointMake(-1, -1);
    self.drawView.pointsArray = nil;
    self.drawView.startPoint = CGPointZero;
    [self.drawView setNeedsDisplay];
}


#pragma mark - UI


- (UILabel*)duratoinLabel
{
    if (!_duratoinLabel)
    {
        _duratoinLabel = [UILabel new];
        _duratoinLabel.textAlignment = NSTextAlignmentLeft;
        _duratoinLabel.textColor = [UIColor blackColor];
        _duratoinLabel.numberOfLines = 0;
        _duratoinLabel.font = [UIFont systemFontOfSize:16];
        [self.routeInfoMenu addSubview:_duratoinLabel];
        
        
    }
    return _duratoinLabel;
}
- (UILabel*)distanceLabel
{
    if (!_distanceLabel)
    {
        _distanceLabel = [UILabel new];
        _distanceLabel.textAlignment = NSTextAlignmentLeft;
        _distanceLabel.textColor = [UIColor blackColor];
        _distanceLabel.numberOfLines = 0;
        _distanceLabel.font = [UIFont systemFontOfSize:16];
        [self.routeInfoMenu addSubview:_distanceLabel];
        
        
    }
    return _distanceLabel;
}

@end
