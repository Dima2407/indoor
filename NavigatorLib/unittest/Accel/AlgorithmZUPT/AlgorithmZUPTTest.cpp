//
// Created by Igor Maschikevich on 6/14/2017.
//

#include "Navigator.h"

#include "AlgorithmZUPTTest.h"

namespace NaviTest {
namespace Accel{

// Register this suite !
CPPUNIT_TEST_SUITE_REGISTRATION(AlgorithmZUPTTest);
//----------------
void AlgorithmZUPTTest::test1() {
    using namespace Navigator::Accel;
    constexpr double accuracy = 1.0e-10; // Accuracy

    double random = std::rand();
     AlgorithmZUPT zupt();

    std::cout <<"Hello world!!"<<std::endl;
//    CPPUNIT_ASSERT(myVelocity(zupt.process(random, random, random,true),
//                              Position3D(0, 0, 0), accuracy));






}
}
}
