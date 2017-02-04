//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#include "Event.h"

faker::Event::Event(long long int hash, double txPower, double rssi, long long int timestamp) : hash(hash),
                                                                                                txPower(txPower),
                                                                                                rssi(rssi),
                                                                                                timestamp(timestamp) {}

bool faker::Event::operator<(const faker::Event &rhs) const {
    return timestamp < rhs.timestamp;
}

namespace faker {
    std::ostream &operator<<(std::ostream &os, const faker::Event &event) {
        os << event.hash << " " << event.txPower << " " << event.rssi << " " << event.timestamp;
        return os;
    }
}