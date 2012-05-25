#include "Edge3D.h"

#include "Vector3D.h"
#include "Point3D.h"
#include "Point.h"
#include <GL/gl.h>

Edge3D::Edge3D(Point3D *p1, Point3D *p2, long int id) :
	Edge(p1, p2, id)
{
#if USE_SCREENSHOT
	this->setColor(0.0, 0.0, 0.0);
	this->highlight();
#endif //#if USE_SCREENSHOT
}

Edge3D::~Edge3D()
{

}

bool Edge3D::intercept(const Edge3D &e) const
{
	return this->intercept((Point3D *)e.getP1(), (Point3D *)e.getP2());
}

bool Edge3D::intercept(const Edge3D *e) const
{
	return this->intercept(*e);
}

bool Edge3D::intercept(const Point3D &p1, const Point3D &p2) const
{
	double min, max, pmin, pmax;

	//if the bounding boxes of the two edges do not intercept, then
	//	the two edges do not intercept

	Point3D *tp1 = (Point3D *)this->getP1();
	Point3D *tp2 = (Point3D *)this->getP2();

	if (tp1->getX() > tp2->getX())
	{
		min = tp2->getX();
		max = tp1->getX();
	}
	else
	{
		min = tp1->getX();
		max = tp2->getX();
	}

	if (p1.getX() > p2.getX())
	{
		pmin = p2.getX();
		pmax = p1.getX();
	}
	else
	{
		pmin = p1.getX();
		pmax = p2.getX();
	}

	if ((min > pmax) || (max < pmin))
	{
		return false;
	}

	if (tp1->getY() > tp2->getY())
	{
		min = tp2->getY();
		max = tp1->getY();
	}
	else
	{
		min = tp1->getY();
		max = tp2->getY();
	}

	if (p1.getY() > p2.getY())
	{
		pmin = p2.getY();
		pmax = p1.getY();
	}
	else
	{
		pmin = p1.getY();
		pmax = p2.getY();
	}

	if ((min > pmax) || (max < pmin))
	{
		return false;
	}

	Vector3D ab(this->vector());
	Vector3D ac(*tp1, p1);
	Vector3D ad(*tp1, p2);

    Vector3D cd(p1, p2);
	Vector3D ca(p1, *tp1);
	Vector3D cb(p1, *tp2);

    return ( (ab.cross(ac).getX() * ab.cross(ad).getX() +
            ab.cross(ac).getY() * ab.cross(ad).getY() +
            ab.cross(ac).getZ() * ab.cross(ad).getZ() < 0.0)
            &&
            (cd.cross(ca).getX() * cd.cross(cb).getX() +
            cd.cross(ca).getY() * cd.cross(cb).getY() +
            cd.cross(ca).getZ() * cd.cross(cb).getZ() < 0.0) );
}

bool Edge3D::intercept(const Point3D *p1, const Point3D *p2) const
{
	return this->intercept(*p1, *p2);
}

double Edge3D::distance(const Point3D &p) const
{
	Vector3D vec = Vector3D(this->vector());
	Vector3D ac(*(Point3D *)(this->getP1()), p);

	if (ac.cosAngle(vec) < 0.0001)
    {
    	return this->getP1()->distance(p);
    }

    vec.invert();

    ac = Vector3D(*(Point3D *)(this->getP2()), p);

    if (ac.cosAngle(vec) < 0.0001)
    {
    	return this->getP2()->distance(p);
    }

    return this->height(p);

	/*Vector3D vec = Vector3D(this->vector());
	vec.normalize();

	Vector3D ac(*(Point3D *)(this->getP1()), p);
	ac.normalize();

	if (ac.dot(vec) < Shape::getTolerance())
	{
    	return this->getP1()->distance(p);
    }

    vec.invert();

    ac = Vector3D(*(Point3D *)(this->getP2()), p);
    ac.normalize();

    if (ac.dot(vec) < Shape::getTolerance())
    {
    	return this->getP2()->distance(p);
    }

    return this->height(p);*/
}

double Edge3D::distance(const Point3D *p) const
{
	return this->distance(*p);
}

double Edge3D::distance(double x, double y) const
{
	Point3D p(x, y);

	return this->distance(p);
}

double Edge3D::straightDistance(const Point3D &p) const
{
	return this->height(p);
}

double Edge3D::straightDistance(const Point3D *p) const
{
	return this->straightDistance(*p);
}

double Edge3D::straightDistance(double x, double y) const
{
	Point3D p(x, y);

	return this->straightDistance(p);
}

double Edge3D::height(const Point3D &p) const
{
	Point3D *p1 = (Point3D *)this->getP1();
	Point3D *p2 = (Point3D *)this->getP2();

	return (2.0*p1->surface(*p2, p)/this->length());
}

double Edge3D::height(const Point3D *p) const
{
	return this->height(*p);
}

double Edge3D::height(double x, double y) const
{
	Point3D p(x, y);

	return this->height(p);
}

double Edge3D::angle(const Point3D &p1, const Point3D &p2) const
{
	Vector3D ab = this->vector();
	Vector3D ac;

    if (this->getP1()->match(p1))
    {
        ac = Vector3D(p1, p2);
    }
    else if (this->getP1()->match(p2))
    {
        ac = Vector3D(p2, p1);
    }
    else if (this->getP2()->match(p1))
    {
    	ac = Vector3D(p1, p2);
    	ab.multiply(-1.0);
    }
    else if (this->getP2()->match(p2))
    {
        ac = Vector3D(p2, p1);
    	ab.multiply(-1.0);
    }
    else
    {
        return -1.0;
    }

    return ab.angle(ac);
}

double Edge3D::angle(const Point3D *p1, const Point3D *p2) const
{
	return this->angle(*p1, *p2);
}

double Edge3D::angle(const Edge3D &e) const
{
	return this->angle((Point3D *)e.getP1(), (Point3D *)e.getP2());
}

double Edge3D::angle(const Edge3D *e) const
{
	return this->angle(*e);
}

double Edge3D::angle(const Point3D &p) const
{
	/*
	             *   p
	            / \  -----> returns this angle
	           /   \
	          /     \
	         /       \
	        /         \
	       /           \
	      /             \
	     *---------------*
	           this
	*/

	Vector3D v1(p, *(Point3D *)this->getP1());
	Vector3D v2(p, *(Point3D *)this->getP2());

	return v1.angle(v2);
}

double Edge3D::angle(const Point3D *p) const
{
	return this->angle(*p);
}

void Edge3D::draw(bool fill) const
{
	glLineWidth(this->width);

	Point3D *tp1 = (Point3D *)this->getP1();
	Point3D *tp2 = (Point3D *)this->getP2();

	glColor3f(r, g, b);

	glBegin(GL_LINES);
		glVertex2f(tp1->getX(), tp1->getY());
		glVertex2f(tp2->getX(), tp2->getY());
	glEnd();

	glLineWidth(1.0);
}

