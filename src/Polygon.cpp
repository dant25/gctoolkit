#include "Polygon.h"

#include "Point2D.h"
#include "Point3D.h"
#include "Vector2D.h"
#include "Vector3D.h"

#include <GL/gl.h>

Polygon::Polygon() :
	GeometricShape()
{

}

Polygon::Polygon(unsigned int numPoints) :
	GeometricShape(numPoints)
{

}

Polygon::~Polygon()
{

}

double Polygon::perimeter() const
{
	double d = 0;

	if (this->numPoints() > 2)
	{
		for (unsigned int i = 0; i < this->numPoints() - 1; i++)
		{
			d += points[i]->distance(points[i+1]);
		}

		d += points[this->numPoints() - 1]->distance(this->points[0]);
	}

	return d;
}

double Polygon::orientedSize() const
{
	return this->orientedSurface();
}

bool Polygon::match(const GeometricShape &s) const
{
	return this->match(&s);
}

bool Polygon::match(const GeometricShape *s) const
{
	Polygon *p = dynamic_cast<Polygon *>(const_cast<GeometricShape *>(s));

	return this->match(p);
}

bool Polygon::match(const Polygon &p) const
{
	if (this->numPoints() != p.numPoints())
	{
		return false;
	}

	unsigned int first = 0;

	for (; first < p.numPoints(); first++)
	{
		if ((this->points[0] == p.points[first]) ||
			(this->points[0]->match(p.points[first])))
		{
			break;
		}
	}

	if (first == p.numPoints())
	{
		return false;
	}

	for (unsigned int i = 1; i < this->numPoints(); i++)
	{
		unsigned int next = (first + i)%p.numPoints();

		if ((this->points[i] != p.points[next]) &&
			(!this->points[i]->match(p.points[next])))
		{
			return false;
		}
	}

	return true;
}

bool Polygon::match(const Polygon *p) const
{
	/*if (!p)
	{
		return false;
	}*/

	return p ? ((this == p) || (this->match(*p))) : false;
}

bool Polygon::equal(const GeometricShape &s) const
{
	return this->equal(&s);
}

bool Polygon::equal(const GeometricShape *s) const
{
	Polygon *p = dynamic_cast<Polygon *>(const_cast<GeometricShape *>(s));

	return this->equal(p);
}

bool Polygon::equal(const Polygon &p) const
{
	if (this->numPoints() != p.numPoints())
	{
		return false;
	}

	unsigned int first = 0;

	for (; first < p.numPoints(); first++)
	{
		if ((this->points[0] == p.points[first]) ||
			(this->points[0]->equal(p.points[first])))
		{
			break;
		}
	}

	if (first == p.numPoints())
	{
		return false;
	}

	if (this->numPoints() == 1)
	{
		return true;
	}

	unsigned int incr = 0;

	if ((this->points[1] == p.points[(first + 1)%p.numPoints()]) ||
		(this->points[1]->equal(p.points[(first + 1)%p.numPoints()])))
	{
		incr = 1;
	}
	else if ((this->points[1] == p.points[(first + p.numPoints() - 1)%p.numPoints()]) ||
			 (this->points[1]->equal(p.points[(first + p.numPoints() - 1)%p.numPoints()])))
	{
		incr = p.numPoints() - 1;
	}

	if (incr == 0)
	{
		return false;
	}

	for (unsigned int i = 2; i < this->numPoints(); i++)
	{
		unsigned int next = static_cast<unsigned int>((static_cast<int>(first) + static_cast<int>(i)*incr)%(static_cast<int>(p.numPoints())));

		if ((this->points[i] != p.points[next]) &&
			(!this->points[i]->equal(p.points[next])))
		{
			return false;
		}
	}

	return true;
}

bool Polygon::equal(const Polygon *p) const
{
	/*if (!p)
	{
		return false;
	}*/

	return p ? ((this == p) || (this->equal(*p))) : false;
}

Vector3D Polygon::normal() const
{
	if (this->dimension() == 2)
	{
		Point2D p1(this->getPoint(0));

		Point2D p2(this->getPoint(1));

		Point2D p3(this->getPoint(2));

		Vector2D v1(p1, p2);
		Vector2D v2(p1, p3);

		return Vector3D(0.0, 0.0, v1.cross(v2));
	}

	if (this->dimension() == 3)
	{
		Point3D p1(this->getPoint(0));
		Point3D p2(this->getPoint(1));
		Point3D p3(this->getPoint(2));

		Vector3D v1(p1, p2);
		Vector3D v2(p1, p3);

		return v1.cross(v2);
	}

	return Vector3D();
}

double Polygon::surface() const
{
    return 0;
}

double Polygon::orientedSurface() const
{
    return 0;
}

bool Polygon::in(const Point &p) const
{
    return 0;
}

bool Polygon::in(const Point *p) const
{
    return 0;
}

bool Polygon::on(const Point &p) const
{
    return 0;
}

bool Polygon::on(const Point *p) const
{
    return 0;
}

bool Polygon::out(const Point &p) const
{
    return 0;
}

bool Polygon::out(const Point *p) const
{
    return 0;
}

void Polygon::draw(bool fill) const
{
	glColor3f(r, g, b);

	if (fill)
	{
		glBegin(GL_POLYGON);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}

        for(unsigned int i=0; i <numPoints(); i++)
        {
            glVertex3f(((Point3D *)getPoint(i))->getX(), ((Point3D *)getPoint(i))->getY(), ((Point3D *)getPoint(i))->getZ());
        }

	glEnd();
}

#if USE_GUI
std::string Polygon::text() const
{
	std::stringstream str;

	for (UInt i = 0; i < this->numPoints(); i++)
	{
		str << " ";

		if (this->getPoint(i))
		{
			str << this->getPoint(i)->text();
		}
		else
		{
			str << "-1";
		}
	}

	return str.str();
}
#endif //#if USE_GUI
