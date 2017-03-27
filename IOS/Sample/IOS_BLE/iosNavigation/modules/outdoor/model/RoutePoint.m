//
//  RoutePoint.m
//  iosNavigation
//
//  Created by Ievgen on 22.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import "RoutePoint.h"

@implementation RoutePoint

- (instancetype)initWithMainParameters:(NSDictionary*)params additional:(NSDictionary*)addParams
{
    self = [super init];
    if (self) {
        
            NSDictionary *allDistance = params[@"routes"][0][@"legs"][0][@"distance"];
            NSDictionary *allDuration = params[@"routes"][0][@"legs"][0][@"duration"];
            
            self.allDistance = [allDistance objectForKey:@"text"];
            self.allDuration = [allDuration objectForKey:@"text"];
            self.tempDistance = [[addParams objectForKey:@"distance"] objectForKey:@"text"];
            self.tempDuration = [[addParams objectForKey:@"duration"] objectForKey:@"text"];
            self.startLocationForMessage = CLLocationCoordinate2DMake([[[addParams objectForKey:@"end_location"] objectForKey:@"lat"] floatValue], [[[addParams objectForKey:@"end_location"] objectForKey:@"lng"] floatValue]);
            self.stepInstruction = [addParams objectForKey:@"html_instructions"];
            [self foramatInstructionText];
            self.maneuver = [addParams objectForKey:@"maneuver"];
    }
    return self;
}

-(void) foramatInstructionText{
    
    for(int i = 0; i <= self.stepInstruction.length; i++){
        
        NSRange firstSign = [self.stepInstruction rangeOfString:@"<"];
        
        if(firstSign.location != NSNotFound){
            
            for(int i = (int)firstSign.location; i <= self.stepInstruction.length; i++){
                
                NSRange lastSign = [self.stepInstruction rangeOfString:@">"];
                
                if(lastSign.location != NSNotFound){
                    
                    self.stepInstruction = [self.stepInstruction stringByReplacingOccurrencesOfString:[self.stepInstruction substringWithRange:NSMakeRange(firstSign.location, lastSign.location + 1 - firstSign.location)] withString:@""];
                    break;
                }
            }
        }
    }
    self.stepInstruction = [self.stepInstruction stringByReplacingOccurrencesOfString:@"/" withString:@""];
}

@end
