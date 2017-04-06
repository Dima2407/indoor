//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#include "RingBufferTest.h"

namespace NaviTest {
    namespace Math {
        namespace Filter {
            // Register this suite !
            CPPUNIT_TEST_SUITE_REGISTRATION(RingBufferTest);

            void RingBufferTest::test1() {
                using namespace Navigator::Math::Filter;
                using namespace Navigator;

                RingBuffer<int> buffer(3);
                int val;

                CPPUNIT_ASSERT(buffer.isEmpty());
                CPPUNIT_ASSERT(buffer.size() == 0);

                // Push 3
                CPPUNIT_ASSERT(buffer.push(-17));
                CPPUNIT_ASSERT(buffer.size() == 1);

                CPPUNIT_ASSERT(!buffer.isFull());
                CPPUNIT_ASSERT(!buffer.isEmpty());
                CPPUNIT_ASSERT(buffer.push(666));
                CPPUNIT_ASSERT(buffer.size() == 2);
                CPPUNIT_ASSERT(buffer.push(13));
                CPPUNIT_ASSERT(buffer.size() == 3);

                // Now the buffer is full
                CPPUNIT_ASSERT(buffer.isFull());
                CPPUNIT_ASSERT(!buffer.push(21)); // Push fails, the buffer is full
                CPPUNIT_ASSERT(buffer.isFull());
                CPPUNIT_ASSERT(buffer.size() == 3);


                // Pop everything
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(-17 == val);
                CPPUNIT_ASSERT(buffer.size() == 2);


                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(666 == val);
                CPPUNIT_ASSERT(buffer.size() == 1);


                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(13 == val);
                CPPUNIT_ASSERT(buffer.size() == 0);

                CPPUNIT_ASSERT(buffer.push(131));
                CPPUNIT_ASSERT(buffer.size() == 1);
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(131 == val);

                // Now we are empty again
                CPPUNIT_ASSERT(buffer.isEmpty());
                CPPUNIT_ASSERT(!buffer.pop(val)); // Empty: pop fails
                CPPUNIT_ASSERT(buffer.isEmpty());

                // Push 3 values
                CPPUNIT_ASSERT(buffer.push(101));
                CPPUNIT_ASSERT(buffer.push(0));
                CPPUNIT_ASSERT(buffer.size() == 2);
                CPPUNIT_ASSERT(buffer.push(-100500));
                CPPUNIT_ASSERT(buffer.size() == 3);
                CPPUNIT_ASSERT(buffer.isFull());

                // Pop 1
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(101 == val);
                CPPUNIT_ASSERT(buffer.size() == 2);

                // Push 1
                CPPUNIT_ASSERT(buffer.push(7));
                CPPUNIT_ASSERT(buffer.size() == 3);

                // Pop 3
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(0 == val);
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(-100500 == val);
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(7 == val);
                CPPUNIT_ASSERT(buffer.isEmpty());

                // Now push something
                CPPUNIT_ASSERT(buffer.push(1));
                CPPUNIT_ASSERT(buffer.push(2));
                CPPUNIT_ASSERT(!buffer.isEmpty());

                // Now clear the buffer
                buffer.clear();
                CPPUNIT_ASSERT(buffer.isEmpty());

                // See that it still works

                // Push 3
                CPPUNIT_ASSERT(buffer.push(-1));
                CPPUNIT_ASSERT(!buffer.isFull());
                CPPUNIT_ASSERT(!buffer.isEmpty());
                CPPUNIT_ASSERT(buffer.push(-2));
                CPPUNIT_ASSERT(buffer.push(-3));
                CPPUNIT_ASSERT(buffer.isFull());

                // Pop 3
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(-1 == val);
                CPPUNIT_ASSERT(!buffer.isFull());
                CPPUNIT_ASSERT(!buffer.isEmpty());
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(-2 == val);
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(-3 == val);
                CPPUNIT_ASSERT(buffer.isEmpty());

            }
//-------------------------------------------------
            void RingBufferTest::testPeek() {
                using namespace Navigator::Math::Filter;
                using namespace Navigator;

                RingBuffer<int> buffer(3);
                int val;

                // Add data
                CPPUNIT_ASSERT(buffer.push(124));
                CPPUNIT_ASSERT(buffer.push(125));
                CPPUNIT_ASSERT(buffer.push(126));
                CPPUNIT_ASSERT(buffer.size() == 3);

                // Now peek
                CPPUNIT_ASSERT(buffer.peek(0, val));
                CPPUNIT_ASSERT(124 == val);
                CPPUNIT_ASSERT(buffer.peek(1, val));
                CPPUNIT_ASSERT(125 == val);
                CPPUNIT_ASSERT(buffer.peek(2, val));
                CPPUNIT_ASSERT(126 == val);

                // And peek again
                CPPUNIT_ASSERT(buffer.peek(0, val));
                CPPUNIT_ASSERT(124 == val);
                CPPUNIT_ASSERT(buffer.peek(1, val));
                CPPUNIT_ASSERT(125 == val);
                CPPUNIT_ASSERT(buffer.peek(2, val));
                CPPUNIT_ASSERT(126 == val);

                // Wrong index in peek
                CPPUNIT_ASSERT(! buffer.peek(3, val));
                CPPUNIT_ASSERT(buffer.size() == 3);

                // Pop one, push one
                CPPUNIT_ASSERT(buffer.pop(val));
                CPPUNIT_ASSERT(124 == val);
                CPPUNIT_ASSERT(buffer.push(127));

                // Check again
                CPPUNIT_ASSERT(buffer.peek(0, val));
                CPPUNIT_ASSERT(125 == val);
                CPPUNIT_ASSERT(buffer.peek(1, val));
                CPPUNIT_ASSERT(126 == val);
                CPPUNIT_ASSERT(buffer.peek(2, val));
                CPPUNIT_ASSERT(127 == val);

                CPPUNIT_ASSERT(buffer.size() == 3);
            }
        }
    }
}