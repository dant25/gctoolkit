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
    Point(std::vector<double> coords, long int id = 0);

    Point(const Point *p);
    Point(const Vector &v);
    Point(const Vector *v);

    ~Point();

    int getId() {return this->id;};
    void setId(int i) {this->id = i;};

    virtual unsigned int dimension() const;

    virtual void setCoords(std::vector<double> coords);

    virtual std::vector<double> getCoords() const;

    virtual void setCoord(unsigned int i, double c);
    virtual double getCoord(unsigned int i) const;

    virtual bool match(const Point &p) const;
    virtual bool match(const Point *p) const;

    virtual bool equal(const Point &p) const;
    virtual bool equal(const Point *p) const;

    double distance(const Point &p) const;

    void setColorRGB(double color_R, double color_G ,double color_B) {r = color_R; g = color_G; b = color_B;};

    void setColorR(double color) {r = color;};
    void setColorG(double color) {g = color;};
    void setColorB(double color) {b = color;};

    virtual void sum(const Vector &v);
    virtual void sum(const Vector *v);

    virtual void draw() const;

protected:
    int id;
    double r;
    double g;
    double b;
    std::vector<double> coords;


};

#endif //#ifndef _POINT_H_

