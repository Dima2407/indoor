//
// Created by  Oleksiy Grechnyev on 3/18/2017.
//

#include "Navigator.h"

#include "BeaconUIDTest.h"


namespace NaviTest {
    namespace Beacons {

        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(BeaconUIDTest);

        void BeaconUIDTest::testStringUID() {
            using namespace Navigator::Beacons;

            BeaconUID uid1("Armadillo1");
            BeaconUID uid2("Armadillo2");

            // Test the BeaconUID(string) constructor
            CPPUNIT_ASSERT(uid1 == BeaconUID("Armadillo1"));
            CPPUNIT_ASSERT(uid1 != BeaconUID("Armadillo2"));
            CPPUNIT_ASSERT(uid1 != uid2);
            CPPUNIT_ASSERT(uid1 != BeaconUID("armadillo1"));
            CPPUNIT_ASSERT(uid1 != BeaconUID("Armadillo12"));
            CPPUNIT_ASSERT(uid1 != BeaconUID("Armadillo"));
            CPPUNIT_ASSERT(uid1 != BeaconUID("ArmaDillo1"));
            CPPUNIT_ASSERT(uid1 != BeaconUID("Armaillo1"));
            CPPUNIT_ASSERT(uid1 != BeaconUID("Arma dillo1"));

            // .. including the empty string
            CPPUNIT_ASSERT(BeaconUID("") == BeaconUID(""));
            CPPUNIT_ASSERT(BeaconUID("") != BeaconUID(" "));

            // And finally test the byte sequence
            BeaconUID uid3;
            uid3.push_back('A');
            uid3.push_back('B');
            uid3.push_back('C');
            CPPUNIT_ASSERT(uid3 == BeaconUID("ABC"));
            CPPUNIT_ASSERT(uid3 != BeaconUID("abc"));

            // And the same with the list constructor
//            BeaconUID uid4{(uint8_t)'A', (uint8_t)'B', (uint8_t)'C'};
            BeaconUID uid4{'A', 'B', 'C'};
            CPPUNIT_ASSERT(uid4 == BeaconUID("ABC"));
            CPPUNIT_ASSERT(uid4 == uid3);
            CPPUNIT_ASSERT(uid4 != BeaconUID("abc"));
        }
        //----------------

        void BeaconUIDTest::testSmmUid() {
            using namespace Navigator::Beacons;

            /// Test String Major Minor UID
            BeaconUID uid1("AbC", 13, 666);

            CPPUNIT_ASSERT(uid1 == BeaconUID("AbC", 13, 666));
            CPPUNIT_ASSERT(uid1 != BeaconUID("ABC", 13, 666));
            CPPUNIT_ASSERT(uid1 != BeaconUID("AbC", 14, 666));
            CPPUNIT_ASSERT(uid1 != BeaconUID("AbC", 13, 667));
            CPPUNIT_ASSERT(uid1 != BeaconUID("AbC", 666, 13));

            /// Only the lower 2 bytes of each int are used, the other 2 bytes are  discarded
            // Note: 13 == 0xd, 666 = 0x29a

            CPPUNIT_ASSERT(uid1 == BeaconUID("AbC", 0xD, 0x29A));
            CPPUNIT_ASSERT(uid1 == BeaconUID("AbC", 0xD, 0xFEDC029A));
            CPPUNIT_ASSERT(uid1 == BeaconUID("AbC", 0x1234000D, 0x29A));
            CPPUNIT_ASSERT(uid1 == BeaconUID("AbC", 0x1234000D, 0xFEDC029A));

            // The byte sequence
            BeaconUID uid2 = BeaconUID{'A', 'b', 'C', 0x0D, 0x00, 0x9A, 0x02};
            CPPUNIT_ASSERT(uid1 == uid2);
        }

        //----------------
        void BeaconUIDTest::testLlUid() {
            using namespace Navigator::Beacons;

            /// Test 8-byte long long
            BeaconUID uid1(17);
            CPPUNIT_ASSERT(uid1 == BeaconUID(17));
            CPPUNIT_ASSERT(uid1 != BeaconUID(18));

            // Try something longer, like real 8 bytes
            BeaconUID uid2(0x123456789ABCDEF0);
            CPPUNIT_ASSERT(uid2 == BeaconUID(0x123456789ABCDEF0));
            CPPUNIT_ASSERT(uid2 != BeaconUID(0x123456789ABCDEF1));
            CPPUNIT_ASSERT(uid2 != BeaconUID(0x223456789ABCDEF0));

            // The byte sequence
            BeaconUID uid4{0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12};
            CPPUNIT_ASSERT(uid2 == uid4);

            // The constructor arg is declared signed long long, but that's not a problem for C++
            BeaconUID uid5(0xFF3456789ABCDEF0);
            CPPUNIT_ASSERT(uid5 == BeaconUID(0xFF3456789ABCDEF0));

            CPPUNIT_ASSERT(BeaconUID(-1) == BeaconUID(0xFFFFFFFFFFFFFFFF));
        }
    }
}