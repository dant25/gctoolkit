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
    ~Triangle3D();

    virtual unsigned int dimension() const;

    virtual bool accordingToNormal(const Point3D &p, bool insideTest) const;
    virtual bool accordingToNormal(const Point3D *p, bool insideTest) const;

    virtual bool out(const Point &p) const;
    virtual bool out(const Point *p) const;
    virtual bool out(const Point3D &p) const;
    virtual bool out(const Point3D *p) const;

    virtual Point circumcenter() const {};     //TO DO
    virtual Point incenter() const {};         //TO DO

    virtual double solidAngle(const Point3D &p) const;
    virtual double solidAngle(const Point3D *p) const;
    virtual double orientedSolidAngle(const Point3D &p, bool insideTest = false) const;
    virtual double orientedSolidAngle(const Point3D *p, bool insideTest = false) const;

    virtual R3Tuple barycentricCoordinates(const Point &p) const;
    virtual R3Tuple barycentricCoordinates(const Point *p) const;
    virtual R3Tuple barycentricCoordinates(const Point3D &p) const;
    virtual R3Tuple barycentricCoordinates(const Point3D *p) const;

    virtual double surface() const;

    std::list<Triangle*> getAdjTriangleList() {return adjTriangleList;};

#if USE_ARRAY
    using Triangle::operator=;
#endif //#if USE_ARRAY


    using Triangle::draw;
    virtual void draw(bool fill) const;
    //virtual void draw() const;

    virtual unsigned int fill(double *coord = NULL, double *color = NULL, double *normal = NULL) const;


private:
    std::list<Triangle*> adjTriangleList;
};


#endif //#ifndef _DATA_TRIANGLE3D_H_
