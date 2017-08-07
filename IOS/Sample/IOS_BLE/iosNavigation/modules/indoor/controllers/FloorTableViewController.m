//
//  FloorTableViewController.m
//  iosNavigation
//
//  Created by AppleFace on 21.02.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import "FloorTableViewController.h"
#import "SessionManager.h"
#import "IndoorMapController.h"
#import "IndoorStreamController.h"
#import "FloorModel.h"
#import "UIColor+HEX.h"
#import "IndoorHeader.h"
@interface FloorTableViewController ()
@property (weak, nonatomic) IBOutlet UIBarButtonItem *menuButton;
//@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) NSArray *mapsArray;
@property (nonatomic, strong) SessionManager* manager;
@property (nonatomic, strong) NSArray *floors;
@end

@implementation FloorTableViewController


-(void)viewDidAppear:(BOOL)animated{
   
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self createDropdownMenu];
    self.navigationController.navigationBar.tintColor = [UIColor whiteColor];
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithHexString:@"#4154B2"];
}



#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {

    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {

    return self.map.froorsArray.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *identifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    
    if(!cell){
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:identifier];
    }

    
    FloorModel *floor = self.map.froorsArray[indexPath.row];
    cell.textLabel.text = [ NSString stringWithFormat:@"Floor %ld",(long)floor.number];
    cell.detailTextLabel.text = floor.subtitle;
    
    return cell;
}


-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    if ([[NSUserDefaults standardUserDefaults] boolForKey:kBLENavigationSwitch] ||[[NSUserDefaults standardUserDefaults] boolForKey:kSensorNavigationSwitch])
    {
        
        FloorModel *floor = self.map.froorsArray[indexPath.row];
        IndoorMapController *vc = [self.storyboard instantiateViewControllerWithIdentifier:@"IndoorMapController"];
        vc.floor = floor;
        [self.navigationController pushViewController:vc animated:YES];
    }
    else{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"ERROR" message:@"Choose navigation type, please" delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
        [alert show];
        
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];

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

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
