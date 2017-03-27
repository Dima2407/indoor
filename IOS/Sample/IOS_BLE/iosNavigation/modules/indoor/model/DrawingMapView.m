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

    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextClearRect(context, rect);

    if(self.pointsArray){
    CGContextSetStrokeColorWithColor(context, [UIColor blueColor].CGColor);
    CGContextSetLineCap(context, kCGLineCapRound);
    CGContextMoveToPoint(context, self.startPoint.x, self.startPoint.y);
    
    CGContextSetLineWidth(context, 3);
    
        for(NSValue *value in self.pointsArray){
            
            CGPoint p = [value CGPointValue];
            CGContextAddLineToPoint(context, p.x, p.y);
            CGContextMoveToPoint(context, p.x, p.y);
        }
    CGContextStrokePath(context);
    }
    
//.................................Draw graph......................................//
//    for(AOPathPoint *p in self.vertexArray){
//        CGContextSetStrokeColorWithColor(context, [UIColor redColor].CGColor);
//        CGPoint point;
//        point.x = p.x;
//        point.y = p.y;
//        
//        point = convertPixelToPoint(point, self.img.image.size, self.view.frame.size);
//        CGContextMoveToPoint(context, point.x, point.y);
//        CGContextAddEllipseInRect(context, CGRectMake(point.x, point.y, 3, 3));
//    }
//    CGContextStrokePath(context);
//................................................................................//
}

@end
