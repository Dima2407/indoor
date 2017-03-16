//
//  IndoorLocationUpdateDelegate.h
//  IndoorLibrary
//
//  Created by AppleFace on 15.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol IndoorLocationUpdateDelegate <NSObject>
-(void)didLocationUpdated: (NSArray*) position;
@end
