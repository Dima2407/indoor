//
//  Graph.h
//  iosNavigation
//

#import <Foundation/Foundation.h>
#import "AOShortestPath.h"
#import "EKGraph.h"

@interface GraphVertex : NSObject
@property (nonatomic, assign) NSInteger x;
@property (nonatomic, assign) NSInteger y;


@property (nonatomic, assign) long distance;


@end

@interface GraphEdge : NSObject
@property (nonatomic, strong) GraphVertex *origin;
@property (nonatomic, strong) GraphVertex *destination;

@property (nonatomic, assign) float weight;

@end

@interface Graph : NSObject

@property (nonatomic, strong) NSMutableArray *vertexes;
@property (nonatomic, strong) NSMutableArray *edges;

@property (strong, nonatomic) AOShortestPath *pathManager;
@property (strong, nonatomic)         EKGraph *graphManager;
@property (nonatomic, strong) NSMutableArray *ekVertexes;
@property (nonatomic, strong) NSMutableArray *ekEdges;



- (instancetype)initWithData:(NSData *)data;


@end
