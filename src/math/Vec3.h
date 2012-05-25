#ifndef _VEC3_H_
#define _VEC3_H_


#include <cmath>

class Point;

class Vec3 {
    public:
        Vec3();
        Vec3(const Point& p);
        Vec3(double _x, double _y, double _z);

        Vec3 operator+(const Vec3& v) const;
        Vec3& operator+=(const Vec3& v);
        Vec3 operator*(double f) const;
        Vec3& operator*=(double f);
        Vec3 operator/(double f) const;
        Vec3& operator/=(double f);

        double length();

        void normalize();

        double x, y, z;
};

/*Vector operator*(double f, const Vector& v){
	return v*f;
}*/

double Dot(const Vec3& v1, const Vec3& v2);

/*Vector Cross(const Vector& v1, const Vector& v2) {
	return Vector((v1.y*v2.z) - (v1.z*v2.y),
					  (v1.z*v2.x) - (v1.x*v2.z),
					  (v1.x*v2.y) - (v1.y*v2.x));
}

Vector Normalize(Vector& v){
	return v/v.Length();
}*/

#endif
