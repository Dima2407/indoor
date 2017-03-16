//
//  MeasurementTransfer.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeasurementEvent.h"
#import "MeasurementTranfer.h"

@protocol IosMeasurementTransferDelegate <NSObject>
@optional
-(void)processEvent: (MeasurementEvent *) event;
- (void)didFailWithError:(NSError *)error;
@end



@interface IosMeasurementTransfer : NSObject<MeasurementTranfer>

@property (nonatomic, weak) id <IosMeasurementTransferDelegate> delegate;

@end
