//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

#include "Point.h"

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
