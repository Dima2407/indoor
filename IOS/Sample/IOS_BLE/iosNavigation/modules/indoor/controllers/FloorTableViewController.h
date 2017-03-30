//
//  FloorTableViewController.h
//  iosNavigation
//
//  Created by AppleFace on 21.02.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "IndoorMainController.h"
#import "BuildingModel.h"
@interface FloorTableViewController : UITableViewController
@property (strong, nonatomic) BuildingModel *map;
@end
