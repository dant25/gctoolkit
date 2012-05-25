#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Point.h"

class Point;

class Vector
{
public:

    Vector(unsigned int dimension = 1, long int id = 0);
    Vector(std::vector<double> coords, long int id = 0);
    Vector(const Vector &v);
    Vector(const Vector *v);
    Vector(const Point &p);
    Vector(const Point *p);
    Vector(const Point &p1, const Point &p2);
    Vector(const Point *p1, const Point *p2);
    virtual ~Vector();

    virtual void setDimension(unsigned int dimension);

    virtual unsigned int dimension() const;

    virtual void setCoords(std::vector<double> coords);
    virtual std::vector<double> getCoords() const;

    virtual void setCoord(unsigned int i, double c);
    virtual double getCoord(unsigned int i) const;

    virtual void sum(const Vector &v);
    virtual void sum(const Vector *v);

    virtual void multiply(double d);

    virtual void invert();

    virtual double dot(const Vector &v) const;
    virtual double dot(const Vector *v) const;

    virtual double norm() const;

    virtual double angle(const Vector &v) const;
    virtual double angle(const Vector *v) const;

    virtual double cosAngle(const Vector &v) const;
    virtual double cosAngle(const Vector *v) const;

    virtual void normalize();

    //matrix should be (dimension + 1) x (dimension + 1)
    virtual void transform(double **matrix);

    virtual bool match(const Vector &v) const;
    virtual bool match(const Vector *v) const;

    virtual bool equal(const Vector &v) const;
    virtual bool equal(const Vector *v) const;

#if USE_OPENGL
    virtual void draw() const;

    virtual std::string text() const;
#endif //#if USE_OPENGL

    long int id;

protected:

    //UInt dimension;

    std::vector<double> coords;
};

#endif //#ifndef _VECTOR_H_
