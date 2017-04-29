//
//  ErrorListener.h
//  IndoorLibrary
//
//  Created by AppleFace on 22.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "IndoorPrefixHeader.pch"
/*!
 @protocol ErrorListener
 
 @brief The ErrorListener protocol
 
 The protocol whose methods you use to receive errors from IndoorLocationManager.
 Implement this protocol in an object of your app and assign your object to the errorListener property of a IndoorLocationManager object. You can use the getError method.
 */
@protocol ErrorListener <NSObject>
-(void)getError:(NSError*)error;
@end
