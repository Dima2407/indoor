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
        void TrajectoryDetectionTest::testAlgorithmZUPT() {
            constexpr double accuracy = 1.0e-10; // Accuracy
            CPPUNIT_ASSERT(0 == spTD->algorithmZUPT(0.5, 1.0, true, 0.3));
            CPPUNIT_ASSERT(myDouble(spTD->algorithmZUPT(3.5, 0.0, false, 0.3), 3.5, accuracy));
            CPPUNIT_ASSERT(myDouble(spTD->algorithmZUPT(-3.5, 0.0, false, 0.3), -3.5, accuracy));
            CPPUNIT_ASSERT(myDouble(spTD->algorithmZUPT(0.5, 0.0, false, 0.3), 1.47099, accuracy));
            CPPUNIT_ASSERT(myDouble(spTD->algorithmZUPT(0.5, 1.0, false, 0.3), 2.47099, accuracy));
            CPPUNIT_ASSERT(myDouble(spTD->algorithmZUPT(0.6, 1.0, false, 0.3), 2.765188, accuracy));
            CPPUNIT_ASSERT(myDouble(spTD->algorithmZUPT(0.6, 2.0, false, 0.3), 3.5, accuracy));
        }

//===================================================
        void TrajectoryDetectionTest::setUp() {
            using namespace std;
            using namespace Navigator::Accel;
            using namespace Navigator::Mesh;
            double posX = 2.0, posY = 2.0;
            // Create a simple 5x4 rect mesh
            constexpr double nx = 5, ny = 4;
            constexpr double dx = 1.0, dy = 1.0;
            constexpr double x0 = 2, y0 = 2;

            std::shared_ptr<RectanMesh> ptrMesh = std::make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);
            // Create a mask table : 20 = nx*ny = 5*4
            vector<int> mTable(nx * ny);
            // Fill the table with the "identity" operation
            for (int i = 0; i < nx * ny; i++)
                mTable[i] = i;
            //black nodes
            mTable[6] = 7;
            mTable[10] = 11;
            mTable[14] = 18;

            ptrMesh->setMaskTable(mTable);

            spTD = std::make_shared<TrajectoryDetection>(ptrMesh, posX, posY);
        }

//===================================================
        bool TrajectoryDetectionTest::myDouble(double x, double y, double accuracy) {
            return fabs(x - y) < accuracy;
        }

//===================================================
    }
}

