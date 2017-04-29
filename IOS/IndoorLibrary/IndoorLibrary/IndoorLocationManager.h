//
//  IndoorLocationManager.h
//  IndoorLibrary
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.

#import "IndoorPrefixHeader.pch"



@interface IndoorLocationManager : NSObject


/*! @brief Object that implements the protocol  IndoorLocationListener */
@property (nonatomic, strong) id<IndoorLocationListener> locationListener;
/*! @brief object that implements the protocol ErrorListener*/
@property (nonatomic, strong) id<ErrorListener> errorListener;
/*! @brief Flag responsible for logging */
@property (nonatomic, assign) BOOL isStartLog;
/*! @brief This property sets frequency getting coordinates */
@property (nonatomic, strong) NSTimer *timer;

/*!
 * @discussion Adds a card of bicons
 * @param config Specifies the parameters of one beacon by an object of type BeaconConfig

 */
-(void)setBeaconConfig:(BeaconConfig*) config;
/*!
 * @discussion Adds UUID bikons
 * @warning It is better to use one UUID for 1 building 
 * @param uuid UUID string value
 */
-(void)addUUID:(NSString*)uuid;
/*!
 * @discussion Returns incoming data logs from beacons
 * @warning Work only if before the method is started, the isStartLog parameter is set to YES
 * @return NSMutableArray containing NSDictionary as the values indicated by timestamp, minor and rssi
 */
-(NSMutableArray*)getLog;
/*!
 * @discussion Adds a provider to provider's collection.
 * @param type  MeasurementProviderType  type of provider
 */
-(void)addProvider: (MeasurementProviderType) type;
/*!
 * @discussion Removes a provider from provider's collection.
 * @param type  MeasurementProviderType type of provider
 */
-(void)removeProvider: (MeasurementProviderType) type;
/*!
 * @discussion Start data processing

 */
-(void)start;
/*!
 * @discussion Stops data processing
 */
-(void)stop;


@end
