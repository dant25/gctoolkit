#ifndef _DATA_POLYGON_H_
#define _DATA_POLYGON_H_

#include "GeometricShape.h"
#include "Vector3D.h"

class Polygon : public GeometricShape
{
public:

    Polygon();
    Polygon(unsigned int numPoints);
    virtual ~Polygon();

    virtual double perimeter() const;
    virtual double surface() const;// = 0;
    virtual double orientedSurface() const;// = 0;

    virtual double orientedSize() const;

    virtual Vector3D normal() const;

    virtual bool in(const Point &p) const;// = 0;
    virtual bool in(const Point *p) const;// = 0;

    virtual bool on(const Point &p) const;// = 0;
    virtual bool on(const Point *p) const;// = 0;

    virtual bool out(const Point &p) const;// = 0;
    virtual bool out(const Point *p) const;// = 0;

    virtual bool match(const GeometricShape &s) const;
    virtual bool match(const GeometricShape *s) const;
    virtual bool match(const Polygon &p) const;
    virtual bool match(const Polygon *p) const;

    virtual bool equal(const GeometricShape &s) const;
    virtual bool equal(const GeometricShape *s) const;
    virtual bool equal(const Polygon &p) const;
    virtual bool equal(const Polygon *p) const;

    virtual void draw(bool fill) const;

    void setColorR(double color) {r = color;};
    void setColorG(double color) {g = color;};
    void setColorB(double color) {b = color;};

#if USE_ARRAY
    using GeometricShape::operator=;
#endif //#if USE_ARRAY

#if USE_GUI
    //virtual void draw() const = 0;

    virtual std::string text() const;
#endif //#if USE_GUI

    protected:
        double r;
        double g;
        double b;

};


#endif //#ifndef _DATA_POLYGON_H_
