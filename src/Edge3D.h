#ifndef _Edge3D_H_
#define _Edge3D_H_

#include "Edge.h"
#include "Point3D.h"
#include "Vector3D.h"

class Edge3D : public Edge
{
public:

    Edge3D(Point3D *p1, Point3D *p2, long int id = 0);
    virtual ~Edge3D();

    virtual bool intercept(const Edge3D &e) const;
    virtual bool intercept(const Edge3D *e) const;
    virtual bool intercept(const Point3D &p1, const Point3D &p2) const;
    virtual bool intercept(const Point3D *p1, const Point3D *p2) const;

    virtual float distance(const Point3D &p) const;
    virtual float distance(const Point3D *p) const;
    virtual float distance(float x, float y) const;

    virtual float straightDistance(const Point3D &p) const;
    virtual float straightDistance(const Point3D *p) const;
    virtual float straightDistance(float x, float y) const;

    virtual float height(const Point3D &p) const;
    virtual float height(const Point3D *p) const;
    virtual float height(float x, float y) const;

    virtual float angle(const Point3D &p1, const Point3D &p2) const;
    virtual float angle(const Point3D *p1, const Point3D *p2) const;
    virtual float angle(const Edge3D &e) const;
    virtual float angle(const Edge3D *e) const;
    virtual float angle(const Point3D &p) const;
    virtual float angle(const Point3D *p) const;

    virtual void draw(bool fill) const;
};


#endif //#ifndef _Edge3D_H_
