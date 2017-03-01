#include "common_types.h"

// This is STUPID, we need these operators in any case
//#if defined(BRIDGE_LIBRARY)

namespace CommonConstants {
const double time_multiplicator = 1.0e-3;

template<>
double big_value<double>() {
    return 1.0e13;
}

} // namepsace CommonConstants

Point operator+(const Point &p1, const Point &p2) {
    Point res = p1;
    res += p2;
    return res;
}

Point operator-(const Point &p1, const Point &p2) {
    Point p = p1;
    p -= p2;
    return p;
}

Point operator*(const Point &p1, const double &val) {
    Point res = p1;
    res.x *= val;
    res.y *= val;
    res.z *= val;
    return res;
}

Point operator / (const Point &p1, const double &val) {
    Point res = p1;
    res.x /= val;
    res.y /= val;
    res.z /= val;
    return res;
}

Point operator*(const double &val, const Point &p1) {
    return p1 * val;
}

Point operator / (const double &val, const Point &p1) {
    return p1 / val;
}

PointMeasurement operator+(const PointMeasurement &p1, const PointMeasurement &p2) {
    PointMeasurement res;
    res.position = p1.position + p2.position;
    res.timestamp = p1.timestamp + p2.timestamp;
    return res;
}

PointMeasurement operator*(const PointMeasurement &p1, const double &val) {
    PointMeasurement res;
    res.position = p1.position * val;
    res.timestamp = p1.timestamp * val;
    return res;
}


Point& Point::operator+=(const Point &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}

Point& Point::operator-=(const Point &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}

Point& Point::operator*=(const Point &rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    this->z *= rhs.z;
    return *this;
}

Point& Point::operator*=(const double &rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}

Point& Point::operator/=(const double &rhs) {
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}

Point& Point::operator/=(const Point &rhs) {
    this->x /= rhs.x;
    this->y /= rhs.y;
    this->z /= rhs.z;
    return *this;
}

Point& Point::operator-() {
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
    return *this;
}

PointMeasurement& PointMeasurement::operator +=(const PointMeasurement &rhs) {
    this->position += rhs.position;
    this->timestamp += rhs.timestamp;
    return *this;
}

std::vector<double> getRssiVectorFromMeasurements(const BeaconMeasurementsContainer &mc) {
    std::vector<double> rssi(mc.size());
    std::vector<double>::iterator rit = rssi.begin();
    for (BeaconMeasurementsContainer::const_iterator it = mc.begin(); it !=mc.end(); ++it, ++rit) {
        *rit = it->rssi;
    }
    return rssi;
}

std::vector<double> getTxVectorFromMeasurements  (const BeaconMeasurementsContainer &mc) {
    std::vector<double> tx(mc.size());
    std::vector<double>::iterator tit = tx.begin();
    for (BeaconMeasurementsContainer::const_iterator it = mc.begin(); it !=mc.end(); ++it, ++tit) {
        *tit = it->txPower;
    }
    return tx;
}

std::vector<time_t> getTimestampVectorFromMeasurements  (const BeaconMeasurementsContainer &mc) {
    std::vector<time_t> tm(mc.size());
    std::vector<time_t>::iterator tit = tm.begin();
    for (BeaconMeasurementsContainer::const_iterator it = mc.begin(); it !=mc.end(); ++it, ++tit) {
        *tit = it->timestamp;
    }
    return tm;
}

//#endif // BRIDGE_LIBRARY

