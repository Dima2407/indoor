//
//  StreamInDoorController.m
//  iosNavigation
//
//  Created by Ievgen on 22.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "IndoorStreamController.h"
#import <AVFoundation/AVFoundation.h>
#import "UIColor+HEX.h"

@interface IndoorStreamController() <UIScrollViewDelegate>


@property (weak, nonatomic) IBOutlet UIImageView *mapView;
@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
@property (strong, nonatomic) DrawingMapView *drawView;
@property (weak, nonatomic) IBOutlet UIView *routeInfoMenu;
@property (weak, nonatomic) IBOutlet UILabel *durationLabel;
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;
@property (weak, nonatomic) IBOutlet UIButton *deleteRouteButton;
@property (weak, nonatomic) IBOutlet RouteInfoView *routeInfoView;
@property (strong, nonatomic) UIImageView *currentPositionView;
@property (strong, nonatomic) NSArray *maneuversArray;

@end

@implementation IndoorStreamController
-(void)viewWillAppear:(BOOL)animated{
    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsUseMesh"])
    {
         [[BeaconManager sharedManager] setMode:@"UseMesh"];
        NSArray* mesh = [NSArray arrayWithObjects:@36, @24, @0.3, @0.3, @0, @0,nil];
        NSArray* mask = [NSArray arrayWithObjects:@26,@26,@26,@27,@28,@29,@30,@30,@30,@55,@55,@55,@55,@55,@55,@55,@55,@55,@55,@306,@306,@310,@310,@310,@49,@26,@26,@27,@28,@29,@30,@30,@55,@55,@55,@55,@55,@55,@55,@55,@55,@55,@306,@306,@306,@310,@310,@310,@49,@49,@50,@51,@52,@53,@54,@55,@55,@55,@55,@55,@55,@55,@55,@55,@55,@55,@306,@306,@306,@310,@310,@310,@73,@73,@74,@75,@76,@77,@78,@79,@79,@79,@79,@79,@79,@79,@79,@79,@79,@305,@306,@306,@306,@310,@310,@310,@97,@97,@98,@99,@100,@101,@102,@103,@103,@103,@103,@103,@103,@103,@103,@103,@304,@305,@306,@306,@306,@310,@310,@310,@121,@121,@122,@123,@124,@125,@126,@127,@127,@127,@127,@127,@127,@127,@127,@303,@304,@305,@306,@306,@306,@310,@310,@310,@145,@145,@146,@147,@148,@149,@150,@151,@151,@151,@151,@151,@151,@151,@303,@303,@304,@305,@306,@306,@306,@310,@310,@310,@169,@169,@170,@171,@172,@173,@174,@175,@175,@175,@175,@175,@175,@303,@303,@303,@304,@305,@306,@306,@306,@310,@310,@310,@193,@193,@194,@195,@196,@197,@198,@199,@199,@199,@199,@199,@199,@303,@303,@303,@304,@305,@306,@306,@306,@310,@310,@310,@217,@217,@218,@219,@220,@221,@222,@223,@223,@223,@223,@297,@297,@303,@303,@303,@304,@305,@306,@306,@306,@310,@310,@310,@241,@241,@242,@243,@244,@245,@246,@247,@247,@247,@297,@297,@297,@303,@303,@303,@304,@305,@306,@306,@306,@310,@310,@310,@265,@265,@266,@243,@268,@269,@270,@271,@271,@297,@297,@297,@297,@303,@303,@303,@304,@305,@306,@306,@306,@310,@310,@310,@289,@289,@290,@290,@292,@293,@294,@295,@296,@297,@297,@297,@297,@303,@303,@303,@304,@305,@306,@306,@306,@310,@310,@310,@313,@313,@314,@314,@316,@317,@318,@319,@320,@321,@321,@321,@372,@327,@327,@327,@328,@329,@330,@330,@330,@334,@334,@334,@337,@337,@338,@338,@340,@341,@342,@343,@344,@345,@345,@371,@372,@373,@351,@351,@352,@353,@354,@354,@354,@358,@358,@358,@361,@361,@362,@362,@364,@365,@366,@367,@368,@369,@370,@371,@372,@373,@374,@375,@376,@377,@378,@378,@404,@382,@382,@382,@385,@385,@386,@386,@388,@389,@390,@391,@392,@393,@394,@395,@396,@397,@398,@399,@400,@401,@402,@403,@404,@405,@406,@406,@409,@409,@410,@410,@412,@413,@414,@415,@416,@417,@418,@419,@420,@421,@422,@423,@424,@425,@426,@403,@404,@405,@430,@430,@433,@433,@434,@434,@412,@413,@414,@415,@416,@441,@442,@443,@444,@445,@446,@447,@448,@449,@450,@450,@404,@454,@454,@454,@457,@457,@458,@458,@484,@485,@486,@487,@465,@465,@466,@467,@468,@469,@470,@471,@472,@473,@474,@474,@474,@478,@478,@478,@481,@481,@482,@482,@484,@485,@486,@487,@488,@489,@490,@491,@492,@493,@494,@495,@496,@497,@498,@498,@524,@502,@502,@502,@505,@505,@506,@506,@508,@509,@510,@511,@512,@513,@514,@491,@492,@493,@494,@495,@496,@497,@498,@524,@524,@524,@502,@502,@529,@529,@530,@531,@532,@533,@534,@535,@536,@537,@538,@538,@492,@493,@494,@495,@496,@497,@498,@548,@548,@548,@502,@502,@553,@553,@554,@555,@556,@557,@558,@559,@560,@561,@562,@562,@588,@589,@590,@591,@592,@593,@594,@572,@572,@572,@572,@572,@577,@577,@578,@579,@580,@581,@582,@583,@584,@585,@586,@587,@588,@589,@590,@591,@592,@593,@594,@595,@596,@596,@596,@596,@601,@601,@602,@603,@604,@605,@606,@607,@608,@609,@610,@611,@612,@613,@614,@615,@616,@617,@618,@619,@620,@620,@620,@620,@625,@625,@626,@603,@604,@629,@630,@631,@632,@633,@634,@635,@636,@637,@638,@639,@640,@641,@642,@643,@644,@644,@644,@694,@649,@649,@650,@650,@629,@629,@630,@655,@656,@657,@658,@659,@660,@661,@662,@663,@664,@665,@666,@667,@668,@668,@694,@694,@673,@673,@674,@674,@674,@678,@678,@679,@680,@681,@682,@683,@684,@685,@686,@687,@688,@689,@690,@691,@692,@693,@694,@694,@697,@697,@698,@698,@725,@702,@702,@703,@704,@705,@706,@707,@708,@709,@710,@711,@712,@713,@714,@715,@716,@717,@718,@718,@721,@721,@722,@722,@725,@725,@726,@727,@728,@729,@730,@731,@732,@709,@710,@711,@712,@713,@714,@739,@740,@741,@742,@742,@745,@745,@746,@746,@749,@749,@750,@751,@752,@753,@754,@755,@732,@732,@710,@711,@712,@713,@763,@763,@764,@765,@766,@766,@769,@769,@770,@770,@772,@773,@774,@775,@776,@777,@778,@779,@780,@780,@806,@807,@808,@809,@787,@787,@788,@789,@790,@790,@793,@793,@794,@794,@796,@797,@798,@799,@800,@801,@802,@803,@804,@805,@806,@807,@808,@809,@810,@811,@812,@813,@790,@790,@817,@817,@818,@818,@820,@821,@822,@823,@824,@825,@826,@827,@828,@829,@830,@831,@832,@833,@834,@835,@836,@813,@813,@790,@817,@817,@818,@818,@820,@821,@822,@823,@824,@825,@826,@827,@828,@829,@830,@831,@832,@833,@834,@835,@836,@836,@813,@813, nil];
        
        [[BeaconManager sharedManager] setConfigs:mesh and:mask];
    }
    else{
        [[BeaconManager sharedManager] setMode:@"Standart"];
    }
   
   
   
}
-(void) viewDidLoad{
    [super viewDidLoad];
    
    
    //////////////////////TODO//////////////////////////////
    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRadar"])
    {
        [self createRadarView];
    }
    else{
        self.scrollView.hidden = YES;
    }
    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRout"])
    {
        self.routeInfoView = [self createCustomRouteInfoView:self.routeInfoView];
        self.routeInfoMenu.hidden = NO;
    }
    else{
         self.routeInfoMenu.hidden = YES;
        self.routeInfoView.hidden = YES;
    }
   
   
   
    self.routeInfoMenu.backgroundColor = [UIColor colorWithHexString:@"#4154B2"];
    self.startPoint = CGPointZero;
    _deleteRouteButton.layer.cornerRadius = 22;
    _deleteRouteButton.backgroundColor = [UIColor colorWithHexString:@"#498DFC"];
    [_deleteRouteButton.layer setShadowOffset:CGSizeMake(5, 5)];
    [_deleteRouteButton.layer setShadowColor:[[UIColor blackColor] CGColor]];
    [_deleteRouteButton.layer setShadowOpacity:0.5];
    self.durationLabel.text = @"Total duration 0.0 sec";
    self.durationLabel.font = [UIFont systemFontOfSize:20];
    self.distanceLabel.text = @"Total distance 0.0 m";
    self.distanceLabel.font = [UIFont systemFontOfSize:14];
    [self addTapGestureOnView:self.mapView selector:@selector(didTap:)];
    [self addTapGestureOnView:self.routeInfoMenu selector:@selector(tapRouteInfoAction:)];
    [self getFloorMapData:self.floor.mapPath fileType:@"map" mapModel:self.floor completionBlock:^(FloorModel *map) {
        [self setMapImage:map.mapImage];
    }];
    
    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithHexString:@"#4154B2"];
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
//    
//    CGPoint point = [self tapDetection:gesture onView:self.drawView];
//    
//    if(point.x > 0 && point.y > 0){
//        CGPoint convertPoint = convertPointToPixel(point, self.mapView.image.size, self.drawView.frame.size);
//        dispatch_async(dispatch_get_main_queue(), ^{
//            [self drawRouteWithStartPoint:self.startPoint endPoint:convertPoint];
//        });
//    }
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

- (IBAction)deleteRouteAction:(UIButton *)sender {
    [self clearRouteAlertWithComplitionBlock:^{
        [self clearMapInfoContent];
    }];
}

#pragma mark - UIScrollViewDelegate -
-(UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView{
    return self.mapView;
}
#pragma mark - Draw Route -
-(void) drawRouteWithStartPoint:(CGPoint)startPoint endPoint:(CGPoint)endPoint{
    
    NSArray *pointsList = [self getPointsFromGraph:self.graph withStartPoint:startPoint endPoint:endPoint];
    self.maneuversArray = [self getManeuverWithStartPoint:startPoint pointsArray:pointsList pixelSize:self.floor.mapSizeCof];
    self.isRoute = YES;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        //        self.routeInfoView.hidden = YES;
        //        self.routeInfoMenu.hidden = YES;
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

//    NSArray *pointsList = [self getPointsFromGraph:self.graph withStartPoint:startPoint endPoint:endPoint];
//    self.maneuversArray = [self getManeuverWithStartPoint:startPoint pointsArray:pointsList pixelSize:self.floor.pixelSize];
//    self.isRoute = YES;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        
//        //self.routeInfoView.hidden = YES;
//        //self.routeInfoMenu.hidden = YES;
//        RoutePoint *point = [self.maneuversArray firstObject];
//        self.routeInfoView = [self fillRouteInfoView:self.routeInfoView
//                                            distance:point.tempDistance
//                                            duration:point.tempDuration
//                                                step:point.stepInstruction
//                                            maneuver:[UIImage maneuverImage:point.maneuver]];
//        [self setAllDistanceAndTime:self.maneuversArray];
//    });
//    NSArray *points = [self convertPoint:pointsList convertType:ConvertTypePoint image:self.mapView.image view:self.drawView];
//    self.drawView = [self drawRouteFromPoints:points onDrawView:self.drawView withStartPoint:convertPixelToPoint(startPoint, self.mapView.image.size,self.drawView.frame.size)];
//    self.tapPoint = endPoint;
//    [self.drawView setNeedsDisplay];
//    [self centerScrolViewOnCurrentLocationWithPoint:convertPixelToPoint(startPoint, self.mapView.image.size,self.drawView.frame.size)];
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
    self.routeInfoMenu.hidden = YES;
    self.tapPoint = CGPointMake(-1, -1);
    self.drawView.pointsArray = nil;
    self.drawView.startPoint = CGPointZero;
    [self.drawView setNeedsDisplay];
}
#pragma mark - BeaconManagerDelegate -
-(void)currentLocation:(CGPoint)location{
    
    CGPoint p;
    p.x = self.mapView.image.size.width / self.floor.widht *location.x;
    p.y = self.mapView.image.size.height / self.floor.height *location.y;
    
    self.startPoint = p;
    
    p = convertPixelToPoint(p, self.mapView.image.size, self.drawView.frame.size);
    self.currentPositionView.frame = CGRectMake(p.x, p.y, 12.5f, 20);
    
    self.drawView.startPoint = p;
    [self.drawView setNeedsDisplay];
    [self centerScrolViewOnCurrentLocationWithPoint:p];
}

@end
