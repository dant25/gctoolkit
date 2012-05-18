#include "Point3D.h"

//#include "State.h"

Point3D::Point3D(float x, float y, float z) :
	Point(3)
{
	this->setPosition(x, y, z);
}

Point3D::Point3D(const Point &p) :
	Point(3)
{
	this->setPosition(p.getCoord(0), p.getCoord(1), p.getCoord(2));
}

Point3D::Point3D(const Point *p) :
	Point(3)
{
	this->setPosition(p->getCoord(0), p->getCoord(1), p->getCoord(2));
}

Point3D::Point3D(const Vector &v) :
	Point(3)
{
	this->setPosition(v.getCoord(0), v.getCoord(1), v.getCoord(2));
}

Point3D::Point3D(const Vector *v) :
	Point(3)
{
	this->setPosition(v->getCoord(0), v->getCoord(1), v->getCoord(2));
}

Point3D::Point3D(const Point &p, const Vector &v) :
	Point(3)
{
	this->setPosition(p.getCoord(0) + v.getCoord(0), p.getCoord(1) + v.getCoord(1), p.getCoord(2) + v.getCoord(2));
}

Point3D::Point3D(const Point *p, const Vector *v) :
	Point(3)
{
	this->setPosition(p->getCoord(0) + v->getCoord(0), p->getCoord(1) + v->getCoord(1), p->getCoord(2) + v->getCoord(2));
}

Point3D::~Point3D()
{

}

void Point3D::setPosition(float x, float y, float z)
{
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}

void Point3D::setX(float x)
{
	//this->setCoord(0, x);
	this->coords[0] = x;
}

float Point3D::getX() const
{
	//return this->getCoord(0);
	return this->coords[0];
}

void Point3D::setY(float y)
{
	//this->setCoord(1, y);
	this->coords[1] = y;
}

float Point3D::getY() const
{
	//return this->getCoord(1);
	return this->coords[1];
}

void Point3D::setZ(float z)
{
	//this->setCoord(2, z);
	this->coords[2] = z;
}

float Point3D::getZ() const
{
	//return this->getCoord(2);
	return this->coords[2];
}

unsigned int Point3D::dimension() const
{
	return 3;
}

float Point3D::surface(const Point3D &p1, const Point3D &p2) const
{
	return surface(&p1, &p2);
}

float Point3D::surface(const Point3D *p1, const Point3D *p2) const
{
	Vector3D ab(this, p1);
	Vector3D ac(this, p2);

	return 0.5*ab.cross(ac).norm();
}

float Point3D::volume(const Point3D &p1, const Point3D &p2, const Point3D &p3) const
{
	return this->volume(&p1, &p2, &p3);
}

float Point3D::volume(const Point3D *p1, const Point3D *p2, const Point3D *p3) const
{
	return fabs(this->orientedVolume(p1, p2, p3));
}

float Point3D::orientedVolume(const Point3D &p1, const Point3D &p2, const Point3D &p3) const
{
	return this->orientedVolume(&p1, &p2, &p3);
}

float Point3D::orientedVolume(const Point3D *p1, const Point3D *p2, const Point3D *p3) const
{
	Vector3D ab(this, p1);
	Vector3D ac(this, p2);
	Vector3D ad(this, p3);

	return ad.dot(ab.cross(ac))/6.0;
}

bool Point3D::match(float x, float y, float z)
{
	return Point::match(Point3D(x, y, z));
}

bool Point3D::equal(float x, float y, float z)
{
	return Point::equal(Point3D(x, y, z));
}

#if USE_GUI
void Point3D::draw() const
{
	if (!getState().isInVisibleSpace(this))
	{
		return;
	}

	//glPointSize(static_cast<GLfloat>(this->getSize()));
#if USE_SCREENSHOT
	glPointSize(static_cast<GLfloat>(this->isHighlighted() ? 5.0 : 1.0));
#else
	glPointSize(static_cast<GLfloat>(this->isHighlighted() ? 5.0 : 2.0));
#endif //#if USE_SCREENSHOT

	glColor(this->getR(), this->getG(), this->getB());

	bool lighting = false;

	if (glIsEnabled(GL_LIGHTING))
	{
		glDisable(GL_LIGHTING);

		lighting = true;
	}

	glPushMatrix();
		this->explodeAndShrink(this, true);

		glBegin(GL_POINTS);
			//glVertex(this->coords[0], this->coords[1], this->coords[2]);
			glVertex(0.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();

	if (lighting)
	{
		glEnable(GL_LIGHTING);
	}

	//glPointSize(1.0);
}

UInt Point3D::fill(GLfloat *coord, GLfloat *color, GLfloat */*normal*/) const
{
	if (!getState().isInVisibleSpace(this))
	{
		return 0;
	}

	if (color)
	{
		color[0] = static_cast<GLfloat>(this->getR());
		color[1] = static_cast<GLfloat>(this->getG());
		color[2] = static_cast<GLfloat>(this->getB());
	}

	coord[0] = static_cast<GLfloat>(0.0);
	coord[1] = static_cast<GLfloat>(0.0);
	coord[2] = static_cast<GLfloat>(0.0);

	this->explodeAndShrink(coord, *this, true);

	return 1;
}
#endif //#if USE_GUI
