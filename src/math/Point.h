#ifndef _POINT_H_
#define _POINT_H_

#include "Vec3.h"

class Point {
    public:

        Point() { } ;
        Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { };

        Point operator+(const Vec3& v) const {
            return Point(x + v.x, y + v.y, z + v.z);
        }

        Point& operator+=(const Vec3& v) {
            x += v.x; y += v.y; z += v.z;
            return *this;
        }

        Vec3 operator-(const Point& p) const {
            return Vec3(x - p.x, y - p.y, z - p.z);
        }

        Point operator-(const Vec3& v) const {
            return Point(x - v.x, y - v.y, z- v.z);
        }

        Point& operator-=(const Vec3& v){
            x -= v.x; y -= v.y; z -= v.z;
            return *this;
        }

        Point operator/(double div) const {
            return Point(x/div, y/div, z/div);
        }
        Point& operator/=(double div) {
            x /= div; y/= div; z /= div;
            return *this;
        }


        double x, y, z;
};

//double Distance (const Point& p1, const Point& p2) {
//	return (p1 - p2).Length();
//}

#endif
