#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Point.h"


class Triangle
{
public:

    Triangle(Point *p1, Point *p2, Point *p3, long int id = 0);
    virtual ~Triangle();

    virtual unsigned int dimension() const;

    virtual void setPoints(Point *p1, Point *p2, Point *p3);

    void setPoint(int pos, Point *p);
    Point *getPoint(int pos) const;

    virtual void setP1(Point *p);
    virtual Point *getP1() const;

    virtual void setP2(Point *p);
    virtual Point *getP2() const;

    virtual void setP3(Point *p);
    virtual Point *getP3() const;

    virtual bool equal(const Triangle *t) const;
    virtual bool have(const Point *p) const;
    virtual bool have(const Point p) const;

/*
    virtual bool in(const Point &p) const = 0;
    virtual bool in(const Point *p) const = 0;

    virtual bool on(const Point &p) const = 0;
    virtual bool on(const Point *p) const = 0;

    virtual bool out(const Point &p) const = 0;
    virtual bool out(const Point *p) const = 0;
*/
    virtual Point circumcenter() const = 0;
    virtual Point incenter() const = 0;

    int numPoints;

    void setColorRGB(double color_R, double color_G ,double color_B) {r = color_R; g = color_G; b = color_B;};

    void setColorR(double color) {r = color;};
    void setColorG(double color) {g = color;};
    void setColorB(double color) {b = color;};

    virtual void draw(bool fill) const = 0;

    protected:
    double r;
    double g;
    double b;

    bool highlighted;
    std::vector<Point*> points;

};

#endif //#ifndef _TRIANGLE_H_
