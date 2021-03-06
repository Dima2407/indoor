//
//  MeasurementTransfer.h
//  IndoorLibrary
//
//  Created by AppleFace on 28.02.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "IndoorPrefixHeader.pch"
#import "IndoorError.h"
#import "MeasurementTranfer.h"
#import "ErrorTransfer.h"


@protocol IosMeasurementTransferDelegate <NSObject>
@required

-(void)processEvent:(MeasurementEvent*) event;
-(void)processError:(IndoorError*) error;

@end



@interface IosMeasurementTransfer : NSObject<MeasurementTranfer,ErrorTransfer>

@property (nonatomic, weak) id <IosMeasurementTransferDelegate> delegate;

@end
