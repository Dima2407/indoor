//
//  ConverterPointAndPixel.h
//  iosNavigation
//
//  Created by Ievgen on 30.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RoutePoint.h"

CGPoint convertPixelToPoint(CGPoint pixel,CGSize imageSz,CGSize screenSz);
CGPoint convertPointToPixel(CGPoint pixel,CGSize imageSz,CGSize screenSz);
NSArray* calculateManeuverWithStartPoint(CGPoint start, NSArray *points, CGFloat pixelSize);
