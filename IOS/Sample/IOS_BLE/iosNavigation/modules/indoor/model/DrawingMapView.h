//
//  MapView.h
//  iosNavigation
//
//  Created by Ievgen on 30.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Graph.h"
#import "FloorModel.h"

@interface DrawingMapView : UIView

@property (assign, nonatomic) CGPoint startPoint;
@property (assign, nonatomic) CGPoint destinationPoint;
@property (strong, nonatomic) NSArray *pointsArray;
@property (nonatomic, strong) FloorModel* floor;
@property (strong, nonatomic) UIImageView *img;
@property (strong, nonatomic) DrawingMapView *view;
@property (nonatomic, assign) BOOL isDrawRoute;
@property (strong, nonatomic) NSArray *vertexArray;
@property (strong, nonatomic) NSArray *edgesArray;
@end
