#include "Vector2D.h"
#include <GL/gl.h>

Vector2D::Vector2D(double x, double y, long int id) :
	Vector(2, id)
{
	this->setPosition(x, y);
}

Vector2D::Vector2D(const Point2D &p1, const Point2D &p2) :
	Vector(p1, p2)
{

}

Vector2D::Vector2D(const Vector &v) :
	Vector(2)
{
	this->setPosition(v.getCoord(0), v.getCoord(1));
}

Vector2D::Vector2D(const Vector *v) :
	Vector(2)
{
	this->setPosition(v->getCoord(0), v->getCoord(1));
}

Vector2D::~Vector2D()
{

}

void Vector2D::setPosition(double x, double y)
{
	this->setX(x);
	this->setY(y);
}

void Vector2D::setX(double x)
{
	this->setCoord(0, x);
}

double Vector2D::getX() const
{
	return this->getCoord(0);
}

void Vector2D::setY(double y)
{
	this->setCoord(1, y);
}

double Vector2D::getY() const
{
	return this->getCoord(1);
}

unsigned int Vector2D::dimension() const
{
	return 2;
}

double Vector2D::cross(const Vector2D &v) const
{
	return (this->getX()*v.getY() - this->getY()*v.getX());
}

double Vector2D::cross(const Vector2D *v) const
{
	return this->cross(*v);
}

double Vector2D::scaledCross(const Vector2D &v) const
{
	double norm = this->norm();

	//if the vectors are too small, scale them to approximately 2
	// this is done because the cross product between
	if (norm < 1.0)
	{
		Vector2D v2(this);

		v2.multiply(2.0/norm);

		norm = v.norm();

		if (norm < 1.0)
		{
			Vector2D v3(v);

			v3.multiply(2.0/norm);

			return v2.cross(v3);
		}

		return v2.cross(v);
	}

	norm = v.norm();

	if (norm < 1.0)
	{
		Vector2D v3(v);

		v3.multiply(2.0/norm);

		return this->cross(v3);
	}

	return this->cross(v);
}

double Vector2D::scaledCross(const Vector2D *v) const
{
	return this->scaledCross(*v);
}

double Vector2D::orientedAngle() const
{
	static const Vector2D v(1.0, 0.0);

    double ang = this->angle(v);

    return (this->getY() >= 0.0) ? ang : 2.0*M_PI - ang;
}

double Vector2D::orientedAngle(const Vector2D &v) const
{
	return (v.orientedAngle() - this->orientedAngle());
}

double Vector2D::orientedAngle(const Vector2D *v) const
{
	return this->orientedAngle(*v);
}

bool Vector2D::left(const Vector2D &v) const
{
	//return (this->cross(v) > Shape::getTolerance());
	return (this->scaledCross(v) > 0.0001);
}

bool Vector2D::left(const Vector2D *v) const
{
	return this->left(*v);
}

bool Vector2D::left(const Point2D &p) const
{
	Vector v(p);

	return this->left(p);
}

bool Vector2D::left(const Point2D *p) const
{
	return this->left(*p);
}

bool Vector2D::right(const Vector2D &v) const
{
	//return (this->cross(v) < -Shape::getTolerance());
	return (this->scaledCross(v) < -0.0001);
}

bool Vector2D::right(const Vector2D *v) const
{
	return this->right(*v);
}

bool Vector2D::right(const Point2D &p) const
{
	Vector v(p);

	return this->right(p);
}

bool Vector2D::right(const Point2D *p) const
{
	return this->right(*p);
}

#if USE_OPENGL
void Vector2D::draw() const
{
	glColor(this->getR(), this->getG(), this->getB());

	glBegin(GL_LINES);
		glVertex(0.0, 0.0);
		glVertex(this->coords[0], this->coords[1]);
	glEnd();

	glPointSize(3.0);

	glBegin(GL_POINTS);
		glVertex(0.0, 0.0);
	glEnd();

	glPointSize(1.0);

	/*glPushMatrix();
		glTranslated(this->coords[0], this->coords[1], 0.0);
		glScalef(0.3, 0.3, 1.0);

		glPushMatrix();
			glRotated(30.0, 0.0, 0.0, 1.0);
			glTranslated(-this->coords[0], -this->coords[1], 0.0);
			glBegin(GL_LINES);
				glVertex(0.0, 0.0);
				glVertex(this->coords[0], this->coords[1]);
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glRotated(-30.0, 0.0, 0.0, 1.0);
			glTranslated(-this->coords[0], -this->coords[1], 0.0);
			glBegin(GL_LINES);
				glVertex(0.0, 0.0);
				glVertex(this->coords[0], this->coords[1]);
			glEnd();
		glPopMatrix();
	glPopMatrix();*/
}
#endif //#if USE_OPENGL
