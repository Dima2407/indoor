//
//  InDoorViewController.m
//  iosNavigation
//
//  Created by Ievgen on 20.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "IndoorTableController.h"
#import "IndoorMapController.h"
#import "SWRevealViewController.h"
#import <CoreLocation/CoreLocation.h>
#import "IndoorMainController.h"
#import "SessionManager.h"
#import "BeaconManager.h"
#import "MapModel.h"
#import "ApiRoutes.h"
#import "FloorTableViewController.h"
#import "BuildingModel.h"



@interface IndoorTableController () <CLLocationManagerDelegate, UITableViewDelegate,UITableViewDataSource>

@property (weak, nonatomic) IBOutlet UIBarButtonItem *menuButton;
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) NSArray *mapsArray;
@property (nonatomic, strong) SessionManager *manager;


@end


@implementation IndoorTableController

-(void)viewWillAppear:(BOOL)animated{
   
}
- (void)viewDidLoad {
    
   
    [super viewDidLoad];
  
   
   
    [[SessionManager sharedManager] getMapListWithComplitionBlock:^(NSArray *buildingList) {
        if (!buildingList) {
            return;
        }
        self.mapsArray = buildingList;
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.tableView reloadData];
        });
    }];
    
    [self createDropdownMenu];
   
    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithRed:0.376f green:0.325f blue:1.f alpha:0.8f];
    self.navigationItem.leftBarButtonItem = nil;
    self.navigationItem.hidesBackButton = YES;
}

#pragma mark - Get Notification
- (void)didGetNotification:(NSNotification*)notification {
    
    dispatch_async(dispatch_get_main_queue(), ^{
       // self.mapsArray = [notification object];
        
        [self.tableView reloadData];
   
    });
}


#pragma mark - Create Drop Down Menu -
-(void) createDropdownMenu{
    
    SWRevealViewController *revealViewController = self.revealViewController;
    if ( revealViewController )
    {
        self.revealViewController.rearViewRevealWidth = self.view.bounds.size.width * 0.8f;
        [self.menuButton setTarget: self.revealViewController];
        [self.menuButton setAction: @selector( revealToggle: )];
        [self.view addGestureRecognizer:self.revealViewController.panGestureRecognizer];
    }
}

#pragma mark - UITableViewDataSource -
-(NSInteger) tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.mapsArray.count;
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
 
    static NSString *identifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    
    if(!cell){
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:identifier];
    }
    BuildingModel *building = [self.mapsArray objectAtIndex:indexPath.row];
    cell.textLabel.text = building.buildingTitle;
    cell.detailTextLabel.text = building.buildingSubtitle;
    return cell;
}
//
//-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
//    
//    MapModel *map = [self.mapsArray objectAtIndex:indexPath.row];
//    IndoorMapController *vc = [self.storyboard instantiateViewControllerWithIdentifier:@"IndoorMapController"];
//    vc.map = map;
//    [self.navigationController pushViewController:vc animated:YES];
//}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    BuildingModel *building = [self.mapsArray objectAtIndex:indexPath.row];
    FloorTableViewController *vc = [self.storyboard instantiateViewControllerWithIdentifier:@"FloorVC"];
    vc.map = building;
    [self.navigationController pushViewController:vc animated:YES];
}
- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    
}

@end

