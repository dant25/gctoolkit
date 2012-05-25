#ifndef _POINT2D_H_
#define _POINT2D_H_

#include "Point.h"
#include "Vector2D.h"


class Point2D : public Point
{
public:

    Point2D(double x = 0.0, double y = 0.0, long int id = 0);
    Point2D(const Point &p);
    Point2D(const Point *p);

    virtual ~Point2D();

    virtual unsigned int dimension() const;

    virtual void setPosition(double x, double y);

    virtual double surface(const Point2D &p1, const Point2D &p2) const;
    virtual double surface(const Point2D *p1, const Point2D *p2) const;

    virtual double orientedSurface(const Point2D &p1, const Point2D &p2) const;
    virtual double orientedSurface(const Point2D *p1, const Point2D *p2) const;

    virtual void setX(double x);
    virtual double getX() const;

    virtual void setY(double y);
    virtual double getY() const;

    virtual bool equal(double x, double y) const;

    virtual void draw() const;
};

#endif //#ifndef _POINT2D_H_
