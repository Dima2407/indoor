//
//  UIImage+ManeuverImage.m
//  iosNavigation
//
//  Created by Ievgen on 29.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "UIImage+ManeuverImage.h"

@implementation UIImage (ManeuverImage)

+(UIImage*) maneuverImage:(NSString*)maneuver{
    
    if(maneuver == nil || [maneuver isEqualToString:@"move-forward"]){
        return [UIImage imageNamed:@"forward.png"];
    }
    else if ([maneuver isEqualToString:@"turn-left"]){
        return [UIImage imageNamed:@"left.png"];
    }
    else if ([maneuver isEqualToString:@"turn-right"]){
        return [UIImage imageNamed:@"right.png"];
    }
    else if ([maneuver isEqualToString:@""]){
        return [UIImage imageNamed:@"back.png"];
    }
    else if ([maneuver isEqualToString:@"turn-slight-right"]){
        return [UIImage imageNamed:@"turn_slight"];
    }
    else if ([maneuver isEqualToString:@"turn-slight-left"]){
        return [UIImage imageNamed:@"left_arrow"];
    }
    else{
        return  nil;
    }
}

@end
