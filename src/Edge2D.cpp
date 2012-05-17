#include "Edge2D.h"

#include "Vector2D.h"
#include "Point2D.h"
#include "Point.h"
#include <GL/gl.h>

Edge2D::Edge2D(Point2D *p1, Point2D *p2, long int id) :
	Edge(p1, p2, id)
{
#if USE_SCREENSHOT
	this->setColor(0.0, 0.0, 0.0);
	this->highlight();
#endif //#if USE_SCREENSHOT
}

Edge2D::~Edge2D()
{

}

bool Edge2D::intercept(const Edge2D &e) const
{
	return this->intercept((Point2D *)e.getP1(), (Point2D *)e.getP2());
}

bool Edge2D::intercept(const Edge2D *e) const
{
	return this->intercept(*e);
}

bool Edge2D::intercept(const Point2D &p1, const Point2D &p2) const
{
	float min, max, pmin, pmax;

	//if the bounding boxes of the two edges do not intercept, then
	//	the two edges do not intercept

	Point2D *tp1 = (Point2D *)this->getP1();
	Point2D *tp2 = (Point2D *)this->getP2();

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

	Vector2D ab(this->vector());
	Vector2D ac(*tp1, p1);
	Vector2D ad(*tp1, p2);

    Vector2D cd(p1, p2);
	Vector2D ca(p1, *tp1);
	Vector2D cb(p1, *tp2);

    return ((ab.cross(ac)*ab.cross(ad) < 0.0) &&
			(cd.cross(ca)*cd.cross(cb) < 0.0));
}

bool Edge2D::intercept(const Point2D *p1, const Point2D *p2) const
{
	return this->intercept(*p1, *p2);
}

float Edge2D::distance(const Point2D &p) const
{
	Vector2D vec = Vector2D(this->vector());
	Vector2D ac(*(Point2D *)(this->getP1()), p);

	if (ac.cosAngle(vec) < 0.0001)
    {
    	return this->getP1()->distance(p);
    }

    vec.invert();

    ac = Vector2D(*(Point2D *)(this->getP2()), p);

    if (ac.cosAngle(vec) < 0.0001)
    {
    	return this->getP2()->distance(p);
    }

    return this->height(p);

	/*Vector2D vec = Vector2D(this->vector());
	vec.normalize();

	Vector2D ac(*(Point2D *)(this->getP1()), p);
	ac.normalize();

	if (ac.dot(vec) < Shape::getTolerance())
	{
    	return this->getP1()->distance(p);
    }

    vec.invert();

    ac = Vector2D(*(Point2D *)(this->getP2()), p);
    ac.normalize();

    if (ac.dot(vec) < Shape::getTolerance())
    {
    	return this->getP2()->distance(p);
    }

    return this->height(p);*/
}

float Edge2D::distance(const Point2D *p) const
{
	return this->distance(*p);
}

float Edge2D::distance(float x, float y) const
{
	Point2D p(x, y);

	return this->distance(p);
}

float Edge2D::straightDistance(const Point2D &p) const
{
	return this->height(p);
}

float Edge2D::straightDistance(const Point2D *p) const
{
	return this->straightDistance(*p);
}

float Edge2D::straightDistance(float x, float y) const
{
	Point2D p(x, y);

	return this->straightDistance(p);
}

float Edge2D::height(const Point2D &p) const
{
	Point2D *p1 = (Point2D *)this->getP1();
	Point2D *p2 = (Point2D *)this->getP2();

	return (2.0*p1->surface(*p2, p)/this->length());
}

float Edge2D::height(const Point2D *p) const
{
	return this->height(*p);
}

float Edge2D::height(float x, float y) const
{
	Point2D p(x, y);

	return this->height(p);
}

bool Edge2D::left(const Point2D &p) const
{
	Vector2D v(*(Point2D *)this->getP1(), p);

	return Vector2D(this->vector()).left(v);
}

bool Edge2D::left(const Point2D *p) const
{
	return this->left(*p);
}

bool Edge2D::left(float x, float y) const
{
	Point2D p(x, y);

	return this->left(p);
}

bool Edge2D::right(const Point2D &p) const
{
	Vector v(this->getP1(), p);

	return Vector2D(this->vector()).right(v);
}

bool Edge2D::right(const Point2D *p) const
{
	return this->right(*p);
}

bool Edge2D::right(float x, float y) const
{
	Point2D p(x, y);

	return this->right(p);
}

bool Edge2D::accordingToNormal(const Point2D &p, bool insideTest) const
{
	return (insideTest) ? !this->right(p) : this->left(p);
}

float Edge2D::angle(const Point2D &p1, const Point2D &p2) const
{
	Vector2D ab = this->vector();
	Vector2D ac;

    if (this->getP1()->match(p1))
    {
        ac = Vector2D(p1, p2);
    }
    else if (this->getP1()->match(p2))
    {
        ac = Vector2D(p2, p1);
    }
    else if (this->getP2()->match(p1))
    {
    	ac = Vector2D(p1, p2);
    	ab.multiply(-1.0);
    }
    else if (this->getP2()->match(p2))
    {
        ac = Vector2D(p2, p1);
    	ab.multiply(-1.0);
    }
    else
    {
        return -1.0;
    }

    return ab.angle(ac);
}

float Edge2D::angle(const Point2D *p1, const Point2D *p2) const
{
	return this->angle(*p1, *p2);
}

float Edge2D::angle(const Edge2D &e) const
{
	return this->angle((Point2D *)e.getP1(), (Point2D *)e.getP2());
}

float Edge2D::angle(const Edge2D *e) const
{
	return this->angle(*e);
}

float Edge2D::angle(const Point2D &p) const
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

	Vector2D v1(p, *(Point2D *)this->getP1());
	Vector2D v2(p, *(Point2D *)this->getP2());

	return v1.angle(v2);
}

float Edge2D::angle(const Point2D *p) const
{
	return this->angle(*p);
}

float Edge2D::orientedAngle(const Point2D &p, bool insideTest) const
{
	return this->orientedAngle(&p, insideTest);
}

float Edge2D::orientedAngle(const Point2D *p, bool insideTest) const
{
	float angle = this->angle(p);

	if (this->accordingToNormal(*p, insideTest))
	{
		return angle;
	}

	return -angle;
}

Vector2D Edge2D::normal() const
{
	Vector2D normal;

	Point2D *tp1 = (Point2D *)this->getP1();
	Point2D *tp2 = (Point2D *)this->getP2();

    if (!tp1->match(tp2))
    {
		if (fabs(tp1->getX() - tp2->getX()) < 0.0001)
		{
			if (tp1->getY() > tp2->getY())
			{
				normal.setPosition(1.0, 0.0);
			}
			else
			{
				normal.setPosition(-1.0, 0.0);
			}
		}
		else if (fabs(tp1->getY() - tp2->getY()) < 0.0001)
		{
			if (tp1->getX() > tp2->getX())
			{
				normal.setPosition(0.0, -1.0);
			}
			else
			{
				normal.setPosition(0.0, 1.0);
			}
		}
		else
		{
			normal.setPosition(tp1->getY() - tp2->getY(), tp2->getX() - tp1->getX());

			normal.normalize();
		}
    }

    return normal;
}


void Edge2D::draw(bool fill) const
{
	glLineWidth(this->width);

	Point2D *tp1 = (Point2D *)this->getP1();
	Point2D *tp2 = (Point2D *)this->getP2();

	glColor3f(r, g, b);

	glBegin(GL_LINES);
		glVertex2f(tp1->getX(), tp1->getY());
		glVertex2f(tp2->getX(), tp2->getY());
	glEnd();

	glLineWidth(1.0);
}

