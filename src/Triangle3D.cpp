#include "Triangle3D.h"

#include "Point2D.h"
#include "Edge2D.h"
#include "Vector3D.h"
#include "Edge.h"

#include <float.h>
#include <GL/gl.h>

Triangle3D::Triangle3D(Point3D *p1, Point3D *p2, Point3D *p3) :
	Triangle(p1, p2, p3)
{

}

Triangle3D::Triangle3D(const Point3D &p1, const Point3D &p2, const Point3D &p3) :
	Triangle(NULL, NULL, NULL)
{
	this->setPoints(new Point3D(p1), new Point3D(p2), new Point3D(p3));
}

Triangle3D::~Triangle3D()
{

}

unsigned int Triangle3D::dimension() const
{
	return 3;
}

R3Tuple Triangle3D::barycentricCoordinates(const Point &p) const
{
	return this->barycentricCoordinates(&p);
}

R3Tuple Triangle3D::barycentricCoordinates(const Point *p) const
{
	return this->barycentricCoordinates(static_cast<const Point3D *>(p));
}

R3Tuple Triangle3D::barycentricCoordinates(const Point3D &p) const
{
	return this->barycentricCoordinates(&p);
}

R3Tuple Triangle3D::barycentricCoordinates(const Point3D *p) const
{
	double s = this->surface();

	if (s < 0.0001)
	{
		return std::make_tuple(0.0, 0.0, 0.0);
	}

	Point3D *p1 = static_cast<Point3D *>(this->getP1());
	Point3D *p2 = static_cast<Point3D *>(this->getP2());
	Point3D *p3 = static_cast<Point3D *>(this->getP3());

	double l1 = p->surface(p2, p3)/s;
	double l2 = p1->surface(p, p3)/s;
	double l3 = p1->surface(p2, p)/s;

	return std::make_tuple(l1, l2, l3);
}

bool Triangle3D::out(const Point &p) const
{
	return this->out(&p);
}

bool Triangle3D::out(const Point *p) const
{
	return this->out(static_cast<const Point3D *>(p));
}

bool Triangle3D::out(const Point3D &p) const
{
	return this->out(&p);
}

bool Triangle3D::out(const Point3D *p) const
{
	/*R3Tuple t = this->barycentricCoordinates(p);

	Real l1 = std::get<0>(t);
	Real l2 = std::get<1>(t);
	Real l3 = std::get<2>(t);*/

	double l1, l2, l3;

	std::tie(l1, l2, l3) = this->barycentricCoordinates(p);

	return (fabs(l1 + l2 + l3 - 1.0) > 0.0001);
}

double Triangle3D::surface() const
{
	Point3D *p1 = static_cast<Point3D *>(this->getP1());
	Point3D *p2 = static_cast<Point3D *>(this->getP2());
	Point3D *p3 = static_cast<Point3D *>(this->getP3());

	return p1->surface(p2, p3);
}

double Triangle3D::solidAngle(const Point3D &p) const
{
	return this->solidAngle(&p);
}

double Triangle3D::solidAngle(const Point3D *p) const
{
	return fabs(this->orientedSolidAngle(p));
}

double Triangle3D::orientedSolidAngle(const Point3D &p, bool insideTest) const
{
	return this->orientedSolidAngle(&p, insideTest);
}

double Triangle3D::orientedSolidAngle(const Point3D *p, bool insideTest) const
{
	if (!this->out(p))
	{
		return 2.0*M_PI;
	}

	//found in http://en.wikipedia.org/wiki/Solid_angle
	Point3D *p1 = static_cast<Point3D *>(this->getP1());
	Point3D *p2 = static_cast<Point3D *>(this->getP2());
	Point3D *p3 = static_cast<Point3D *>(this->getP3());

	Vector3D a(p, p1);
	Vector3D b(p, p2);
	Vector3D c(p, p3);

	double an = a.norm();
	double bn = b.norm();
	double cn = c.norm();

	double den = an*bn*cn + a.dot(b)*cn + b.dot(c)*an + c.dot(a)*bn;

	if (fabs(den) < 0.0001)
	{
		return 0.0;
	}

	double num = a.dot(c.cross(b));

	double ang = 2.0*atan2(num, den);

	if (fabs(ang) < 0.0001)
	{
		ang = 0.0;
	}

	//std::cout << "ang = " << ang << " ";

	ang = this->accordingToNormal(p, insideTest) ?
		((ang < 0.0) ?  2.0*M_PI + ang : ang) :
		((ang > 0.0) ? -2.0*M_PI + ang : ang);

	/*if (!this->accordingToNormal(p, insideTest))
	{
		std::cout << "NOT ";
	}

	std::cout << "according to normal, angle = " << ang << std::endl;*/

	return ang;

	/*double ang = this->solidAngle(p);

	return (this->accordingToNormal(p, insideTest)) ? ang : -ang;*/
}

bool Triangle3D::accordingToNormal(const Point3D &p, bool insideTest) const
{
	return this->accordingToNormal(&p, insideTest);
}

bool Triangle3D::accordingToNormal(const Point3D *p, bool insideTest) const
{
	//Vector3D n = this->normal();
	Vector3D n = Vector3D(this->getP1(), this->getP2()).cross( Vector3D(this->getP1(), this->getP3()) );
	Vector3D v(static_cast<Point3D *>(this->getP1()), p);

	n.normalize();
	v.normalize();

	//since both n and v are normalized, the cosAngle need not to be called, because
	//  n.cosAngle(v) = n.dot(v)/(n.norm()*v.norm())
	//return (insideTest) ? n.cosAngle(v) > -Data::getTolerance() : n.cosAngle(v) > Data::getTolerance();
	return (insideTest) ? n.dot(v) > -0.0001 : n.dot(v) > 0.0001;
}


//void Triangle3D::draw(bool fill) const
void Triangle3D::draw(bool fill) const
{
	/*if ((!fill) && (!this->isHighlighted()))
	{
		return;
	}*/

	glColor3f(r, g, b);

	//Vector3D n = this->normal();
	//glNormal3f(n.getX(), n.getY(), n.getZ());

	Point3D *p1 = static_cast<Point3D *>(this->getP1());
	Point3D *p2 = static_cast<Point3D *>(this->getP2());
	Point3D *p3 = static_cast<Point3D *>(this->getP3());

	bool changed = false;
	int modes[2];

	glGetIntegerv(GL_POLYGON_MODE, modes);

	bool wireframe = ((modes[0] != GL_FILL) || (modes[1] != GL_FILL));

	//glPushMatrix();

		glBegin(GL_TRIANGLES);
			glVertex3f(p1->getX(), p1->getY(), p1->getZ());
			glVertex3f(p2->getX(), p2->getY(), p2->getZ());
			glVertex3f(p3->getX(), p3->getY(), p3->getZ());
		glEnd();

		if (!wireframe)
		{
			GLboolean lighting = glIsEnabled(GL_LIGHTING);

			if (lighting)
			{
				glDisable(GL_LIGHTING);
			}

			glLineWidth(1.0);

			glBegin(GL_LINE_LOOP);
				glVertex3f(p1->getX(), p1->getY(), p1->getZ());
				glVertex3f(p2->getX(), p2->getY(), p2->getZ());
				glVertex3f(p3->getX(), p3->getY(), p3->getZ());
			glEnd();

			if (lighting)
			{
				glEnable(GL_LIGHTING);
			}
		}
	//glPopMatrix();

	if (changed)
	{
		glPolygonMode(GL_FRONT, modes[0]);
		glPolygonMode(GL_BACK, modes[1]);
	}
}

unsigned int Triangle3D::fill(double *coord, double *color, double *normal) const
{
	if (color)
	{
		color[0] = color[3] = color[6] = static_cast<GLfloat>(r);
		color[1] = color[4] = color[7] = static_cast<GLfloat>(g);
		color[2] = color[5] = color[8] = static_cast<GLfloat>(b);
	}
/*
	if (normal)
	{
		Vector3D n = this->normal();

		normal[0] = normal[3] = normal[6] = static_cast<GLfloat>(n.getX());
		normal[1] = normal[4] = normal[7] = static_cast<GLfloat>(n.getY());
		normal[2] = normal[5] = normal[8] = static_cast<GLfloat>(n.getZ());
	}
*/
	coord[0] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP1())->getX());
	coord[1] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP1())->getY());
	coord[2] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP1())->getZ());

	coord[3] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP2())->getX());
	coord[4] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP2())->getY());
	coord[5] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP2())->getZ());

	coord[6] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP3())->getX());
	coord[7] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP3())->getY());
	coord[8] = static_cast<GLfloat>(static_cast<Point3D *>(this->getP3())->getZ());

	return 3;
}
