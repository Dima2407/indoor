//
// Created by  Oleksiy Grechnyev on 3/12/2017.
//

#pragma once

//#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/** @brief An example of a CppUnit test fixture
 *
 * Apparently a new object of this class is created for each test
 */
class DummyTest : public CPPUNIT_NS::TestFixture {

    // Create the suite for this fixture
CPPUNIT_TEST_SUITE(DummyTest);
        CPPUNIT_TEST(test1);
        CPPUNIT_TEST(test2);
    CPPUNIT_TEST_SUITE_END();

public:

    void setUp() override {
//        std::cout << "Before !!! \n";
        // Do some before each activity here
    }

    void tearDown() override {
//        std::cout << "After !!! \n";
        // Do some after each activity here
    }

    void test1() {
        CPPUNIT_ASSERT(2 * 2 == 4);
    }

    void test2() {
        CPPUNIT_ASSERT(3 * 7 == 21);
    }

private:
    /// A field if needed
    int privateField;

};



