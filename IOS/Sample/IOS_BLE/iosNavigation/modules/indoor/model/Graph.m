//
//  Graph.m
//  iosNavigation
//

#import "Graph.h"
#import "EKVertex.h"
#import "EKEdge.h"

@implementation GraphVertex
@end

@implementation GraphEdge
@end


@interface Graph ()
@property (nonatomic) BOOL fillingVertices;

@end


@implementation Graph

- (instancetype)initWithData:(NSData *)data {
    self = [super init];
    
   self.jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
//    NSArray *eachLineOfString = [stringFromData componentsSeparatedByString:@"\n"];
//    
//    _pathManager = [[AOShortestPath alloc] init];
//    _pathManager.pointList = [NSMutableArray array];
//    
//    for (NSString *line in eachLineOfString) {
//        if ([line containsString:@"->GRAPH"]) {
//            _fillingVertices = YES;
//        } else if ([line containsString:@"->EDGES"]) {
//            _fillingVertices = NO;
//        } else {
//            
//            if (_fillingVertices) {
//                NSArray *vertexesStrings = [line componentsSeparatedByString:@" "];
//                GraphVertex *vertex = [[GraphVertex alloc] init];
//                vertex.x = [vertexesStrings[0] integerValue];
//                vertex.y = [vertexesStrings[1] integerValue];
//                vertex.distance = 99999999999;
//                
//                [self.vertexes addObject:vertex];
//                
//                // add path path point
//                AOPathPoint *p = [[AOPathPoint alloc] initWithX:vertex.x Y:vertex.y];
//                [_pathManager.pointList addObject:p];
//                
////--------------------- new DIJKSTRA ALGO -----------------------
//                EKVertex *ekV = [[EKVertex alloc] init];
//                ekV.label = [line stringByReplacingOccurrencesOfString:@"\r" withString:@""];
//                ekV->x = vertex.x;
//                ekV->y = vertex.y;
//                
//                [self.ekVertexes addObject:ekV];
////---------------------------------------------------------------
//            } else {
//                
//                NSArray *edgeStrings = [line componentsSeparatedByString:@" "];
//                if ([edgeStrings count] < 5) {
//                    break;
//                }
//                
//                GraphEdge *edge = [[GraphEdge alloc] init];
//                
//                GraphVertex *origin = [[GraphVertex alloc] init];
//                origin.x = [edgeStrings[0] integerValue];
//                origin.y = [edgeStrings[1] integerValue];
//                origin.distance = 99999999999;
//                
//                edge.origin = origin;
//                
//                GraphVertex *dest = [[GraphVertex alloc] init];
//                dest.x = [edgeStrings[2] integerValue];
//                dest.y = [edgeStrings[3] integerValue];
//                dest.distance = 99999999999;
//                
//                edge.destination = dest;
//                edge.weight = [edgeStrings[4] floatValue];
//                
//                [self.edges addObject:edge];
//                
////--------------------- new DIJKSTRA ALGO -----------------------
//                EKVertex *aV;
//                for (EKVertex *vertex in self.ekVertexes) {
//                    if (vertex->x == origin.x && vertex->y == origin.y) {
//                        aV = vertex;
//                        break;
//                    }
//                }
//                
//                EKVertex *cV;
//                for (EKVertex *vertex in self.ekVertexes) {
//                    if (vertex->x == dest.x && vertex->y == dest.y) {
//                        cV = vertex;
//                        break;
//                    }
//                }
//
//                EKEdge *ekEdge = [[EKEdge alloc] initWithAdjacentFrom:aV
//                                                                   To:cV
//                                                            andWeight:[NSNumber numberWithInteger:edge.weight]];
//                
//                [self.ekEdges addObject:ekEdge];
////---------------------------------------------------------------
//                
//            }
//        }
//    }
//    
//    // create path connections
//    for (int i = 0; i<_pathManager.pointList.count; i++) {
//        AOPathPoint *p = _pathManager.pointList[i];
//        [self createPathConnectionsForPoint:p];
//    }
//    
////--------------------- new DIJKSTRA ALGO -----------------------
//    for (EKVertex *eV in self.ekVertexes) {
//        NSMutableArray *adjEdges = [NSMutableArray new];
//        
//        for (EKEdge *eE in self.ekEdges) {
//            if ([eE.adjacentFrom isEqual:eV]) {
//                [adjEdges addObject:eE];
//            }
//        }
//        
//        eV.adjacentEdges = [NSMutableSet setWithArray:adjEdges];
//    }
//
//    self.graphManager = [[EKGraph alloc] initWithStartVertex:[self.ekVertexes firstObject]];
//    self.graphManager.vertices = [self.ekVertexes mutableCopy];
//    
////---------------------------------------------------------------
    
    return self;
}

- (void)createPathConnectionsForPoint:(AOPathPoint *)p {
    NSMutableArray *cons = [NSMutableArray new];
    for (GraphEdge *edge in self.edges) {
        if (edge.origin.x == p.x && edge.origin.y == p.y) { // check destination point also ?
            AOPathConnection *c = [[AOPathConnection alloc] init];
            c.weight = edge.weight;
            c.point = [self getPathPointWithX:edge.destination.x Y:edge.destination.y];
            
            [cons addObject:c];
        }
        
    }
    
    for (AOPathConnection *connection in cons) {
        [p addConnection:connection];
    }
}

- (AOPathPoint *)getPathPointWithX:(NSInteger)x Y:(NSInteger)y {
    __block AOPathPoint *pathPoint;
    [_pathManager.pointList enumerateObjectsUsingBlock:^(AOPathPoint *p, NSUInteger idx, BOOL *stop) {
        if (p.x == x && p.y == y) {
            pathPoint = p;
            *stop = YES;
        }
    }];
    return pathPoint;
}

//- (NSArray*)getConnectionListForPoint:(AOPathPoint *)point {
//    
//    NSMutableArray *cons = [NSMutableArray new];
//
//    for (GraphEdge *edge in self.edges) {
//        if (edge.origin.x == point.x && edge.origin.y == point.y) { // check destination point also ?
//            AOPathConnection *c = [[AOPathConnection alloc] init];
//            c.weight = edge.weight;
//            c.point = [_pathManager getPathPointWithX:point.x Y:point.y];
//            [cons addObject:c];
//        }
//    }
//    
//    return cons.copy;
//}

#pragma getters and setters
- (NSMutableArray *)vertexes {
    if (!_vertexes) {
        _vertexes = [[NSMutableArray alloc] init];
    }
    return _vertexes;
}

- (NSMutableArray *)edges {
    if (!_edges) {
        _edges = [[NSMutableArray alloc] init];
    }
    return _edges;
}

- (NSMutableArray *)ekVertexes {
    if (!_ekVertexes) {
        _ekVertexes = [[NSMutableArray alloc] init];
    }
    return _ekVertexes;
}

- (NSMutableArray *)ekEdges {
    if (!_ekEdges) {
        _ekEdges = [[NSMutableArray alloc] init];
    }
    return _ekEdges;
}



@end
