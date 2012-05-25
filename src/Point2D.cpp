#include "Point2D.h"
#include <GL/gl.h>

Point2D::Point2D(double x, double y, long int id) :
	Point(id)
{
    this->coords.resize(2, 0.0);

    this->setX(x);
	this->setY(y);

    this->id = id;

}

Point2D::Point2D(const Point &p) :
	Point(2)
{
	this->setPosition(p.getCoord(0), p.getCoord(1));
}

Point2D::Point2D(const Point *p) :
	Point(2)
{
	this->setPosition(p->getCoord(0), p->getCoord(1));
}

Point2D::~Point2D()
{

}

unsigned int Point2D::dimension() const
{
	return 2;
}

void Point2D::setPosition(double x, double y)
{
	this->setX(x);
	this->setY(y);
}

double Point2D::surface(const Point2D &p1, const Point2D &p2) const
{
	return fabs(this->orientedSurface(p1, p2));
}

double Point2D::surface(const Point2D *p1, const Point2D *p2) const
{
	return this->surface(*p1, *p2);
}

double Point2D::orientedSurface(const Point2D &p1, const Point2D &p2) const
{
	Vector2D ab(*this, p1);
	Vector2D ac(*this, p2);

	return 0.5*ab.cross(ac);
}

double Point2D::orientedSurface(const Point2D *p1, const Point2D *p2) const
{
	return this->orientedSurface(*p1, *p2);
}

void Point2D::setX(double x)
{
	this->setCoord(0, x);
}

double Point2D::getX() const
{
	return this->getCoord(0);
}

void Point2D::setY(double y)
{
	this->setCoord(1, y);
}

double Point2D::getY() const
{
	return this->getCoord(1);
}

bool Point2D::equal(double x, double y) const
{
	Point2D p(x, y);

	return Point::equal(p);
}

//#if USE_OPENGL
void Point2D::draw() const
{
	glPointSize(6);

	glColor3f(r, g, b);

	glBegin(GL_POINTS);
		glVertex2f(this->coords[0], this->coords[1]);
	glEnd();

	glPointSize(1.0);
}
//#endif //#if USE_OPENGL
