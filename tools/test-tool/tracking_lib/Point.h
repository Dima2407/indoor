//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

#ifndef TESTTOOL_POINT_H
#define TESTTOOL_POINT_H

#include <list>


/** \brief An (X, Y, Z) point in 3D space
 *
 * Defines trivial operators to work with Points
 */
struct Point {
    Point() : x(0), y(0), z(0) {}
    double x;
    double y;
    double z;

    Point& operator +=(const Point &rhs);
    Point& operator -=(const Point &rhs);
    Point& operator *=(const Point &rhs);
    Point& operator *=(const double &rhs);
    Point& operator /=(const double &rhs);
    Point& operator /=(const Point  &rhs);
    Point& operator  -();
};


Point operator+(const Point &p1, const Point &v2);
Point operator-(const Point &p1, const Point &v2);
Point operator*(const Point &p1, const double &val);
Point operator/(const Point &p1, const double &val);
Point operator*(const double &val, const Point &p1);
Point operator/(const double &val, const Point &p1);


// Types
typedef Point Vector3;
typedef std::list<Point> PointContainer;

#endif //TESTTOOL_POINT_H
