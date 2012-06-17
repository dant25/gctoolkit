#include "Triangle.h"


Triangle::Triangle(Point *p1, Point *p2, Point *p3, long int id)
{
    points.resize(3);
    numPoints = 3;

	this->setPoints(p1, p2, p3);

	r = 0;
	g = 0;
	b = 0;
}

Triangle::~Triangle()
{

}

unsigned int Triangle::dimension() const
{
	return this->points.size();
}

void Triangle::setPoints(Point *p1, Point *p2, Point *p3)
{
	this->setP1(p1);
	this->setP2(p2);
	this->setP3(p3);
}

void Triangle::setPoint(int pos, Point *p)
{
     switch(pos)
    {
        case 0:
            //this->setP1(p);
            this->points[0] = p;
        break;
        case 1:
            //this->setP2(p);
            this->points[1] = p;
        break;
        case 2:
            //this->setP3(p);
            this->points[2] = p;
        break;
    }
}

Point *Triangle::getPoint(int pos) const
{
    switch(pos)
    {
        case 0:
            //return this->getP1();
            return (this->points[0]);
        break;
        case 1:
            //return this->getP2();
            return (this->points[1]);
        break;
        case 2:
            //return this->getP3();
            return (this->points[2]);
        break;
    }
    return NULL;
}

void Triangle::setP1(Point *p)
{
	this->setPoint(0, p);
}

Point *Triangle::getP1() const
{
    if(this->numPoints > 0)
        return this->getPoint(0);
    else
        return NULL;
}

void Triangle::setP2(Point *p)
{
	this->setPoint(1, p);
}

Point *Triangle::getP2() const
{
    if(this->numPoints > 1)
        return (this->getPoint(1));
    else
        return NULL;
}

void Triangle::setP3(Point *p)
{
	this->setPoint(2, p);
}

Point *Triangle::getP3() const
{
    if(this->numPoints > 2)
        return (this->getPoint(2));
    else
        return NULL;
}

bool Triangle::equal(const Triangle *t) const
{
    if(     ( t->getP1()->equal(this->getP1()) || t->getP2()->equal(this->getP1()) || t->getP3()->equal(this->getP1()) )
       &&   ( t->getP1()->equal(this->getP2()) || t->getP2()->equal(this->getP2()) || t->getP3()->equal(this->getP2()) )
       &&   ( t->getP1()->equal(this->getP3()) || t->getP2()->equal(this->getP3()) || t->getP3()->equal(this->getP3()) ) )
        return true;

    return false;
}

bool Triangle::have(const Point *p) const
{
    if( this->getP1()->match(p) || this->getP2()->match(p) || this->getP3()->match(p) )
        return true;

    return false;
}

bool Triangle::have(const Point p) const
{
    if( this->getP1()->match(p) || this->getP2()->match(p) || this->getP3()->match(p) )
        return true;

    return false;
}

