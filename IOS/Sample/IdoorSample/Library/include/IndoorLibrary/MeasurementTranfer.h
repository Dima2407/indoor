//
//  MeasurementTranfer.h
//  IndoorLibrary
//
//  Created by AppleFace on 13.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MeasurementTranfer <NSObject>

+(void)deliver:(MeasurementEvent*)event;

@end
