//
// Created by  Oleksiy Grechnyev on 2/13/2017.
//


#include "PolyTrajectory.h"
#include <iostream>

namespace tester {

    bool PolyTrajectory::readAuto(std::string const &fileName) {
        using namespace std;

        if (! pLine.readDAT(fileName)) return false;

        // Check that there are at least 2 points

        int npoints = pLine.getPoints().size(); // Number of points

        if (npoints < 2) {
            cerr << "ERROR::PolyTrajectory: Need at least 2 points in file " << fileName << endl;
            exit(1);
        }

        // Sort after reading
        pLine.sort();

        return true;

    }

    Vec3 PolyTrajectory::trajectory(double t) const {
        using namespace std;

        // First find the correct segment
        // The segment is index, index+1
        // Where index = 0, ..., npoints-2
        // If t<t0 then index =0
        // If t0<t<t1 then index =0
        // ... if t>t(n-1) then index=n-2 (the maximum)
        int index;

        int npoints = pLine.getPoints().size(); // Number of points

        if (npoints < 2) {
            cerr << "ERROR::PolyTrajectory: Need at least 2 points." << endl;
            exit(1);
        }

        // Find the correct index, min:0, max: n-2
        for (index =0; index < npoints-2 && pLine.getPoints()[index+1].t < t ; index++);

        // Now we work with the segment index, index+1
        double t1 = pLine.getPoints()[index].t;
        double t2 = pLine.getPoints()[index+1].t;

        Vec3 point1 = pLine.getPoints()[index].r;
        Vec3 point2 = pLine.getPoints()[index+1].r;

        // Use this segment for linear interpolation
        return point1 * ((t2 - t) / (t2 - t1)) + point2 * ((t - t1) / (t2 - t1));
    }
}