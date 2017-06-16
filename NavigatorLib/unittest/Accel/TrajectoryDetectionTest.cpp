//
// Created by Igor Maschikevich on 6/15/2017.
//
#include <vector>
#include <memory>
#include "../mydoubleeq.h"
#include "Navigator.h"
#include "TrajectoryDetectionTest.h"
#include "Navigator/Mesh/RectanMesh.h"
#include "Navigator/Accel/TrajectoryDetection.h"

namespace NaviTest {
namespace Accel {
// Register this suite !
CPPUNIT_TEST_SUITE_REGISTRATION(TrajectoryDetectionTest);

void TrajectoryDetectionTest::test1() {
    using namespace std;
    using namespace Navigator::Accel;
    using namespace Navigator::Mesh;

    double posX= 2.0, posY = 2.0;
    // Create a simple 5x4 rect mesh
    constexpr double nx = 5, ny = 4;
    constexpr double dx = 1.0, dy = 1.0;
    constexpr double x0 = 2, y0 = 2;

    std::shared_ptr<RectanMesh> ptrMesh = std::make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);
    // Create a mask table : 20 = nx*ny = 5*4
    vector<int> mTable(nx * ny);
    for (int i = 0; i < nx*ny; i++)
        mTable[i] = i;
    //black nodes
    mTable[6] = 7;
    mTable[10] = 11;
    mTable[14] = 18;

    ptrMesh -> setMaskTable(mTable);

    Navigator::Accel::TrajectoryDetection t( ptrMesh, posX, posY);
    // if point black
    CPPUNIT_ASSERT(true == t.checkBlack(3, 4));
    CPPUNIT_ASSERT(true == t.checkBlack(4, 4));
    CPPUNIT_ASSERT(true == t.checkBlack(5, 4));
    //    // if point black (double)
    CPPUNIT_ASSERT(true == t.checkBlack(3.4, 4.4));
    CPPUNIT_ASSERT(true == t.checkBlack(4.4, 4.4));
    CPPUNIT_ASSERT(true == t.checkBlack(5.4, 4.4));
    //    // if point white
    CPPUNIT_ASSERT(false == t.checkBlack(3, 3));
    CPPUNIT_ASSERT(false == t.checkBlack(4, 3));
    CPPUNIT_ASSERT(false == t.checkBlack(5, 3));
    //    // if point white (double)
    CPPUNIT_ASSERT(false == t.checkBlack(3.4, 3.4));
    CPPUNIT_ASSERT(false == t.checkBlack(4.4, 3.4));
    CPPUNIT_ASSERT(false == t.checkBlack(5.4, 3.4));

}
}
}
