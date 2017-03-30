//
//  AOShortPath.h
//  Path
//
//  Created by Art on 25.08.2014.
//  Copyright (c) 2014 Path. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class AOPathConnection;

@interface AOPathPoint : NSObject

@property (nonatomic, assign) NSInteger x;
@property (nonatomic, assign) NSInteger y;

@property (assign, nonatomic) long tag;
@property (strong, nonatomic) NSMutableArray *connectionList;

- (instancetype)initWithX:(NSInteger)x Y:(NSInteger)y;
//- (instancetype)initWithTag:(long)tag;

- (void)addConnection:(AOPathConnection*)connection;
//- (AOPathConnection*)getConnectionToPointWithTag:(long)tag;
- (AOPathConnection*)getConnectionToPointWithX:(NSInteger)x Y:(NSInteger)y;

@end

@interface AOPathConnection : NSObject
// closest point ?
@property (strong, nonatomic) AOPathPoint *point;
@property (assign, nonatomic) CGFloat weight;
@end



@interface AOShortestPath : NSObject

@property (strong, nonatomic) NSMutableArray *pointList;

- (AOPathPoint*)getNearestPathPointToX:(NSInteger)x Y:(NSInteger)y;
//- (AOPathPoint*)getPathPointWithTag:(long)tag;
- (NSArray*)getShortestPathFromPointX:(NSInteger)x_1
                                fromY:(NSInteger)y_1
                                  toX:(NSInteger)x_2
                                  toY:(NSInteger)y_2;

- (NSArray*)getShortestPathFromPoint:(AOPathPoint*)fromPoint
                             toPoint:(AOPathPoint*)toPoint;

@end
