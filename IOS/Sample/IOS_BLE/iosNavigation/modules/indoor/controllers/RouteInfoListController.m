//
//  RouteInfoListController.m
//  iosNavigation
//
//  Created by Ievgen on 26.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "RouteInfoListController.h"
#import "UIImage+ManeuverImage.h"
#import "RouteInfoCell.h"
#import "RoutePoint.h"
#import "UIColor+HEX.h"

@interface RouteInfoListController ()

@end

@implementation RouteInfoListController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithHexString:@"#4154B2"];
}
#pragma mark - UITableViewDataSource -
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.routePoints.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *identifier = @"Cell";
    RouteInfoCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier forIndexPath:indexPath];
    
    if(!cell){
        cell = [[RouteInfoCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];
    }
    
    RoutePoint *point = [self.routePoints objectAtIndex:indexPath.row];
    
    cell.instructionLabel.text = point.stepInstruction;
    cell.distanceLabel.text = point.tempDistance;
    cell.durationLabel.text = point.tempDuration;
    cell.image.image = [UIImage maneuverImage:point.maneuver];
    return cell;
}
#pragma mark - Actions -
-(IBAction) canselAction:(id)sender{
    [self dismissViewControllerAnimated:self completion:nil];
}

@end
