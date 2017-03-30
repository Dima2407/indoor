//
//  MenuViewController.h
//  iosNavigation
//
//  Created by Ievgen on 16.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MenuViewController : UITableViewController

@property (weak, nonatomic) IBOutlet UISwitch *showRadar;
@property (weak, nonatomic) IBOutlet UISwitch *showRout;
@property (weak, nonatomic) IBOutlet UISwitch *showPOI;
@property (weak, nonatomic) IBOutlet UISwitch *OnLogs;
@property (weak, nonatomic) IBOutlet UIButton *sendLogButton;
@end
