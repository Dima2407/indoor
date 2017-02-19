//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#include "Event.h"
#include <iomanip>

namespace tester {
    Event::Event(long long int hash, double txPower, double rssi, long long int timestamp) : hash(hash),
                                                                                             txPower(txPower),
                                                                                             rssi(rssi),
                                                                                             timestamp(timestamp) {}

    bool Event::operator<(const Event &rhs) const {
        return timestamp < rhs.timestamp;
    }


    std::ostream &operator<<(std::ostream &os, const Event &event) {
        using namespace std;
        os << setw(6) << event.hash << " " << setw(12) << event.txPower << " " << setw(12) << event.rssi << " "
           << setw(12) << event.timestamp;
        return os;
    }

    std::istream &operator>>(std::istream &is, Event &event) {
        is >> event.hash >> event.txPower >> event.rssi >> event.timestamp;
        return is;
    }
}