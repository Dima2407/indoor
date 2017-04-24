//
//  IndoorLocationListener.h
//  IndoorLibrary
//
//  Created by AppleFace on 21.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "PrefixHeader.pch"
/*!
 @protocol IndoorLocationListener
 
 @brief The IndoorLocationListener protocol
 
 The protocol whose methods you use to receive coordinates from IndoorLocationManager.
 Implement this protocol in an object of your app and assign your object to the locationListener property of a IndoorLocationManager object. You can use the onLocation method.
 */
@protocol IndoorLocationListener <NSObject>

-(void)onLocation:(NSArray*)coordinte;

@end
