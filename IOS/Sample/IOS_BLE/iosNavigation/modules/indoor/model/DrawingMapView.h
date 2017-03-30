//
//  MapView.h
//  iosNavigation
//
//  Created by Ievgen on 30.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Graph.h"

@interface DrawingMapView : UIView

@property (assign, nonatomic) CGPoint startPoint;
@property (strong, nonatomic) NSArray *pointsArray;

@property (strong, nonatomic) UIImageView *img;
@property (strong, nonatomic) DrawingMapView *view;

@property (strong, nonatomic) NSArray *vertexArray;
@property (strong, nonatomic) NSArray *edgesArray;
@end
