//
//  IndoorError.h
//  IndoorLibrary
//
//  Created by AppleFace on 22.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IndoorError : NSError

@property (nonatomic, strong) NSError *error;

-(instancetype)initWithOptions:(NSUInteger)code title:(NSString*)title message:(NSString*) message;

@end
