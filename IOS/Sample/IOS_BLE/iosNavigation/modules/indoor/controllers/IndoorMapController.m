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
#import <CoreBluetooth/CBCentralManager.h>
#import "UIImage+ManeuverImage.h"
#import "IndoorHeader.h"

@interface IndoorMapController () <IndoorStreamControllerDelegate,CBCentralManagerDelegate>

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
@property (nonatomic, strong) CBCentralManager* centralManager;
@end

@implementation IndoorMapController
-(void)viewWillAppear:(BOOL)animated{
    
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    _centralManager = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
    self.routeInfoView = [self createCustomRouteInfoView:self.routeInfoView];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"kSettingsShowRout"];
    self.routeInfoView.hidden = YES;
    
    self.routeInfoMenu.hidden = YES;
    self.startPoint = CGPointZero;
    self.viewOfPoiArray = [NSMutableArray array];
    self.poisDictionary = [NSMutableDictionary dictionary];
    self.routeInfoMenu.backgroundColor = [UIColor colorWithHexString:@"#4154B2"];
    _deleteRouteButton.layer.cornerRadius = 22;
    _deleteRouteButton.backgroundColor = [UIColor colorWithHexString:@"#498DFC"];
    [_deleteRouteButton.layer setShadowOffset:CGSizeMake(5, 5)];
    [_deleteRouteButton.layer setShadowColor:[[UIColor blackColor] CGColor]];
    [_deleteRouteButton.layer setShadowOpacity:0.5];
    self.duratoinLabel.text = @"Total duration 0.0 sec";
    self.duratoinLabel.font = [UIFont systemFontOfSize:20];
    self.distanceLabel.text = @"Total distance 0.0 m";
    self.distanceLabel.font = [UIFont systemFontOfSize:14];
    
    //[self createDropdownMenuWihtMenuButton:self.menuButton view:self.view];
    [self addTapGestureOnView:self.mapView selector:@selector(didTap:)];
    [self addTapGestureOnView:self.routeInfoMenu selector:@selector(tapRouteInfoAction:)];
    [[SessionManager sharedManager] getFloorMap:self.floor.mapPath dataType:@"map" floorModel:self.floor withCoplitionBlock:^(FloorModel *map) {
        
        
        
        if([UIImage imageWithData:map.mapImage]){
            
            dispatch_async (dispatch_get_main_queue(), ^{
                [self setMapImage:map.mapImage];
                
            });
        }
        else{
            dispatch_async (dispatch_get_main_queue(), ^{
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"ERROR" message:@"Map is empty" delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
                [alert show];
                
            });
            
            
            
        }
    }];
    [[SessionManager sharedManager] getFloorMap:self.floor.graphPath dataType:@"graph" floorModel:self.floor withCoplitionBlock:^(FloorModel *map) {
        if(map.mapGraph != nil){
            NSString *stringFromData = [NSString stringWithUTF8String:[self.floor.mapGraph bytes]];
            if (stringFromData)
            {
                [[BeaconManager sharedManager]setGraph:self.floor withGraph:stringFromData];
            }
            
            
        }
        else{
            NSLog(@"GraphData is nil");
        }
    }];
    
    
    
    
    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithHexString:@"#4154B2"];
    [self.navigationController.navigationBar setTitleTextAttributes:@{NSForegroundColorAttributeName : [UIColor whiteColor]}];
    self.navigationController.navigationBar.backItem.title = @"Back";
  
   
    
}
-(void)startNavigation{

    NSArray* mesh;
    NSArray* mask;
    if ([self.floor.buildingTitle isEqualToString:@"IT-Jim"])
    {
        mesh = [NSArray arrayWithObjects:@37, @25, @0.3, @0.3, @0, @0,nil];
        mask = [NSArray arrayWithObjects:@27, @27, @27, @28, @29, @30, @31, @31, @31, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @348, @348, @348, @348, @51, @27, @27, @28, @29, @30, @31, @31, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @343, @348, @348, @348, @348, @51, @51, @52, @53, @54, @55, @56, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @57, @343, @343, @348, @348, @348, @348, @76, @76, @77, @78, @79, @80, @81, @82, @82, @82, @82, @82, @82, @82, @82, @82, @82, @82, @343, @343, @343, @348, @348, @348, @348, @101, @101, @102, @103, @104, @105, @106, @107, @107, @107, @107, @107, @107, @107, @107, @107, @107, @342, @343, @343, @343, @348, @348, @348, @348, @126, @126, @127, @128, @129, @130, @131, @132, @132, @132, @132, @132, @132, @132, @132, @132, @341, @342, @343, @343, @343, @348, @348, @348, @348, @151, @151, @152, @153, @154, @155, @156, @157, @157, @157, @157, @157, @157, @157, @157, @340, @341, @342, @343, @343, @343, @348, @348, @348, @348, @176, @176, @177, @178, @179, @180, @181, @182, @182, @182, @182, @182, @182, @182, @340, @340, @341, @342, @343, @343, @343, @348, @348, @348, @348, @201, @201, @202, @203, @204, @205, @206, @207, @207, @207, @207, @207, @207, @340, @340, @340, @341, @342, @343, @343, @343, @348, @348, @348, @348, @226, @226, @227, @228, @229, @230, @231, @232, @232, @232, @232, @232, @335, @340, @340, @340, @341, @342, @343, @343, @343, @348, @348, @348, @348, @251, @251, @252, @253, @254, @255, @256, @257, @257, @257, @257, @335, @335, @340, @340, @340, @341, @342, @343, @343, @343, @348, @348, @348, @348, @276, @276, @277, @278, @279, @280, @281, @282, @282, @282, @335, @335, @335, @340, @340, @340, @341, @342, @343, @343, @343, @348, @348, @348, @348, @301, @301, @302, @303, @304, @305, @306, @307, @307, @334, @335, @335, @335, @340, @340, @340, @341, @342, @343, @343, @343, @348, @348, @348, @348, @326, @326, @327, @328, @329, @330, @331, @332, @333, @334, @335, @335, @335, @340, @340, @340, @341, @342, @343, @343, @343, @348, @348, @348, @348, @351, @351, @352, @353, @354, @355, @356, @357, @358, @359, @360, @360, @387, @388, @365, @365, @366, @367, @368, @368, @368, @373, @373, @373, @373, @376, @376, @377, @378, @379, @380, @381, @382, @383, @384, @385, @386, @387, @388, @389, @390, @391, @392, @393, @393, @420, @421, @398, @398, @398, @401, @401, @402, @403, @404, @405, @406, @407, @408, @409, @410, @411, @412, @413, @414, @415, @416, @417, @418, @419, @420, @421, @422, @423, @423, @426, @426, @427, @428, @429, @430, @431, @432, @433, @434, @435, @436, @437, @438, @439, @440, @441, @442, @443, @444, @445, @446, @447, @448, @448, @451, @451, @452, @453, @429, @430, @431, @432, @433, @459, @460, @461, @462, @463, @464, @465, @466, @467, @468, @444, @445, @446, @447, @473, @473, @476, @476, @477, @478, @478, @430, @431, @432, @484, @484, @485, @486, @487, @488, @489, @490, @491, @492, @493, @493, @445, @446, @498, @498, @498, @501, @501, @502, @503, @503, @530, @531, @532, @509, @509, @510, @511, @512, @513, @514, @515, @516, @517, @518, @518, @518, @523, @523, @523, @523, @526, @526, @527, @528, @529, @530, @531, @532, @533, @534, @535, @536, @537, @538, @539, @540, @541, @542, @543, @543, @571, @571, @548, @548, @548, @551, @551, @552, @553, @554, @555, @556, @557, @558, @559, @560, @536, @537, @538, @539, @540, @541, @542, @543, @543, @571, @571, @571, @548, @548, @576, @576, @577, @578, @579, @580, @581, @582, @583, @584, @585, @585, @537, @538, @539, @540, @541, @542, @543, @596, @596, @596, @596, @548, @548, @601, @601, @602, @603, @604, @605, @606, @607, @608, @609, @610, @610, @637, @638, @639, @640, @641, @642, @643, @644, @621, @621, @621, @621, @621, @626, @626, @627, @628, @629, @630, @631, @632, @633, @634, @635, @636, @637, @638, @639, @640, @641, @642, @643, @644, @645, @646, @646, @646, @646, @651, @651, @652, @653, @654, @655, @656, @657, @658, @659, @660, @661, @662, @663, @664, @665, @666, @667, @668, @669, @670, @671, @671, @671, @671, @676, @676, @677, @678, @654, @680, @681, @682, @683, @684, @685, @686, @687, @688, @689, @690, @691, @692, @693, @694, @695, @696, @696, @696, @748, @701, @701, @702, @703, @703, @680, @681, @707, @708, @709, @710, @686, @687, @688, @689, @690, @691, @692, @693, @694, @695, @696, @747, @748, @748, @726, @726, @727, @728, @728, @731, @731, @732, @733, @734, @735, @736, @737, @738, @739, @740, @741, @742, @743, @744, @745, @746, @747, @748, @748, @751, @751, @752, @753, @753, @756, @756, @757, @758, @759, @760, @761, @762, @763, @764, @765, @766, @767, @768, @769, @770, @771, @772, @773, @773, @776, @776, @777, @778, @778, @780, @781, @782, @783, @784, @785, @786, @787, @763, @764, @765, @766, @767, @768, @794, @795, @796, @797, @798, @798, @801, @801, @802, @803, @803, @805, @806, @807, @808, @809, @810, @811, @787, @787, @764, @765, @766, @767, @794, @794, @820, @821, @822, @823, @823, @826, @826, @827, @828, @829, @830, @831, @832, @833, @834, @835, @836, @837, @837, @864, @865, @866, @867, @844, @844, @845, @846, @847, @848, @848, @851, @851, @852, @853, @854, @855, @856, @857, @858, @859, @860, @861, @862, @863, @864, @865, @866, @867, @868, @869, @870, @871, @872, @848, @848, @876, @876, @877, @878, @879, @880, @881, @882, @883, @884, @885, @886, @887, @888, @889, @890, @891, @892, @893, @894, @895, @896, @872, @872, @848, @876, @876, @877, @878, @879, @880, @881, @882, @883, @884, @885, @886, @887, @888, @889, @890, @891, @892, @893, @894, @895, @896, @896, @872, @872, nil];
    }
    
    else if([self.floor.buildingTitle isEqualToString:@"Kaa Solutions"]){

        mesh = [NSArray arrayWithObjects:@22, @44, @0.3, @0.3, @0, @0,nil];
        
        mask = [NSArray arrayWithObjects:@45, @45, @46, @47, @48, @49, @50, @51, @52, @53, @54, @55, @56, @57, @58, @59, @60, @61, @62, @63, @64, @65, @66, @67, @68, @69, @70, @71, @72, @73, @74, @75, @76, @77, @78, @79, @80, @81, @82, @83, @84, @85, @86, @86, @45, @45, @46, @47, @48, @49, @50, @51, @52, @53, @54, @55, @56, @57, @58, @59, @60, @61, @62, @63, @64, @65, @66, @67, @68, @69, @70, @71, @72, @73, @74, @75, @76, @77, @78, @79, @80, @81, @82, @83, @84, @85, @86, @86, @89, @89, @90, @91, @92, @93, @94, @95, @96, @97, @98, @99, @100, @101, @102, @103, @104, @105, @106, @107, @108, @109, @110, @111, @112, @113, @114, @115, @116, @117, @118, @119, @120, @121, @122, @123, @124, @125, @126, @127, @128, @129, @130, @130, @133, @133, @134, @135, @136, @137, @138, @139, @140, @141, @142, @143, @144, @145, @146, @147, @148, @149, @150, @151, @152, @153, @154, @155, @156, @157, @158, @159, @160, @161, @162, @163, @164, @165, @166, @167, @168, @169, @170, @171, @172, @173, @174, @174, @177, @177, @178, @179, @180, @181, @182, @183, @184, @185, @186, @187, @188, @189, @190, @191, @192, @193, @194, @195, @196, @197, @198, @155, @156, @201, @202, @203, @204, @205, @206, @207, @164, @165, @210, @211, @212, @213, @214, @215, @216, @217, @218, @218, @221, @221, @222, @223, @224, @225, @226, @227, @228, @229, @230, @231, @232, @233, @234, @235, @236, @237, @238, @239, @240, @241, @242, @242, @245, @245, @246, @247, @248, @249, @250, @251, @251, @254, @254, @255, @256, @257, @258, @259, @260, @261, @262, @262, @265, @265, @266, @267, @268, @269, @270, @271, @272, @273, @274, @275, @276, @277, @278, @279, @280, @281, @282, @283, @284, @285, @286, @286, @245, @245, @246, @247, @248, @249, @250, @251, @251, @298, @298, @299, @300, @301, @302, @303, @304, @305, @306, @306, @309, @309, @310, @311, @312, @313, @314, @315, @316, @317, @318, @319, @320, @321, @322, @323, @324, @325, @326, @327, @328, @329, @330, @330, @376, @377, @378, @379, @380, @381, @382, @383, @384, @342, @342, @343, @344, @345, @346, @347, @348, @349, @350, @350, @353, @353, @354, @355, @356, @357, @358, @359, @360, @361, @362, @363, @364, @365, @366, @367, @368, @369, @370, @371, @372, @373, @374, @375, @376, @377, @378, @379, @380, @381, @382, @383, @384, @385, @386, @387, @388, @389, @390, @391, @392, @393, @394, @394, @397, @397, @398, @399, @400, @401, @402, @403, @404, @405, @406, @407, @408, @409, @410, @411, @412, @413, @414, @415, @416, @417, @418, @419, @420, @421, @422, @423, @424, @425, @426, @427, @428, @429, @430, @431, @432, @433, @434, @435, @436, @437, @438, @438, @441, @441, @442, @443, @444, @445, @446, @447, @448, @449, @450, @451, @452, @453, @454, @455, @456, @457, @458, @459, @460, @461, @462, @463, @464, @465, @466, @467, @468, @469, @470, @471, @472, @473, @474, @475, @476, @477, @478, @479, @480, @481, @482, @482, @485, @485, @486, @487, @488, @489, @490, @491, @492, @493, @494, @495, @496, @497, @498, @499, @500, @501, @502, @503, @504, @505, @506, @507, @508, @509, @510, @511, @512, @513, @514, @515, @516, @517, @518, @519, @520, @521, @522, @523, @524, @525, @526, @526, @529, @529, @530, @531, @532, @533, @534, @535, @536, @537, @538, @539, @540, @541, @542, @543, @500, @501, @502, @547, @548, @549, @550, @551, @552, @553, @510, @511, @556, @557, @558, @559, @516, @517, @518, @563, @564, @565, @566, @523, @524, @525, @570, @570, @573, @573, @574, @575, @576, @577, @578, @579, @580, @581, @582, @583, @584, @585, @586, @587, @587, @501, @591, @591, @592, @593, @594, @595, @596, @597, @597, @600, @600, @601, @602, @603, @603, @517, @607, @607, @608, @609, @610, @610, @524, @614, @614, @614, @617, @617, @618, @619, @620, @621, @622, @623, @624, @625, @626, @627, @628, @629, @630, @631, @631, @631, @591, @591, @592, @593, @594, @595, @596, @597, @597, @644, @644, @645, @646, @647, @647, @647, @607, @607, @608, @609, @610, @610, @658, @658, @658, @658, @661, @661, @662, @663, @620, @621, @622, @623, @624, @625, @626, @671, @672, @673, @674, @675, @675, @720, @591, @591, @592, @593, @594, @595, @596, @597, @731, @688, @688, @689, @690, @691, @691, @736, @607, @607, @608, @609, @610, @610, @745, @702, @702, @702, @705, @705, @706, @707, @707, @621, @755, @755, @756, @757, @715, @715, @716, @717, @718, @719, @720, @720, @720, @591, @592, @593, @594, @595, @596, @731, @731, @731, @732, @733, @734, @735, @736, @736, @736, @607, @608, @609, @610, @745, @745, @745, @746, @746, @749, @749, @750, @751, @751, @751, @755, @755, @756, @757, @758, @759, @760, @761, @762, @763, @764, @764, @764, @855, @856, @857, @858, @859, @860, @775, @775, @775, @776, @777, @778, @779, @780, @780, @780, @871, @872, @873, @874, @789, @789, @789, @790, @790, @793, @793, @794, @795, @795, @841, @799, @799, @800, @801, @802, @803, @804, @805, @806, @807, @808, @808, @854, @855, @856, @857, @858, @859, @860, @861, @819, @819, @820, @821, @822, @823, @824, @824, @870, @871, @872, @873, @874, @875, @833, @833, @834, @834, @837, @837, @838, @839, @840, @841, @842, @843, @844, @845, @846, @847, @848, @849, @850, @851, @852, @853, @854, @855, @856, @857, @858, @859, @860, @861, @862, @863, @864, @865, @866, @867, @868, @869, @870, @871, @872, @873, @874, @875, @876, @877, @878, @878, @881, @881, @882, @883, @884, @885, @886, @887, @888, @889, @890, @891, @892, @893, @894, @895, @896, @897, @898, @899, @900, @901, @902, @903, @904, @905, @906, @907, @908, @909, @910, @911, @912, @913, @914, @915, @916, @917, @918, @919, @920, @921, @922, @922, @881, @881, @882, @883, @884, @885, @886, @887, @888, @889, @890, @891, @892, @893, @894, @895, @896, @897, @898, @899, @900, @901, @902, @903, @904, @905, @906, @907, @908, @909, @910, @911, @912, @913, @914, @915, @916, @917, @918, @919, @920, @921, @922, @922, nil];
        
    }
    else{
        NSLog(@"undefined building name");
    }
    if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLENavigationSwitch] ||[[NSUserDefaults standardUserDefaults] boolForKey:kSensorNavigationSwitch])
    {
        if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLENavigationSwitch])
        {
            
            NSString *filter = nil;
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLECircleSwitch])
            {
                filter = @"CircleBuffers";
            }
            
            else if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLEKalmanSwitch]){
                filter = @"KalmanFilter";
                
            }
            int usemap = 0;
            int useWalls = 0;
            int useMask = 0;
            int useMultilat = 0;
            
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLETrilatirationSwitch]){
                useMultilat = 1;
                
            }
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLEMapSwitch])
            {
                usemap = 1;
            }
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLEWallsSwitch])
            {
                useWalls = 1;
            }
            [[BeaconManager sharedManager] setMesh:mesh and:mask];
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLEMeshSwitch])
            {
                
                useMask = 1;
            }
            [[BeaconManager sharedManager] setBeaconConfig:filter useMultilat:useMultilat useMap:usemap useMesh:useMask useWalls:useWalls ];
        }
        else if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorNavigationSwitch])
        {
            NSString *filter = nil;
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorManual])
            {
                filter = @"Manual";
            }
            else if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorRSSIAveraging])
            {
                filter = @"RSSIAveraging";
                
                
            }
            else if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorKalmanSwitch])
            {
                filter = @"KalmanFilter";
                
            }
            int usemap = 0;
            int useWalls = 0;
            int useMask = 0;
            
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorMapCorrectionSwitch])
            {
                usemap = 1;
            }
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorWallsCorrectionSwitch])
            {
                useWalls = 1;
            }
            [[BeaconManager sharedManager] setMesh:mesh and:mask];
            if ([[NSUserDefaults standardUserDefaults] boolForKey:kSensorMeshCorrectionSwitch])
            {
                
                useMask = 1;
            }
            
            [[BeaconManager sharedManager] setSensorConfig:filter useMap:usemap useMesh:useMask useWalls:useWalls x:[[NSUserDefaults standardUserDefaults] doubleForKey:kSensorX] y:[[NSUserDefaults standardUserDefaults] doubleForKey:kSensorY]];
            
            
        }
    }
    else{
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Error" message:@"Turn on navigation" preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *buildRoutAction = [UIAlertAction actionWithTitle:@"ok" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            
        }];
        UIAlertAction *canselAction = [UIAlertAction actionWithTitle:@"Close" style:UIAlertActionStyleDestructive handler:nil];
        [alert addAction:buildRoutAction];
        [alert addAction:canselAction];
        [self presentViewController:alert animated:YES completion:nil];
    }
    
    [self callBeaconManager];
    
}
-(void)viewWillDisappear:(BOOL)animated{
    //[[BeaconManager sharedManager] stopBeacon];
}


#pragma mark - CBCentralManagerDelegate -
- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    if (central.state == CBCentralManagerStatePoweredOn) {
        //Bluetooth is on
    } else if(central.state == CBCentralManagerStatePoweredOff) {
        //Bluetooth is disabled
    }
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
    [[BeaconManager sharedManager] startBeacon];
    if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLENavigationSwitch] || [[NSUserDefaults standardUserDefaults] boolForKey:kSensorRSSIAveraging])
    {
        [[BeaconManager sharedManager] setBeaconMap:self.floor withBeaconData:self.floor.beacons];
    }
    [BeaconManager sharedManager].delegate = self;
}
#pragma mark - IndoorStreamControllerDelegate -
-(void) refreshRouteWihtStartPoint:(CGPoint)startPoint tapPint:(CGPoint)tapPoint{
    
    
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
    
    
    
    self.drawView.view = self.drawView;
    self.drawView.img = self.mapView;
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
    
    dispatch_async (dispatch_get_main_queue(), ^{
        [self startNavigation];
        UIImage *map = [UIImage imageWithData:imgData];
        
        self.mapView.image = map;
        self.drawView = [self createDrawViewWithStartPoint:CGPointZero withSizeView:self.mapView];
        
        [[SessionManager sharedManager] getIndoorPoiForFloorID:[NSString stringWithFormat:@"%zd", self.floor.idFloor] complitionBlock:^(NSDictionary *poiDictionary) {
            dispatch_async(dispatch_get_main_queue(), ^{
                self.poisDictionary = poiDictionary;
                
                [self createPoiMarkers:poiDictionary];
                self.currentPositionView = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"map_pin_icn"]];
                self.currentPositionView.frame = CGRectMake(0, 0, 25, 40);
                [self.drawView addSubview:self.currentPositionView];
                [self.view setNeedsDisplay];
            });
            
        }];
        
    });
    
}
#pragma mark - Tap Gesture -
-(void) didTap:(UITapGestureRecognizer*)gesture{
    if ( [[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRout"])
    {
        NSLog(@"You have choosen destination already");
    }
    else{
        CGPoint point = [self tapDetection:gesture onView:self.drawView];
        self.tapPoint = point;
        CGPoint destination  = {self.mapView.image.size.width /self.mapView.frame.size.width  * point.x * self.floor.pixelSize,self.mapView.image.size.height /self.mapView.frame.size.height  * point.y * self.floor.pixelSize };
        [[BeaconManager sharedManager] setDestination:destination];
        if(point.x > 0 && point.y > 0){
            self.routeInfoView.hidden = NO;
            self.routeInfoMenu.hidden = NO;
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"kSettingsShowRout"];
            
            self.drawView.isDrawRoute = YES;
            self.drawView.view = self.drawView;
            self.drawView.img = self.mapView;
            [self.drawView setNeedsDisplay];
            
        }
        else{
            
        }
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
    
    if([[NSUserDefaults standardUserDefaults] boolForKey:@"kSettingsShowRout"]){
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
                self.routeInfoView.hidden = NO;
                self.routeInfoMenu.hidden = NO;
                [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"kSettingsShowRout"];
                
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
 
    if([[NSUserDefaults standardUserDefaults] boolForKey:kBLECircleSwitch]||[[NSUserDefaults standardUserDefaults] boolForKey:kSensorRSSIAveraging]){
        if (CGPointEqualToPoint(location, CGPointZero))
        {
            
            self.navigationController.navigationBar.topItem.title = @"Initialization...";
            CGPoint p = CGPointMake(0, 0);
            self.startPoint = p;
            
            self.drawView.startPoint = p;
            [self.drawView setNeedsDisplay];
        }
        else{
            self.navigationController.navigationBar.topItem.title = @"";
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
            self.currentPositionView.frame = CGRectMake(p.x-25/2, p.y-40, 25, 40);
            p.x = p.x;
            p.y = p.y;
            self.drawView.startPoint = p;
            [self.drawView setNeedsDisplay];
        }
        
    }
    else{
        self.navigationController.navigationBar.topItem.title = @"";
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
        self.currentPositionView.frame = CGRectMake(p.x-25/2, p.y-40, 25, 40);
        p.x = (int)p.x;
        p.y = (int)p.y;
        self.drawView.startPoint = p;
        [self.drawView setNeedsDisplay];
    }
}
-(void)currentRouting:(NSArray *)way{
    if (way!=nil)
    {
        
        NSMutableArray* points = [NSMutableArray new];
        [way enumerateObjectsUsingBlock:^(NSDictionary*  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            CGPoint location = CGPointMake([[obj objectForKey:@"x"] floatValue], [[obj objectForKey:@"y"] floatValue]);
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
            
            p = convertPixelToPoint(p, self.mapView.image.size, self.drawView.frame.size);
            
            
            [points addObject:[NSValue valueWithCGPoint:p]];
        }];
        
        self.drawView.pointsArray = [points copy];
        CGFloat distance = [[BeaconManager sharedManager] getDistance] * self.floor.pixelSize;
        self.distanceLabel.text = [NSString stringWithFormat:@"Total distance %.2f m", distance];
        self.duratoinLabel.text =  calculateTimeDuration(distance);
        self.maneuversArray =   calculateManeuverWithStartPoint(CGPointZero, points, self.floor.pixelSize);
        //NSLog(@"%@",temp);
        RoutePoint* firstPoint = [self.maneuversArray firstObject];
        self.routeInfoView.imageView.image = [UIImage maneuverImage: firstPoint.maneuver ];
        self.routeInfoView.distance.text = firstPoint.maneuver;
    }
    else{
        //NSLog(@"Routing array is nil");
    }
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
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"kSettingsShowRout"];
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
