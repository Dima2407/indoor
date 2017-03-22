//
//  IndoorError.m
//  IndoorLibrary
//
//  Created by AppleFace on 22.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "IndoorError.h"

@implementation IndoorError

-(instancetype)initWithOptions:(NSUInteger)code title:(NSString*)title message:(NSString*) message{
    
    NSDictionary *userInfo = [NSDictionary dictionaryWithObjectsAndKeys:title, @"errorTitle", message, @"errorMassege", nil];
    
    NSString* domain = @"com.IndoorLibrary.kaa-solutions";
    
    _error = [NSError errorWithDomain:domain
                                     code:code
                                 userInfo:userInfo];
    return self;
}

@end
