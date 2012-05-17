#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Point.h"

class Vector
{
public:

    Vector(unsigned int dimension = 1, long int id = 0);
    Vector(std::vector<float> coords, long int id = 0);
    Vector(const Vector &v);
    Vector(const Vector *v);
    Vector(const Point &p);
    Vector(const Point *p);
    Vector(const Point &p1, const Point &p2);
    Vector(const Point *p1, const Point *p2);
    virtual ~Vector();

    virtual void setDimension(unsigned int dimension);

    virtual unsigned int dimension() const;

    virtual void setCoords(std::vector<float> coords);
    virtual std::vector<float> getCoords() const;

    virtual void setCoord(unsigned int i, float c);
    virtual float getCoord(unsigned int i) const;

    virtual void sum(const Vector &v);
    virtual void sum(const Vector *v);

    virtual void multiply(float d);

    virtual void invert();

    virtual float dot(const Vector &v) const;
    virtual float dot(const Vector *v) const;

    virtual float norm() const;

    virtual float angle(const Vector &v) const;
    virtual float angle(const Vector *v) const;

    virtual float cosAngle(const Vector &v) const;
    virtual float cosAngle(const Vector *v) const;

    virtual void normalize();

    //matrix should be (dimension + 1) x (dimension + 1)
    virtual void transform(float **matrix);

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

    std::vector<float> coords;
};

#endif //#ifndef _VECTOR_H_
