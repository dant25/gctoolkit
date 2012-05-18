#ifndef _DATA_POINT3D_H_
#define _DATA_POINT3D_H_

//#include "Definitions.h"
#include "Point.h"
#include "Vector3D.h"


class Point3D : public Point
{
public:

    Point3D(float x = 0.0, float y = 0.0, float z = 0.0);
    Point3D(const Point &p);
    Point3D(const Point *p);
    Point3D(const Vector &v);
    Point3D(const Vector *v);
    Point3D(const Point &p, const Vector &v);
    Point3D(const Point *p, const Vector *v);
    virtual ~Point3D();

    virtual void setPosition(float x, float y, float z);

    virtual void setX(float x);
    virtual float getX() const;

    virtual void setY(float y);
    virtual float getY() const;

    virtual void setZ(float z);
    virtual float getZ() const;

    virtual unsigned int dimension() const;

    virtual float surface(const Point3D &p1, const Point3D &p2) const;
    virtual float surface(const Point3D *p1, const Point3D *p2) const;

    virtual float volume(const Point3D &p1, const Point3D &p2, const Point3D &p3) const;
    virtual float volume(const Point3D *p1, const Point3D *p2, const Point3D *p3) const;

    virtual float orientedVolume(const Point3D &p1, const Point3D &p2, const Point3D &p3) const;
    virtual float orientedVolume(const Point3D *p1, const Point3D *p2, const Point3D *p3) const;

    using Point::match;
    virtual bool match(float x, float y, float z);

    using Point::equal;
    virtual bool equal(float x, float y, float z);

#if USE_ARRAY
    using Point::operator=;
#endif //#if USE_ARRAY

#if USE_GUI
    using Point::draw;
    virtual void draw() const;

    virtual UInt fill(GLfloat *coord = NULL, GLfloat *color = NULL, GLfloat *normal = NULL) const;
#endif //#if USE_GUI
};


#endif //#ifndef _DATA_POINT3D_H_
