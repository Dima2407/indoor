//
//  IndoorMapViewController.h
//  iosNavigation
//
//  Created by Ievgen on 27.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "IndoorMainController.h"
#import "FloorModel.h"
#import "BuildingModel.h"

@interface IndoorMapController : IndoorMainController
@property (nonatomic, strong) FloorModel *floor;
@end
