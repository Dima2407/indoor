//
//  BeaconConfig.m
//  IndoorLibrary
//
//  Created by AppleFace on 13.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import "BeaconConfig.h"


@interface BeaconConfig()


@end
//    Beacon(const BeaconUID &uid, double txPower, double damp, const Math::Position3D &pos, const std::string &meta = "") :
//    uid(uid),
//    txPower(txPower),
//    damp(damp),
//    pos(pos),
//    meta(meta) {}
//

@implementation BeaconConfig

-(instancetype)initWithUUID:(NSString*)uuid major:(NSUInteger)major minor:(NSUInteger)minor txPower:(CGFloat)txPower damp:(CGFloat)damp andX:(CGFloat)x andY:(CGFloat)y andZ:(CGFloat)z{
    self = [super init];
    
    if(self){
        
        self.uuid = uuid ;
        self.major = major;
        self.minor = minor;
        self.txPower = txPower;
        self.damp = damp;
        self.x = x;
        self.y = y;
        self.z = z;
  
       
    }
    return self;
}


@end
