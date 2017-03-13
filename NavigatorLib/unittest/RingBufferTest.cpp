//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#include "RingBufferTest.h"

namespace NaviTest {
    CPPUNIT_TEST_SUITE_REGISTRATION(RingBufferTest);

    void RingBufferTest::test1() {
        using namespace Navi::filter;
        using namespace Navi;

        RingBuffer<int> buffer(3);
        int val;

        CPPUNIT_ASSERT(buffer.isEmpty());

        // Push 3
        CPPUNIT_ASSERT(buffer.push(-17));
        CPPUNIT_ASSERT(! buffer.isFull());
        CPPUNIT_ASSERT(! buffer.isEmpty());
        CPPUNIT_ASSERT(buffer.push(666));
        CPPUNIT_ASSERT(buffer.push(13));

        // Now the buffer is full
        CPPUNIT_ASSERT(buffer.isFull());
        CPPUNIT_ASSERT(! buffer.push(21)); // Push fails, the buffer is full
        CPPUNIT_ASSERT(buffer.isFull());

        // Pop everything
        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( -17 == val );

        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( 666 == val );

        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( 13 == val );

        // Now we are empty again
        CPPUNIT_ASSERT(buffer.isEmpty());
        CPPUNIT_ASSERT(! buffer.pop(val)); // Empty: pop fails
        CPPUNIT_ASSERT(buffer.isEmpty());

        // Push 3 values
        CPPUNIT_ASSERT(buffer.push(101));
        CPPUNIT_ASSERT(buffer.push(0));
        CPPUNIT_ASSERT(buffer.push(-100500));
        CPPUNIT_ASSERT(buffer.isFull());

        // Pop 1
        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( 101 == val );

        // Push 1
        CPPUNIT_ASSERT(buffer.push(7));

        // Pop 3
        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( 0 == val );
        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( -100500 == val );
        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( 7 == val );
        CPPUNIT_ASSERT(buffer.isEmpty());


        // Now push something
        CPPUNIT_ASSERT(buffer.push(1));
        CPPUNIT_ASSERT(buffer.push(2));
        CPPUNIT_ASSERT(! buffer.isEmpty());

        // Now clear the buffer
        buffer.clear();
        CPPUNIT_ASSERT(buffer.isEmpty());

        // See that it still works

        // Push 3
        CPPUNIT_ASSERT(buffer.push(-1));
        CPPUNIT_ASSERT(! buffer.isFull());
        CPPUNIT_ASSERT(! buffer.isEmpty());
        CPPUNIT_ASSERT(buffer.push(-2));
        CPPUNIT_ASSERT(buffer.push(-3));
        CPPUNIT_ASSERT(buffer.isFull());

        // Pop 3
        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( -1 == val );
        CPPUNIT_ASSERT(! buffer.isFull());
        CPPUNIT_ASSERT(! buffer.isEmpty());
        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( -2 == val );
        CPPUNIT_ASSERT(buffer.pop(val));
        CPPUNIT_ASSERT( -3 == val );
        CPPUNIT_ASSERT(buffer.isEmpty());

    }
}