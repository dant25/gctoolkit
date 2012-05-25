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

    virtual double distance(const Point3D &p) const;
    virtual double distance(const Point3D *p) const;
    virtual double distance(double x, double y) const;

    virtual double straightDistance(const Point3D &p) const;
    virtual double straightDistance(const Point3D *p) const;
    virtual double straightDistance(double x, double y) const;

    virtual double height(const Point3D &p) const;
    virtual double height(const Point3D *p) const;
    virtual double height(double x, double y) const;

    virtual double angle(const Point3D &p1, const Point3D &p2) const;
    virtual double angle(const Point3D *p1, const Point3D *p2) const;
    virtual double angle(const Edge3D &e) const;
    virtual double angle(const Edge3D *e) const;
    virtual double angle(const Point3D &p) const;
    virtual double angle(const Point3D *p) const;

    virtual void draw(bool fill) const;
};


#endif //#ifndef _Edge3D_H_
