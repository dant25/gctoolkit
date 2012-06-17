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

    virtual Point circumcenter() const {return Point();};     //TO DO
    virtual Point incenter() const {return Point();};         //TO DO

    virtual Vector3D normal() const;

    virtual double solidAngle(const Point3D &p) const;
    virtual double solidAngle(const Point3D *p) const;
    virtual double orientedSolidAngle(const Point3D &p, bool insideTest = false) const;
    virtual double orientedSolidAngle(const Point3D *p, bool insideTest = false) const;

    virtual R3Tuple barycentricCoordinates(const Point &p) const;
    virtual R3Tuple barycentricCoordinates(const Point *p) const;
    virtual R3Tuple barycentricCoordinates(const Point3D &p) const;
    virtual R3Tuple barycentricCoordinates(const Point3D *p) const;

    virtual bool intercept(const Triangle3D &t) const;
    virtual bool intercept(const Triangle3D *t) const;
    virtual bool intercept(const Edge &e) const;
    virtual bool intercept(const Edge *e) const;
    virtual bool intercept(const Point3D &p1, const Point3D &p2, const Point3D &p3) const;
    virtual bool intercept(const Point3D *p1, const Point3D *p2, const Point3D *p3) const;

    static double signedPlaneDistance(const Point3D &p, const Vector3D &n, double d);
    static double signedPlaneDistance(const Point3D *p, const Vector3D *n, double d);

    virtual double signedPlaneDistance(const Point3D &p) const;
    virtual double signedPlaneDistance(const Point3D *p) const;
    virtual double signedPlaneDistance(double x, double y, double z) const;

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
