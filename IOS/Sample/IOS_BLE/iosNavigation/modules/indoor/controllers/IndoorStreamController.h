//
//  StreamInDoorController.h
//  iosNavigation
//
//  Created by Ievgen on 22.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "IndoorMainController.h"
#import "FloorModel.h"
#import "BuildingModel.h"

@protocol IndoorStreamControllerDelegate;

@interface IndoorStreamController : IndoorMainController

@property (weak, nonatomic) id <IndoorStreamControllerDelegate> delegate;
@property (assign, nonatomic) CGPoint startPoint;
@property (assign, nonatomic) CGPoint tapPoint;
@property (strong, nonatomic) BuildingModel *build;
@property (nonatomic, assign) FloorModel *floor;
@property (nonatomic, strong) Graph *graph;

@end

@protocol IndoorStreamControllerDelegate <NSObject>

-(void) refreshRouteWihtStartPoint:(CGPoint)startPoint tapPint:(CGPoint)tapPoint;

@end
