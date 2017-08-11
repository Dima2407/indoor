//
//  IndoorLocationManager.h
//  IndoorLibrary
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.

#import "IndoorPrefixHeader.pch"
/*!
 * @typedef MeasurementProviderType
 * @brief A list of providers types.
 * @constant STANDART_MODE  use BLE_PROVIDER with standart settings.
 * @constant SENSOR_MODE use SENSOR_PROVIDER.
 * @constant MESH_MODE use BLE_PROVIDER with mesh for map.
 */
typedef NS_ENUM(NSInteger, IndoorLocationManagerMode)
{
    BLE_MODE = 1,
    SENSOR_MODE,
    FILTER_MODE
};

@interface IndoorLocationManager : NSObject


/*! @brief Object that implements the protocol  IndoorLocationListener */
@property (nonatomic, strong) id<IndoorLocationListener> locationListener;
/*! @brief object that implements the protocol ErrorListener*/
@property (nonatomic, strong) id<ErrorListener> errorListener;
/*! @brief Flag responsible for logging */
@property (nonatomic, assign) BOOL isStartLog;
/*! @brief Flag responsible for using a binary mask */
@property (nonatomic, assign) BOOL isOnMask;
/*! @brief Flag responsible for getting routing array  */
@property (nonatomic, assign) BOOL isRouting;
/*! @brief This property sets frequency getting coordinates */
@property (nonatomic, strong) NSTimer *timer;


/*!
 * @discussion Choose IndoorLocationManager working mode
 * @param mode Specifies the mode of IndoorLocationManager
 
 */
-(void)setMode:(IndoorLocationManagerMode)mode;

/*!
 * @discussion Adds NSArray destination coordinates
 * @param destination Specifies destination coordinate
 */
-(void)setDectinationPosition:(NSArray*)destination;
/*!
 * @discussion Adds a card of bicons
 * @param config Specifies the parameters of one beacon by an object of type BeaconConfig
 */

-(void)setConfiguration:(NSDictionary*) config;
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
 * @discussion Return NSMutableArray of NSDictionarys where value by key "x" - return x coordinate, "y" - y coordinate, "z" - z coordinate.
 */
-(NSMutableArray*)getRouting;
/*!
 * @discussion Return CGFloat value distance to destination in meters
 */
-(CGFloat)getDistance;
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
 * @discussion Preparing IndoorLocationManager for work with all setted params
 
 */
-(void)prepare;
/*!
 * @discussion Start data processing
 */
-(void)start;
/*!
 * @discussion Stops data processing
 */
-(void)stop;

@end
