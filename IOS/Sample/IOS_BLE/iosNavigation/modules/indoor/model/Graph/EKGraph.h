//
//  EKGraph.h
//  EKAlgorithms
//
//  Created by Evgeny Karkan on 12.11.13.
//  Copyright (c) 2013 EvgenyKarkan. All rights reserved.
//

#import <Foundation/Foundation.h>

@class EKVertex;

@interface EKGraph : NSObject

@property (nonatomic, strong) NSMutableArray *vertices;

- (instancetype)initWithStartVertex:(id)startVertex;
- (void)depthFirstSearch;
- (void)depthFirstSearchRecursive:(EKVertex *)vertex;
- (void)breadthFirstSearch;
- (BOOL)isUndirectedGraph;
- (void)clearVisitHistory;
- (void)primMST:(id)startVertex;
- (void)kruskalMST;
- (NSArray *)dijkstraSPTFrom:(id)sourceVertex To:(id)targetVertex;
- (NSArray *)dijkstraShortestPathFrom:(CGPoint)sourcePoint To:(CGPoint)targetPoint;

- (void)topSort;



@end
