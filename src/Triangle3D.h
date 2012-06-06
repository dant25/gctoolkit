#ifndef _DATA_TRIANGLE3D_H_
#define _DATA_TRIANGLE3D_H_

#include <tuple>
#include <iostream>

#include "Triangle2D.h"
#include "Triangle.h"
#include "Point3D.h"
#include "Edge3D.h"

typedef std::tuple<double, double, double> R3Tuple;

class Triangle3D : public Triangle
{
public:

    Triangle3D(Point3D *p1 = NULL, Point3D *p2 = NULL, Point3D *p3 = NULL);
    Triangle3D(const Point3D &p1, const Point3D &p2, const Point3D &p3);
    virtual ~Triangle3D();

    virtual unsigned int dimension() const;

    virtual bool accordingToNormal(const Point3D &p, bool insideTest) const;
    virtual bool accordingToNormal(const Point3D *p, bool insideTest) const;

    virtual bool out(const Point &p) const;
    virtual bool out(const Point *p) const;
    virtual bool out(const Point3D &p) const;
    virtual bool out(const Point3D *p) const;

    virtual double solidAngle(const Point3D &p) const;
    virtual double solidAngle(const Point3D *p) const;
    virtual double orientedSolidAngle(const Point3D &p, bool insideTest = false) const;
    virtual double orientedSolidAngle(const Point3D *p, bool insideTest = false) const;

    virtual R3Tuple barycentricCoordinates(const Point &p) const;
    virtual R3Tuple barycentricCoordinates(const Point *p) const;
    virtual R3Tuple barycentricCoordinates(const Point3D &p) const;
    virtual R3Tuple barycentricCoordinates(const Point3D *p) const;

    virtual double surface() const;

#if USE_ARRAY
    using Triangle::operator=;
#endif //#if USE_ARRAY

#if USE_GUI
    using Triangle::draw;
    //virtual void draw(bool fill) const;
    virtual void draw() const;

    virtual UInt fill(GLfloat *coord = NULL, GLfloat *color = NULL, GLfloat *normal = NULL) const;
#endif //#if USE_GUI

protected:

};


#endif //#ifndef _DATA_TRIANGLE3D_H_
