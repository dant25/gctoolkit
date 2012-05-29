#include "Edge.h"

Edge::Edge(Point *p1, Point *p2, long int id)
{
	this->points.resize(2, NULL);

	this->setPoints(p1, p2);

	this->setWidth(1.5);

	r = 0;
	g = 0;
	b = 0;

	this->id = id;
}

Edge::~Edge()
{

}

void Edge::setPoints(Point *p1, Point *p2)
{
	this->setP1(p1);
	this->setP2(p2);
}

void Edge::setP1(Point *p)
{
	this->setPoint(0, p);
}

Point *Edge::getP1() const
{
	return this->getPoint(0);
}

void Edge::setP2(Point *p)
{
	this->setPoint(1, p);
}

Point *Edge::getP2() const
{
	return this->getPoint(1);
}

void Edge::setPoint(unsigned int i, Point *p)
{
	if (i < this->points.size())
	{
		this->points[i] = p;
	}
}

Point *Edge::getPoint(unsigned int i) const
{
	return (i < this->points.size()) ? points[i] : NULL;
}

double Edge::length() const
{
	return this->vector().norm();
}

double Edge::size() const
{
	return this->length();
}

double Edge::orientedSize() const
{
	return this->size();
}

Vector Edge::vector() const
{
	Vector v(this->getP1(), this->getP2());

	return v;
}

bool Edge::in(const Point &p) const
{
	double d1 = p.distance(this->getP1());
	double d2 = p.distance(this->getP2());

	return ((fabs(d1 + d2 - this->length()) < 0.0001));
}

bool Edge::in(const Point *p) const
{
	return in(*p);
}

bool Edge::on(const Point &p) const
{
	return ((p.equal(this->getP1())) || (p.equal(this->getP2())));
}

bool Edge::on(const Point *p) const
{
	return ((p == this->getP1()) || (p == this->getP2()) || (on(*p)));
}

bool Edge::out(const Point &p) const
{
	return !this->in(p);
}

bool Edge::out(const Point *p) const
{
	return this->out(*p);
}

double Edge::angle(const Point &p) const
{
	return this->angle(&p);
}

double Edge::angle(const Point *p) const
{
	Vector v1(p, this->getP1());
	Vector v2(p, this->getP2());

	return v1.angle(v2);
}

bool Edge::match(const Edge &e) const
{
	return this->match(*(e.getP1()), *(e.getP2()));
}

bool Edge::match(const Edge *e) const
{
	return this->match(e->getP1(), e->getP2());
}

bool Edge::match(const Point &p1, const Point &p2) const
{
	return (((this->getP1()->match(p1)) && (this->getP2()->match(p2))) ||
			((this->getP1()->match(p2)) && (this->getP2()->match(p1))));
}

bool Edge::match(const Point *p1, const Point *p2) const
{
	return (((this->getP1() == p1) && (this->getP2() == p2)) ||
			((this->getP1() == p2) && (this->getP2() == p1)));
}

bool Edge::equal(const Edge &e) const
{
	return this->equal(e.getP1(), e.getP2());
}

bool Edge::equal(const Edge *e) const
{
	return this->equal(*e);
}

bool Edge::equal(const Point &p1, const Point &p2) const
{
	return (((this->getP1()->equal(p1)) && (this->getP2()->equal(p2))) ||
			((this->getP1()->equal(p2)) && (this->getP2()->equal(p1))));
}

bool Edge::equal(const Point *p1, const Point *p2) const
{
	return ((this->match(p1, p2)) || (this->equal(*p1, *p2)));
}


void Edge::setWidth(double width) const
{
	this->width = width;
}

double Edge::getWidth() const
{
	return this->width;
}

void Edge::highlight() const
{
	highlightEdge = true;


	this->setWidth(2.0);

	this->setWidth(3.0);

}

void Edge::unhighlight() const
{
	highlightEdge = false;

	this->setWidth(1.0);
}
/*
void Edge::draw(bool fill) const
{

}
*/
