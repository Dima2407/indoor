//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#include "BeaconTime.h"

namespace faker{


    long long int BeaconTime::getHash() const {
        return hash;
    }

    void BeaconTime::setHash(long long int hash) {
        BeaconTime::hash = hash;
    }

    double BeaconTime::getT1() const {
        return t1;
    }

    void BeaconTime::setT1(double t1) {
        BeaconTime::t1 = t1;
    }

    double BeaconTime::getT2() const {
        return t2;
    }

    void BeaconTime::setT2(double t2) {
        BeaconTime::t2 = t2;
    }

    double BeaconTime::getPeriod() const {
        return period;
    }

    void BeaconTime::setPeriod(double period) {
        BeaconTime::period = period;
    }

    std::ostream &operator<<(std::ostream &os, const BeaconTime &time) {
        os << time.hash << "  " << time.t1 << " " << time.t2 << " " << time.period;
        return os;
    }

    std::istream &operator>>(std::istream &is, BeaconTime &time) {
        is >> time.hash >> time.t1 >> time.t2 >> time.period;
        return is;
    }


}