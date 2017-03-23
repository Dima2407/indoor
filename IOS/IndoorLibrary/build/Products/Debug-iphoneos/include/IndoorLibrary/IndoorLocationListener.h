//
//  IndoorLocationListener.h
//  IndoorLibrary
//
//  Created by AppleFace on 21.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "PrefixHeader.pch"

@protocol IndoorLocationListener <NSObject>

-(void)onLocation:(NSArray*)coordinte;

@end
