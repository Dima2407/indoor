//
//  ErrorListener.h
//  IndoorLibrary
//
//  Created by AppleFace on 22.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "PrefixHeader.pch"

@protocol ErrorListener <NSObject>
-(void)getError:(NSError*)error;
@end
