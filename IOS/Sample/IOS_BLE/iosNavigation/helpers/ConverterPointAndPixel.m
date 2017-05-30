//
//  ConverterPointAndPixel.m
//  iosNavigation
//
//  Created by Ievgen on 30.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "ConverterPointAndPixel.h"

CGPoint convertPixelToPoint(CGPoint pixel,CGSize imageSz,CGSize screenSz){
    
    float percentX = imageSz.width / screenSz.width;
    float percentY = imageSz.height / screenSz.height;
    
    CGPoint point;
    
    point.x = pixel.x / percentX;
    point.y = pixel.y / percentY;
    
    return point;
}

CGPoint convertPointToPixel(CGPoint point,CGSize imageSz,CGSize screenSz){

    float percentX = imageSz.width / screenSz.width;
    float percentY = imageSz.height / screenSz.height;
    
    CGPoint pixel;
    
    pixel.x = point.x * percentX;
    pixel.y = point.y * percentY;
    
    return pixel;
}

double absVec(CGPoint point){
    
    double absolute = sqrt(point.x * point.x + point.y * point.y);
    return absolute;
}

RoutePoint* fillRoutePoint(NSString *maneuver, NSString *stepInstruction, NSString *tempDistance, NSString *tempDuration){
    
    RoutePoint *routePoint = [[RoutePoint alloc]init];
    routePoint.maneuver = maneuver;
    routePoint.stepInstruction = stepInstruction;
    routePoint.tempDistance = tempDistance;
    routePoint.tempDuration = tempDuration;
    return routePoint;
}

NSString* calculateTimeDuration(double distance){
    
    double v = 4.f * 1000.f / 3600.f;
    double dist = distance / v;
    NSString *str = [NSString stringWithFormat:@"%1.2fsec",dist];
    return str;
}

NSArray* calculateManeuverWithStartPoint(CGPoint start, NSArray *points, CGFloat pixelSize){
    
    NSMutableArray *array = [NSMutableArray array];
    
    int xTH = 40;
    CGPoint pointA = [[points firstObject] CGPointValue];
    CGPoint vectorA = CGPointMake(0, 1);
    double absoluteA = absVec(vectorA);
    
    double distance = 0.0;

    
    for(int i = 1; i < points.count; i++){
        
         CGPoint p = [[points objectAtIndex:i] CGPointValue];
        
        CGPoint pointB = [[points objectAtIndex:i] CGPointValue];
        CGPoint vectorB = CGPointMake(pointB.x - pointA.x, pointB.y - pointA.y);
        double absoluteB = absVec(vectorB);
        distance += absoluteB;
        double scalar = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
        
        double ortogonalX = -vectorA.y / absoluteA;
        double ortogonalY = vectorA.x / absoluteA;
        
        double deltaX = ((ortogonalX * vectorB.x) + (ortogonalY * vectorB.y));
        double deltaY = scalar / absoluteA;
        
        if(deltaX > 0){
            
            if(fabs(deltaX) > xTH){
                
                distance = distance * pixelSize;
                NSString *time = calculateTimeDuration(distance);
                NSString *dist = [NSString stringWithFormat:@"%.2fm",distance];
                [array addObject:fillRoutePoint(@"turn-right", @"Turn right", dist,time)];
                distance = 0.0;
            }
            else  if(fabs(deltaX) < xTH){
                
                distance = distance * pixelSize;
                NSString *time = calculateTimeDuration(distance);
                NSString *dist = [NSString stringWithFormat:@"%.2fm",distance];
                [array addObject:fillRoutePoint(@"turn-left", @"Turn Left", dist,time)];
                distance = 0.0;
            }
            else{
                double dist12 = distance * pixelSize;
                NSString *time = calculateTimeDuration(dist12);
                NSString *dist = [NSString stringWithFormat:@"%1.2fm",distance * 0.01];
                [array addObject:fillRoutePoint(@"move-forward", @"Move forward", dist,time)];
                distance = 0.0;
            }
        }
        else if(deltaX < 0){
            
            if (fabs(deltaX) > xTH) {
                
                distance = distance * pixelSize;
                NSString *time = calculateTimeDuration(distance);
                NSString *dist = [NSString stringWithFormat:@"%.2fm",distance];
                [array addObject:fillRoutePoint(@"turn-left", @"Turn Left", dist,time)];
                distance = 0.0;
            }
            else if (fabs(deltaX) < xTH) {
                
                distance = distance * pixelSize;
                NSString *time = calculateTimeDuration(distance);
                NSString *dist = [NSString stringWithFormat:@"%.2fm",distance];
                [array addObject:fillRoutePoint(@"turn-right", @"Turn right", dist,time)];
                distance = 0.0;
            }
            else{
                double dist13 = distance * pixelSize;
                NSString *time = calculateTimeDuration(dist13);
                NSString *dist = [NSString stringWithFormat:@"%.2fm",distance * 0.01];
                [array addObject:fillRoutePoint(@"move-forward", @"Move forward", dist,time)];
                distance = 0.0;
            }
        }
        else if (deltaX == 0){
            if (fabs(deltaX) > xTH) {
                
                distance = distance * pixelSize;
                NSString *time = calculateTimeDuration(distance);
                NSString *dist = [NSString stringWithFormat:@"%.2fm",distance];
                [array addObject:fillRoutePoint(@"turn-left", @"Turn Left", dist,time)];
                distance = 0.0;
            }
            else{
            double dist13 = distance * pixelSize ;
            NSString *time = calculateTimeDuration(dist13);
            NSString *dist = [NSString stringWithFormat:@"%.2fm",distance * 0.01];
            [array addObject:fillRoutePoint(@"move-forward", @"Move forward", dist,time)];
                distance = 0.0;
        }
        }
        pointA = pointB;
        vectorA = vectorB;
        absoluteA = absoluteB;
    }
    return array;
}









