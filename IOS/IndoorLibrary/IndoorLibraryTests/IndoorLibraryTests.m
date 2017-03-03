//
//  IndoorLibraryTests.m
//  IndoorLibraryTests
//
//  Created by AppleFace on 02.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "GPSMeasurementProvider.h"
#import <CoreLocation/CLLocationManager.h>

@interface IndoorLibraryTests : XCTestCase
@property (nonatomic, strong) GPSMeasurementProvider *testProvider;
@property (nonatomic, strong) CLLocationManager *manager;
@end

@implementation IndoorLibraryTests

- (void)setUp {
    [super setUp];
    NSLog(@"%@ setUp", self.name);
    self.testProvider = [[GPSMeasurementProvider alloc] init];
  
    
    
    XCTAssertNotNil(self.testProvider, @"Cannot create GPSMeasurementProvider instance");
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}
-(void) testCoordinates {
    self.manager = [[CLLocationManager alloc] init];
    self.testProvider.manager = self.manager;
    [self.testProvider start];
    
    NSLog(@"_______________%d", [CLLocationManager authorizationStatus]);
   
    XCTAssertTrue(self.testProvider.longitude == 0);
    
}
-(void) testStatus {
   
    XCTAssertTrue(self.testProvider.longitude == 0);
    
}
- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
