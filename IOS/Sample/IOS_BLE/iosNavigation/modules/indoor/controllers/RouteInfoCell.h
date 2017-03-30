//
//  RouteInfoCell.h
//  iosNavigation
//
//  Created by Ievgen on 26.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RouteInfoCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *instructionLabel;
@property (weak, nonatomic) IBOutlet UILabel *distanceLabel;
@property (weak, nonatomic) IBOutlet UILabel *durationLabel;
@property (weak, nonatomic) IBOutlet UIImageView *image;

@end
