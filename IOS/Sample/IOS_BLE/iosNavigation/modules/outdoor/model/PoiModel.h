//
//  PoiModel.h
//  iosNavigation
//
//  Created by Ievgen on 26.09.16.
//  Copyright © 2016 Ievgen. All rights reserved.
//

#import <GoogleMaps/GoogleMaps.h>

@interface PoiModel : GMSMarker

- (instancetype)initWithParameters:(NSDictionary*)params;

@end
