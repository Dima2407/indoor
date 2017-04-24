//
//  IndoorLocationManager.h
//  IndoorLibrary
//
//  Created by AppleFace on 06.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.

#import "PrefixHeader.pch"



@interface IndoorLocationManager : NSObject


/*! @brief обьект  реализующий протокол IndoorLocationListener */
@property (nonatomic, strong) id<IndoorLocationListener> locationListener;
/*! @brief обьект  реализующий протокол ErrorListener*/
@property (nonatomic, strong) id<ErrorListener> errorListener;
/*! @brief флаг отвечающий за запись логов */
@property (nonatomic, assign) BOOL isStartLog;
/*! @brief This property устанавливает частоту доставки координат */
@property (nonatomic, strong) NSTimer *timer;

/*!
 * @discussion добавляет карту биконов
 * @warning биконы добавляются по одному
 * @param config BeaconConfig используется для создания карты биконов 

 */
-(void)setBeaconConfig:(BeaconConfig*) config;
/*!
 * @discussion добавляет UUID биконов
 * @warning вы можете  добавить не больше 3 уникальных UUID
 * @param uuid строковое значение UUID
 */
-(void)addUUID:(NSString*)uuid;
/*!
 * @discussion возвращает логи входящих данных от биконов
 * @warning логи возвращаются только если перед вызовом метода старт параметр isStartLog установлен как YES
 * @return возвращает NSMutableArray содержащих NSDictionary в качестве значений которому указаны timestamp, minor and rssi
 */
-(NSMutableArray*)getLog;
/*!
 * @discussion добавляет провайдер к колекции провайдеров.
 * @param type  MeasurementProviderType  тип провайдера
 */
-(void)addProvider: (MeasurementProviderType) type;
/*!
 * @discussion удаляет провайдер к колекции провайдеров.
 * @param type  MeasurementProviderType  тип провайдера
 */
-(void)removeProvider: (MeasurementProviderType) type;
/*!
 * @discussion стартует обработку данных

 */
-(void)start;
/*!
 * @discussion останавливает обработку данных
 */
-(void)stop;


@end
