#ifndef _DATA_GEOMETRIC_SHAPE_H_
#define _DATA_GEOMETRIC_SHAPE_H_

#include "Point.h"
#include "Edge.h"
#include "Vector.h"


class GeometricShape
#if USE_GUI
    : public Data::Colorable
#endif //#if USE_GUI
{
public:

    GeometricShape();
    GeometricShape(unsigned int numPoints);
    virtual ~GeometricShape();

    virtual void setPoint(unsigned int i, Point *p);
    virtual Point *getPoint(unsigned int i) const;

    virtual void setEdge(unsigned int i, Edge *e);
    virtual Edge *getEdge(unsigned int i) const;

    virtual void add(Point *p);
    virtual void remove(Point *p);

    virtual void add(Edge *e);
    virtual void remove(Edge *e);

    virtual unsigned int numPoints() const;

    virtual unsigned int dimension() const;

    virtual double size() const;
    virtual double orientedSize() const = 0;


    virtual Point mid() const;


    virtual bool in(const Point &p) const = 0;
    virtual bool in(const Point *p) const = 0;

    virtual bool on(const Point &p) const = 0;
    virtual bool on(const Point *p) const = 0;

    virtual bool out(const Point &p) const = 0;
    virtual bool out(const Point *p) const = 0;

    virtual bool have(const Point &p) const;
    virtual bool have(const Point *p) const;

    virtual bool match(const GeometricShape &s) const;
    virtual bool match(const GeometricShape *s) const;

    virtual bool equal(const GeometricShape &s) const;
    virtual bool equal(const GeometricShape *s) const;

#if USE_ARRAY
    virtual GeometricShape &operator=(const GeometricShape &s);
#endif //#if USE_ARRAY

#if USE_GUI
    virtual void highlight() const;
    virtual void unhighlight() const;

    using Colorable::draw;
    //virtual void draw(bool fill) const = 0;
    virtual void draw() const = 0;

    virtual bool isInVisibleSpace() const;
#endif //#if USE_GUI

protected:

#if USE_ARRAY
    UShort numPts;
    Point **points;
#else
    std::vector<Point *> points;
    std::vector<Edge *> edges;
#endif //#if USE_ARRAY
};


#endif //#ifndef _DATA_GEOMETRIC_SHAPE_H_

