#include "Vector3D.h"

#include "Point3D.h"

Vector3D::Vector3D(float x, float y, float z) :
	Vector(3)
{
	this->setPosition(x, y, z);
}

Vector3D::Vector3D(const Vector &v) :
	Vector(3)
{
	this->setPosition(v.getCoord(0), v.getCoord(1), v.getCoord(2));
}

Vector3D::Vector3D(const Vector *v) :
	Vector(3)
{
	this->setPosition(v->getCoord(0), v->getCoord(1), v->getCoord(2));
}

Vector3D::Vector3D(const Point &p) :
	Vector(3)
{
	this->setPosition(p.getCoord(0), p.getCoord(1), p.getCoord(2));
}

Vector3D::Vector3D(const Point *p) :
	Vector(3)
{
	this->setPosition(p->getCoord(0), p->getCoord(1), p->getCoord(2));
}

Vector3D::Vector3D(const Point &p1, const Point &p2) :
	Vector(3)
{
	this->setPosition(p2.getCoord(0) - p1.getCoord(0), p2.getCoord(1) - p1.getCoord(1), p2.getCoord(2) - p1.getCoord(2));
}

Vector3D::Vector3D(const Point *p1, const Point *p2) :
	Vector(3)
{
	this->setPosition(p2->getCoord(0) - p1->getCoord(0), p2->getCoord(1) - p1->getCoord(1), p2->getCoord(2) - p1->getCoord(2));
}

Vector3D::~Vector3D()
{

}

void Vector3D::setPosition(float x, float y, float z)
{
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}

void Vector3D::setX(float x)
{
	//this->setCoord(0, x);
	this->coords[0] = x;
}

float Vector3D::getX() const
{
	//return this->getCoord(0);
	return this->coords[0];
}

void Vector3D::setY(float y)
{
	//this->setCoord(1, y);
	this->coords[1] = y;
}

float Vector3D::getY() const
{
	//return this->getCoord(1);
	return this->coords[1];
}

void Vector3D::setZ(float z)
{
	//this->setCoord(2, z);
	this->coords[2] = z;
}

float Vector3D::getZ() const
{
	//return this->getCoord(2);
	return this->coords[2];
}

unsigned int Vector3D::dimension() const
{
	return 3;
}

Vector3D Vector3D::cross(const Vector3D &v) const
{
	return this->cross(&v);
}

Vector3D Vector3D::cross(const Vector3D *v) const
{
	Vector3D c(this->getY()*v->getZ() - this->getZ()*v->getY(),
			   this->getZ()*v->getX() - this->getX()*v->getZ(),
			   this->getX()*v->getY() - this->getY()*v->getX());

	return c;
}

#if USE_GUI
void Vector3D::draw() const
{
	glColor(this->getR(), this->getG(), this->getB());

	glBegin(GL_LINES);
		glVertex(0.0, 0.0, 0.0);
		glVertex(this->coords[0], this->coords[1], this->coords[2]);
	glEnd();

	//glPointSize(3.0);

	glBegin(GL_POINTS);
		glVertex(0.0, 0.0, 0.0);
	glEnd();

	//glPointSize(1.0);
}
#endif //#if USE_GUI
