//
// Created by  Oleksiy Grechnyev on 2/8/2017.
//

#ifndef TESTTOOL_DOUBLEPAIR_H
#define TESTTOOL_DOUBLEPAIR_H

/// A pair of doubles (e.g. time, delta)
struct DoublePair {
    double t, v;

    /// Constructor
    DoublePair(double t, double v) : t(t), v(v) {}

    /// Constructor
    DoublePair() {}
};


#endif //TESTTOOL_DOUBLEPAIR_H
