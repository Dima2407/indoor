//
//  MapView.m
//  iosNavigation
//
//  Created by Ievgen on 30.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "DrawingMapView.h"
#import "AOShortestPath.h"
#import "ConverterPointAndPixel.h"

@implementation DrawingMapView

- (void)drawRect:(CGRect)rect {
    if (self.isDrawRoute)
    {
        NSArray *points = [NSArray arrayWithObjects:
                           [NSValue valueWithCGPoint:CGPointMake(50.0, 6.0)],
                           [NSValue valueWithCGPoint:CGPointMake(300.7, 80.8)],
                           nil];
        
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGContextClearRect(context, rect);
        
        if(points){
            CGContextSetStrokeColorWithColor(context, [UIColor colorWithRed:0.376f green:0.325f blue:1.f alpha:0.8f].CGColor);
            CGContextSetLineCap(context, kCGLineCapRound);
            CGContextMoveToPoint(context, self.startPoint.x, self.startPoint.y);
            CGContextSetLineWidth(context, 3);
            
            
            for(NSValue *value in points){
                
                CGPoint p = [value CGPointValue];
                
                CGContextAddLineToPoint(context, p.x, p.y);
                CGContextMoveToPoint(context, p.x, p.y);
            }
            CGContextAddLineToPoint(context, self.destinationPoint.x, self.destinationPoint.y);
            CGContextStrokePath(context);
        }
    }

    
}

@end
