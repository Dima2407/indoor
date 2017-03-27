//
//  BeaconListController.m
//  iosNavigation
//
//  Created by Ievgen on 22.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "BeaconListController.h"
#import "BeaconCell.h"
#import "BeaconManager.h"

@interface BeaconListController () <UITableViewDelegate, UITableViewDataSource, BeaconManagerDelegate>

@property (weak, nonatomic) IBOutlet UIBarButtonItem *menuButton;
@property (strong, nonatomic) NSArray *beaconsArray;
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) BeaconManager *manager;

@end

@implementation BeaconListController

-(void)viewDidLoad{
    [super viewDidLoad];
    
   self.manager = [BeaconManager sharedManager];
     self.manager.delegate = self;
}

#pragma mark - BeaconListDelegate -
-(void) refreshBeaconList:(NSArray *)beaons{
    self.beaconsArray = beaons;
    [self.tableView reloadData];
}

#pragma mark - UITableViewDataSource -
-(NSInteger) tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    if(self.beaconsArray.count > 1){
    return self.beaconsArray.count;
    }
    else{
        return 0;
    }
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    static NSString *identifier = @"Cell";
    
    BeaconCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    
    if(!cell){
      cell = [[BeaconCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];
    }
    
    CLBeacon *beacon = [self.beaconsArray objectAtIndex:indexPath.row];
    
    NSArray *array = [[NSString stringWithFormat:@"%@",beacon.proximityUUID] componentsSeparatedByString:@">"];
    
    cell.proximityUUID.text = [array lastObject];
    cell.proximity.text = [NSString stringWithFormat:@"%ld",beacon.proximity];
    cell.major.text = [NSString stringWithFormat:@"%@",beacon.major];
    cell.minor.text = [NSString stringWithFormat:@"%@",beacon.minor];
    cell.rssi.text = [NSString stringWithFormat:@"%ld",beacon.rssi];
    cell.accurasi.text = [NSString stringWithFormat:@"%f",beacon.accuracy];
    return cell;
}

@end
