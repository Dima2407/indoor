//
//  RouteInfoView.h
//  iosNavigation
//
//  Created by Ievgen on 22.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RouteInfoView : UIView

@property (weak, nonatomic) IBOutlet UILabel *distance;
@property (weak, nonatomic) IBOutlet UILabel *duration;
@property (weak, nonatomic) IBOutlet UILabel *nextStep;
@property (weak, nonatomic) IBOutlet UIImageView *imageView;

@end
