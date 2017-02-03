//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#ifndef TESTERALL_EVENT_H
#define TESTERALL_EVENT_H

#include <ostream>

namespace faker {
    /** \brief A fake measurement event
     *
     *  Contains hash, txPower(taken from beacon), rssi (calculated) and timestamp (faked)
     * */
    class Event {
    public:
        long long hash;
        double txPower;
        double rssi;
        long long timestamp;

        /// Full construtor
        Event(long long int hash, double txPower, double rssi, long long int timestamp);
        /// Default constructor
        Event() {}

        /// Comparison by timestamp only for sorting
        bool operator<(const Event &rhs) const;

        /// ostream output operator
        friend std::ostream &operator<<(std::ostream &os, const Event &event);

    };
}

#endif //TESTERALL_EVENT_H