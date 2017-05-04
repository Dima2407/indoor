//
//  UIColor+HEX.m
//  ThirdPartyLibraries
//
//  Created by AppleFace on 09.12.16.
//  Copyright © 2016 AppleFace. All rights reserved.
//

#import "UIColor+HEX.h"

@implementation UIColor (HEX)
+ (UIColor *)colorWithHexString:(NSString *)hexString {
    unsigned rgbValue = 0;
    NSScanner *scanner = [NSScanner scannerWithString:hexString];
    [scanner setScanLocation:1]; // bypass '#' character
    [scanner scanHexInt:&rgbValue];
    
    return [UIColor colorWithRed:((rgbValue & 0xFF0000) >> 16)/255.0 green:((rgbValue & 0xFF00) >> 8)/255.0 blue:(rgbValue & 0xFF)/255.0 alpha:1.0];
}
@end
