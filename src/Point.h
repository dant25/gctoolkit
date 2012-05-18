#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <vector>
#include <math.h>
#include "Vector.h"

class Vector;

class Point
{
public:
    Point(long int id = 0);
    Point(std::vector<float> coords, long int id = 0);

    Point(const Point *p);
    Point(const Vector &v);
    Point(const Vector *v);

    ~Point();

    int getId() {return this->id;};

    virtual unsigned int dimension() const;

    virtual void setCoords(std::vector<float> coords);

    virtual std::vector<float> getCoords() const;

    virtual void setCoord(unsigned int i, float c);
    virtual float getCoord(unsigned int i) const;

    virtual bool match(const Point &p) const;
    virtual bool match(const Point *p) const;

    virtual bool equal(const Point &p) const;
    virtual bool equal(const Point *p) const;

    float distance(const Point &p) const;

    void setColorR(float color) {r = color;};
    void setColorG(float color) {g = color;};
    void setColorB(float color) {b = color;};

    virtual void draw() const;

protected:
    int id;
    float r;
    float g;
    float b;
    std::vector<float> coords;


};

#endif //#ifndef _POINT_H_

