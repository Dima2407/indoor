//
// Created by  Oleksiy Grechnyev on 2/13/2017.
//

#ifndef TESTTOOL_POLYTRAJECTORY_H
#define TESTTOOL_POLYTRAJECTORY_H

#include "Vec3tList.h"

namespace tester {
    /// Polyline trajectory based on a Vec3tList object
    class PolyTrajectory {
    public:
        /// Read the list from a data file, return true if success
        bool readAuto(std::string const & fileName);

        /// Calculate the linear trajectory Vec3(t)
        Vec3 trajectory(double t) const;

        /// Get the strating time
        const double startTime() const {
            return pLine.getPoints().front().t;
        }

        /// Get the ending time
        const double endTime() const {
            return pLine.getPoints().back().t;
        }

    private:
        /// The timestamped polyline
        Vec3tList pLine;
    };
}

#endif //TESTTOOL_POLYTRAJECTORY_H
