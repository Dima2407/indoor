//
//  EKVertex.m
//  EKAlgorithms
//
//  Created by Evgeny Karkan on 12.11.13.
//  Copyright (c) 2013 EvgenyKarkan. All rights reserved.
//

#import "EKVertex.h"

@implementation EKVertex
- (NSString *)description {
    return [NSString stringWithFormat:@"x = %ld, y = %ld", (long)x, (long)y];
}
@end
