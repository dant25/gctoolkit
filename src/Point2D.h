#ifndef _POINT2D_H_
#define _POINT2D_H_

#include "Point.h"
#include "Vector2D.h"


class Point2D : public Point
{
public:

    Point2D(float x = 0.0, float y = 0.0, long int id = 0);

    virtual ~Point2D();

    virtual unsigned int dimension() const;

    virtual void setPosition(float x, float y);

    virtual float surface(const Point2D &p1, const Point2D &p2) const;
    virtual float surface(const Point2D *p1, const Point2D *p2) const;

    virtual float orientedSurface(const Point2D &p1, const Point2D &p2) const;
    virtual float orientedSurface(const Point2D *p1, const Point2D *p2) const;

    virtual void setX(float x);
    virtual float getX() const;

    virtual void setY(float y);
    virtual float getY() const;

    virtual bool equal(float x, float y) const;

    virtual void draw() const;
};

#endif //#ifndef _POINT2D_H_
