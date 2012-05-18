#ifndef _DATA_VECTOR3D_H_
#define _DATA_VECTOR3D_H_

//#include "Definitions.h"
#include "Vector.h"

class Vector3D : public Vector
{
public:

    Vector3D(float x = 0.0, float y = 0.0, float z = 0.0);
    Vector3D(const Vector &v);
    Vector3D(const Vector *v);
    Vector3D(const Point &p);
    Vector3D(const Point *p);
    Vector3D(const Point &p1, const Point &p2);
    Vector3D(const Point *p1, const Point *p2);
    virtual ~Vector3D();

    virtual void setPosition(float x, float y, float z);

    virtual void setX(float x);
    virtual float getX() const;

    virtual void setY(float y);
    virtual float getY() const;

    virtual void setZ(float z);
    virtual float getZ() const;

    virtual unsigned int dimension() const;

    virtual Vector3D cross(const Vector3D &v) const;
    virtual Vector3D cross(const Vector3D *v) const;

#if USE_ARRAY
    using Vector::operator=;
#endif //#if USE_ARRAY

#if USE_GUI
    using Vector::draw;
    virtual void draw() const;
#endif //#if USE_GUI
};


#endif //#ifndef _DATA_VECTOR3D_H_
