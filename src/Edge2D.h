#ifndef _EDGE2D_H_
#define _EDGE2D_H_

#include "Edge.h"
#include "Point2D.h"
#include "Vector2D.h"

class Edge2D : public Edge
{
public:

    Edge2D(Point2D *p1, Point2D *p2, long int id = 0);
    virtual ~Edge2D();

    virtual bool intercept(const Edge2D &e) const;
    virtual bool intercept(const Edge2D *e) const;
    virtual bool intercept(const Point2D &p1, const Point2D &p2) const;
    virtual bool intercept(const Point2D *p1, const Point2D *p2) const;

    virtual double distance(const Point2D &p) const;
    virtual double distance(const Point2D *p) const;
    virtual double distance(double x, double y) const;

    virtual double straightDistance(const Point2D &p) const;
    virtual double straightDistance(const Point2D *p) const;
    virtual double straightDistance(double x, double y) const;

    virtual double height(const Point2D &p) const;
    virtual double height(const Point2D *p) const;
    virtual double height(double x, double y) const;

    virtual bool left(const Point2D &p) const;
    virtual bool left(const Point2D *p) const;
    virtual bool left(double x, double y) const;

    virtual bool right(const Point2D &p) const;
    virtual bool right(const Point2D *p) const;
    virtual bool right(double x, double y) const;

    virtual bool accordingToNormal(const Point2D &p, bool insideTest = false) const;

    virtual double angle(const Point2D &p1, const Point2D &p2) const;
    virtual double angle(const Point2D *p1, const Point2D *p2) const;
    virtual double angle(const Edge2D &e) const;
    virtual double angle(const Edge2D *e) const;
    virtual double angle(const Point2D &p) const;
    virtual double angle(const Point2D *p) const;
    virtual double orientedAngle(const Point2D &p, bool insideTest = false) const;
    virtual double orientedAngle(const Point2D *p, bool insideTest = false) const;

    virtual Vector2D normal() const;

    virtual void draw(bool fill) const;
};


#endif //#ifndef _EDGE2D_H_
