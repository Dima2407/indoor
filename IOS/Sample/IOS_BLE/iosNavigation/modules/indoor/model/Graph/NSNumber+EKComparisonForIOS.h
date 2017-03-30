//
// Created by ASPCartman on 26/08/14.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE

@interface NSNumber (EKComparisonForIOS)

- (BOOL) isGreaterThan:(NSNumber *)obj;
- (BOOL) isLessThan:(NSNumber *)obj;

@end

#endif
