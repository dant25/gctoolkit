#include "Triangle2D.h"
#include "Vector2D.h"

#include <GL/gl.h>




Triangle2D::Triangle2D(Point2D *p1, Point2D *p2, Point2D *p3, long int id) :
	Triangle(p1, p2, p3, id)
{
    //this->setColor(0.0, 0.0, 0.0);
	this->setColorR(0.0);
	this->setColorG(0.0);
	this->setColorB(0.0);
}

Triangle2D::Triangle2D(const Point2D &p1, const Point2D &p2, const Point2D &p3, long int id) :
	Triangle(new Point2D(p1), new Point2D(p2), new Point2D(p3), id)
{

}

Triangle2D::~Triangle2D()
{

}

unsigned int Triangle2D::dimension() const
{
	return 2;
}

Point Triangle2D::circumcenter() const
{
	Point2D *p1 = (Point2D *)this->getP1();
	Point2D *p2 = (Point2D *)this->getP2();
	Point2D *p3 = (Point2D *)this->getP3();

	if (!p1 || !p2 || !p3)
	{
		return Point();
	}

	//found in http://en.wikipedia.org/wiki/Circumcenter

	Vector2D b(*p1, *p2);
	Vector2D c(*p1, *p3);

	double bdot = b.dot(b);
	double cdot = c.dot(c);

	double d = 2.0*b.cross(c);

	double x = (c.getY()*bdot - b.getY()*cdot)/d;
	double y = (b.getX()*cdot - c.getX()*bdot)/d;

	Point2D p(x + p1->getX(), y + p1->getY());

	return p;

}

Point Triangle2D::incenter() const
{
	Point2D *p1 = (Point2D *)this->getP1();
	Point2D *p2 = (Point2D *)this->getP2();
	Point2D *p3 = (Point2D *)this->getP3();

	if (!p1 || !p2 || !p3)
	{
		return Point();
	}

	//found in http://en.wikipedia.org/wiki/Incircle

	double a = p1->distance(p2);
    double b = p2->distance(p3);
    double c = p3->distance(p1);

    double sum = a + b + c;

    double x = (a*p3->getX() + b*p1->getX() + c*p2->getX())/sum;
    double y = (a*p3->getY() + b*p1->getY() + c*p2->getY())/sum;

    Point2D p(x, y);

    return p;
}

void Triangle2D::draw(bool fill) const
{
/*
	if ((fill) && (!highlighted))
	{
		return;
	}
*/
	glColor3f(r, g, b);

	if (fill)
	{
		glBegin(GL_TRIANGLES);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}

	Point2D *p1 = (Point2D *)this->getP1();
	Point2D *p2 = (Point2D *)this->getP2();
	Point2D *p3 = (Point2D *)this->getP3();

	glVertex2f(p1->getX(), p1->getY());
	glVertex2f(p2->getX(), p2->getY());
	glVertex2f(p3->getX(), p3->getY());

	glEnd();
}
