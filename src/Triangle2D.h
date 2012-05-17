#ifndef _TRIANGLE2D_H_
#define _TRIANGLE2D_H_

#include "Triangle.h"
#include "Point2D.h"

class Triangle2D : public Triangle
{
public:

    Triangle2D(Point2D *p1, Point2D *p2, Point2D *p3, long int id = 0);
    Triangle2D(const Point2D &p1, const Point2D &p2, const Point2D &p3, long int id = 0);
    virtual ~Triangle2D();

    virtual unsigned int dimension() const;

    virtual Point circumcenter() const;
    virtual Point incenter() const;

    virtual void draw(bool fill) const;
};

#endif //#ifndef _TRIANGLE2D_H_
