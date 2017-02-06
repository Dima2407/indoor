//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#ifndef TESTERALL_BEACONTIME_H
#define TESTERALL_BEACONTIME_H

#include <iostream>

namespace faker {
/** \brief Time data for a beacon, i.e. start time, end time, period
 *
 * Here I finally decided to do things properly, i.e. private fields + getters/setters
 *
 * Faker time units (e.g. seconds) are used here, not timestamp units !!!
 * */
    class BeaconTime {
    public:

        /// Full constructor
        BeaconTime(long long int hash, double t1, double t2, double period) : hash(hash), t1(t1), t2(t2),
                                                                              period(period) {}
        /// Default constructor
        BeaconTime() {}

        // Stream IO
        friend std::ostream &operator<<(std::ostream &os, const BeaconTime &time);
        friend std::istream &operator>>(std::istream &is, BeaconTime &time);

        // Getters+setters
        long long int getHash() const;

        void setHash(long long int hash);

        double getT1() const;

        void setT1(double t1);

        double getT2() const;

        void setT2(double t2);

        double getPeriod() const;

        void setPeriod(double period);

    private:
        /// Beacon hash (ID)
        long long hash;
        /// Start time
        double t1;
        /// End time
        double t2;
        /// Perios
        double period;
    };
}


#endif //TESTERALL_BEACONTIME_H
