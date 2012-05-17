#ifndef _EDGE_H_
#define _EDGE_H_

#include "Point.h"
#include "Vector.h"


class Edge
{
public:

    Edge(Point *p1 = NULL, Point *p2 = NULL, long int id = 0);
    virtual ~Edge();

    long int getId() {return id;};

    virtual void setPoints(Point *p1, Point *p2);

    virtual void setP1(Point *p);
    virtual Point *getP1() const;

    virtual void setP2(Point *p);
    virtual Point *getP2() const;

    virtual void setPoint(unsigned int i, Point *p);
    virtual Point *getPoint(unsigned int i) const;

    virtual float length() const;

    virtual float size() const;
    virtual float orientedSize() const;

    virtual Vector vector() const;

    virtual bool in(const Point &p) const;
    virtual bool in(const Point *p) const;

    virtual bool on(const Point &p) const;
    virtual bool on(const Point *p) const;

    virtual bool out(const Point &p) const;
    virtual bool out(const Point *p) const;

    virtual float angle(const Point &p) const;
    virtual float angle(const Point *p) const;

    virtual bool match(const Edge &e) const;
    virtual bool match(const Edge *e) const;
    virtual bool match(const Point &p1, const Point &p2) const;
    virtual bool match(const Point *p1, const Point *p2) const;

    virtual bool equal(const Edge &e) const;
    virtual bool equal(const Edge *e) const;
    virtual bool equal(const Point &p1, const Point &p2) const;
    virtual bool equal(const Point *p1, const Point *p2) const;


    virtual void setWidth(float width) const;
    virtual float getWidth() const;

    virtual void highlight() const;
    virtual void unhighlight() const;

    void setColorR(float color) {r = color;};
    void setColorG(float color) {g = color;};
    void setColorB(float color) {b = color;};

    virtual void draw(bool fill) const = 0;


protected:
    std::vector<Point *> points;

    mutable bool highlightEdge;

    mutable float width;

    float r;
    float g;
    float b;

    long int id;

};


#endif //#ifndef _EDGE_H_
