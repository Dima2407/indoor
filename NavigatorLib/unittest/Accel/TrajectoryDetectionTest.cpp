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
#include "Navigator/Math/Position3D.h"

namespace NaviTest {
namespace Accel {
// Register this suite !
CPPUNIT_TEST_SUITE_REGISTRATION(TrajectoryDetectionTest);

//===================================================
void TrajectoryDetectionTest::testCheckBlack() {
    // if point black
    CPPUNIT_ASSERT(true == spTD->checkBlack(3, 4));
    CPPUNIT_ASSERT(true == spTD->checkBlack(4, 4));
    CPPUNIT_ASSERT(true == spTD->checkBlack(5, 4));
    // if point black (double)
    CPPUNIT_ASSERT(true == spTD->checkBlack(3.4, 4.4));
    CPPUNIT_ASSERT(true == spTD->checkBlack(4.4, 4.4));
    CPPUNIT_ASSERT(true == spTD->checkBlack(5.4, 4.4));
    // if point white
    CPPUNIT_ASSERT(false == spTD->checkBlack(3, 3));
    CPPUNIT_ASSERT(false == spTD->checkBlack(4, 3));
    CPPUNIT_ASSERT(false == spTD->checkBlack(5, 3));
    // if point white (double)
    CPPUNIT_ASSERT(false == spTD->checkBlack(3.4, 3.4));
    CPPUNIT_ASSERT(false == spTD->checkBlack(4.4, 3.4));
    CPPUNIT_ASSERT(false == spTD->checkBlack(5.4, 3.4));
}
//===================================================
void TrajectoryDetectionTest::testCheckXY() {
    // if point posX < minX
    CPPUNIT_ASSERT(2.0 == spTD->checkXY(1.5, 6.0, 2.0));
    CPPUNIT_ASSERT(2.0 == spTD->checkXY(1.0, 6.0, 2.0));
    CPPUNIT_ASSERT(3.5 == spTD->checkXY(3.5, 6.0, 2.0));
    // if point maxX < posX
    CPPUNIT_ASSERT(6.0 == spTD->checkXY(6.5, 6.0, 2.0));
    CPPUNIT_ASSERT(6.0 == spTD->checkXY(7.0, 6.0, 2.0));
    CPPUNIT_ASSERT(4.0 == spTD->checkXY(4.0, 6.0, 2.0));
    // if point posY < minY
    CPPUNIT_ASSERT(2.0 == spTD->checkXY(1.5, 5.0, 2.0));
    CPPUNIT_ASSERT(2.0 == spTD->checkXY(1.0, 5.0, 2.0));
    CPPUNIT_ASSERT(3.5 == spTD->checkXY(3.5, 5.0, 2.0));
    // if point maxY < posY
    CPPUNIT_ASSERT(5.0 == spTD->checkXY(5.5, 5.0, 2.0));
    CPPUNIT_ASSERT(5.0 == spTD->checkXY(6.0, 5.0, 2.0));
    CPPUNIT_ASSERT(4.0 == spTD->checkXY(4.0, 5.0, 2.0));
}
//===================================================
void TrajectoryDetectionTest::testCheckWall(){
    /// True if the line (x0,y0) -> (x,y) crosses a wall (obstacle)
    CPPUNIT_ASSERT(false == spTD->checkWall(2.4, 2.6, 6.3, 2.6));
    CPPUNIT_ASSERT(false == spTD->checkWall(2.6, 2.7, 3.5, 3.4));
    CPPUNIT_ASSERT(true == spTD->checkWall(2.2, 2.7, 2.5, 4.3));
    CPPUNIT_ASSERT(false == spTD->checkWall(3.1, 3.2, 6.4, 3.6));
    CPPUNIT_ASSERT(true == spTD->checkWall(3.4, 3.3, 3.2, 5.4));
}

void TrajectoryDetectionTest::setUp()
{
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
    // Fill the table with the "identity" operation
    for (int i = 0; i < nx*ny; i++)
        mTable[i] = i;
    //black nodes
    mTable[6] = 7;
    mTable[10] = 11;
    mTable[14] = 18;

    ptrMesh -> setMaskTable(mTable);

    spTD = std::make_shared<TrajectoryDetection>(ptrMesh, posX, posY);
}
//==============================================
}
}

