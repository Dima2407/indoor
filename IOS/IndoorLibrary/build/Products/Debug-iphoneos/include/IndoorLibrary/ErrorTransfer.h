//
//  ErrorTransfer.h
//  IndoorLibrary
//
//  Created by AppleFace on 22.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IndoorError.h"

@protocol ErrorTransfer <NSObject>

-(void)deliverError:(IndoorError*)error;

@end
