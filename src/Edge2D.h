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

    virtual float distance(const Point2D &p) const;
    virtual float distance(const Point2D *p) const;
    virtual float distance(float x, float y) const;

    virtual float straightDistance(const Point2D &p) const;
    virtual float straightDistance(const Point2D *p) const;
    virtual float straightDistance(float x, float y) const;

    virtual float height(const Point2D &p) const;
    virtual float height(const Point2D *p) const;
    virtual float height(float x, float y) const;

    virtual bool left(const Point2D &p) const;
    virtual bool left(const Point2D *p) const;
    virtual bool left(float x, float y) const;

    virtual bool right(const Point2D &p) const;
    virtual bool right(const Point2D *p) const;
    virtual bool right(float x, float y) const;

    virtual bool accordingToNormal(const Point2D &p, bool insideTest = false) const;

    virtual float angle(const Point2D &p1, const Point2D &p2) const;
    virtual float angle(const Point2D *p1, const Point2D *p2) const;
    virtual float angle(const Edge2D &e) const;
    virtual float angle(const Edge2D *e) const;
    virtual float angle(const Point2D &p) const;
    virtual float angle(const Point2D *p) const;
    virtual float orientedAngle(const Point2D &p, bool insideTest = false) const;
    virtual float orientedAngle(const Point2D *p, bool insideTest = false) const;

    virtual Vector2D normal() const;

    virtual void draw(bool fill) const;
};


#endif //#ifndef _EDGE2D_H_
