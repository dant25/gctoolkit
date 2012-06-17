#include "Triangle3D.h"

#include "Point2D.h"
#include "Edge2D.h"
#include "Vector3D.h"
#include "Edge.h"

#include <limits.h>

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

	double l1 = std::get<0>(t);
	double l2 = std::get<1>(t);
	double l3 = std::get<2>(t);*/

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
	//return (insideTest) ? n.cosAngle(v) > -0.0001 : n.cosAngle(v) > 0.0001;
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

Vector3D Triangle3D::normal() const
{
    return Vector3D(this->getP2(), this->getP1()).cross( Vector3D(this->getP3(), this->getP1()) );
}
















bool Triangle3D::intercept(const Triangle3D &t) const
{
	return this->intercept(&t);
}

bool Triangle3D::intercept(const Triangle3D *t) const
{
	bool shareOne = false;

	for (unsigned int i = 0; i < 3; i++)
	{
		Point3D *p = (Point3D*)this->getPoint(i);

		if ((t->have(p)) || (t->have(*p)))
		{
			if (!shareOne)
			{
				shareOne = true;
			}
			else
			{
				return false;
			}
		}
	}

	//std::cout << "shareOne = " << shareOne << std::endl;

	//Code based on book Geometric Tools for Computer Graphics
	Vector3D n = this->normal();
	//std::cout << "n = " << n.text() << std::endl;
	n.normalize();
	//std::cout << "n = " << n.text() << std::endl;

	Vector3D p(this->getP1());
	//std::cout << "p = " << p.text() << std::endl;

	double d = -n.dot(p);
	//std::cout << "d = " << d << std::endl;

	double tdists[3];

	for (unsigned int i = 0; i < 3; i++)
	{
		tdists[i] = Triangle3D::signedPlaneDistance(static_cast<Point3D *>(t->getPoint(i)), &n, d);
		//std::cout << "tdists[" << i << "] = " << tdists[i] << std::endl;
	}

	//if (((tdists[0] < 0.0) && (tdists[1] < 0.0) && (tdists[2] < 0.0)) ||
	//	((tdists[0] > 0.0) && (tdists[1] > 0.0) && (tdists[2] > 0.0)))
	if (((tdists[0] < -0.0001) && (tdists[1] < -0.0001) && (tdists[2] < -0.0001)) ||
		((tdists[0] >  0.0001) && (tdists[1] >  0.0001) && (tdists[2] >  0.0001)))
	{
		//std::cout << "returning false" << std::endl;
		return false;
	}

	Vector3D tn = t->normal();
	//std::cout << "tn = " << tn.text() << std::endl;
	tn.normalize();
	//std::cout << "tn = " << tn.text() << std::endl;

	Vector3D tp(t->getP1());
	//std::cout << "tp = " << tp.text() << std::endl;

	double td = -tn.dot(tp);
	//std::cout << "td = " << td << std::endl;

	double n1n2 = n.dot(tn);
	//std::cout << "n1n2 = " << n1n2 << std::endl;

	//if both triangles lie in parallel planes
	//if (1.0 - std::fabs(tn.dot(n)) < 0.0001)
	if (1.0 - fabs(n1n2) < 0.0001)
	{
		//std::cout << "parallel planes" << std::endl;

		//if the planes are not the same
		if (fabs(td - d) > 0.0001)
		{
			return false;
		}

		//project the points of the triangles in the plane (x, y or z) that
		//  is the most parallel to the triangles
		Vector3D u[3];

		for (unsigned int i = 0; i < 3; i++)
		{
			u[i].setCoord(i, 1.0);
		}

		unsigned int max = 3;
		double maxValue = -DBL_MAX;

		for (unsigned int i = 0; i < 3; i++)
		{
			double dot = fabs(u[i].dot(n));

			if (dot > maxValue)
			{
				maxValue = dot;
				max = i;
			}
		}

		Point2D p[3], tp[3];

		unsigned int coord = 0;

		for (unsigned int i = 0; i < 3; i++)
		{
			if (i == max)
			{
				continue;
			}

			for (unsigned int j = 0; j < 3; j++)
			{
				p[j].setCoord(coord, this->getPoint(j)->getCoord(i));
				tp[j].setCoord(coord, t->getPoint(j)->getCoord(i));
			}

			coord++;
		}

		//create 2D edges for the triangles
		Edge2D e[3] , te[3];

		for (unsigned int i = 0; i < 3; i++)
		{
			e[i].setPoints(&p[i], &p[(i + 1)%3]);
			te[i].setPoints(&tp[i], &tp[(i + 1)%3]);
		}

		//test for 2D edge interceptions
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (e[i].intercept(te[j]))
				{
					return true;
				}
			}
		}

		return false;
	}

	double dists[3];

	for (unsigned int i = 0; i < 3; i++)
	{
		dists[i] = Triangle3D::signedPlaneDistance(static_cast<Point3D *>(this->getPoint(i)), &tn, td);
		//std::cout << "dists[" << i << "] = " << dists[i] << std::endl;
	}

	//if (((dists[0] < 0.0) && (dists[1] < 0.0) && (dists[2] < 0.0)) ||
	//	((dists[0] > 0.0) && (dists[1] > 0.0) && (dists[2] > 0.0)))
	if (((dists[0] < -0.0001) && (dists[1] < -0.0001) && (dists[2] < -0.0001)) ||
		((dists[0] >  0.0001) && (dists[1] >  0.0001) && (dists[2] >  0.0001)))
	{
		//std::cout << "returning false" << std::endl;
		return false;
	}

	//line direction and point
	Vector3D ld = n.cross(tn);
	//std::cout << "ld = " << ld.text() << std::endl;

	//double n1n2 = n.dot(tn);
	double n1 = 1.0; //n.dot(n);
	//std::cout << "n1 = " << n1 << std::endl;
	double n2 = 1.0; //tn.dot(tn);
	//std::cout << "n2 = " << n2 << std::endl;

	double den = n1n2*n1n2 - n1*n2;
	//std::cout << "den = " << den << std::endl;

	d *= -1.0;
	td *= -1.0;

	double a = (td*n1n2 - d*n2)/(den);
	//std::cout << "a = " << a << std::endl;
	double b = (d*n1n2 - td*n1)/(den);
	//std::cout << "b = " << b << std::endl;

	Vector3D ln1(n), ln2(tn);
	//std::cout << "ln1 = " << ln1.text() << std::endl;
	//std::cout << "ln2 = " << ln2.text() << std::endl;
	ln1.multiply(a);
	//std::cout << "ln1 = " << ln1.text() << std::endl;
	ln2.multiply(b);
	//std::cout << "ln2 = " << ln2.text() << std::endl;


	Point3D lp(ln1);

	lp.sum(ln2);
	//std::cout << "lp = " << lp.text() << std::endl;

	double proj[3], tproj[3];

	for (unsigned int i = 0; i < 3; i++)
	{
		proj[i] = ld.dot(Vector3D(&lp, static_cast<Point3D *>(this->getPoint(i))));
		//std::cout << "proj[" << i << "] = " << proj[i] << std::endl;
		tproj[i] = ld.dot(Vector3D(&lp, static_cast<Point3D *>(t->getPoint(i))));
		//std::cout << "tproj[" << i << "] = " << tproj[i] << std::endl;
	}

	//these are the parameters of the line that is the intersection of a
	//  triangle and the plane of the other triangle
	double param[2], tparam[2];
	param[0] = param[1] = tparam[0] = tparam[1] = 0.0;

	//this boolean means that at least one of the distances of the points to the
	//  interception line is 0
	bool zero = false, tzero = false;

	for (unsigned int i = 0; i < 3; i++)
	{
		if (fabs(dists[i]) < 0.0001)
		{
			dists[i] = 0.0;

			zero = true;
		}

		if (fabs(tdists[i]) < 0.0001)
		{
			tdists[i] = 0.0;

			tzero = true;
		}
	}

	//std::cout << "zero = " << std::boolalpha << zero << std::endl;
	//for the this triangle:

	//if one or two points hit the other plane
	if (zero)
	{
		unsigned int z1 = 4, z2 = 4;

		for (unsigned int i = 0; i < 3; i++)
		{
			//if (dists[i] < 0.0001)
			if (dists[i] == 0.0)
			{
				if (z1 == 4)
				{
					z1 = i;
				}
				else
				{
					z2 = i;

					break;
				}
			}
		}

		//std::cout << "z1 = " << z1 << std::endl;
		//std::cout << "z2 = " << z2 << std::endl;

		param[0] = proj[z1];
		//std::cout << "param[0] = " << param[0] << std::endl;

		//if two points hit the other plane
		if (z2 != 4)
		{
			param[1] = proj[z2];
			//std::cout << "param[1] = " << param[1] << std::endl;
		}
		else
		{
			//if there are two points in the same side
			if (((dists[(z1 + 1)%3] < 0.0) && (dists[(z1 + 2)%3] < 0.0)) ||
				((dists[(z1 + 1)%3] > 0.0) && (dists[(z1 + 2)%3] > 0.0)))
			{
				param[1] = proj[z1];
				//std::cout << "param[1] = " << param[1] << std::endl;
			}
			else
			{
				z2 = (z1 + 1)%3;
				//std::cout << "z2 = " << z2 << std::endl;
				z1 = (z1 + 2)%3;
				//std::cout << "z1 = " << z1 << std::endl;

				param[1] = proj[z2] + (proj[z1] - proj[z2])*dists[z2]/(dists[z2] - dists[z1]);
				//std::cout << "param[1] = " << param[1] << std::endl;
			}
		}
	}
	else
	{
		unsigned int different = 4;

		for (unsigned int i = 0; i < 3; i++)
		{
			if (((dists[i] < 0.0) && (dists[(i+1)%3] > 0.0) && (dists[(i+2)%3] > 0.0)) ||
				((dists[i] > 0.0) && (dists[(i+1)%3] < 0.0) && (dists[(i+2)%3] < 0.0)))
			{
				different = i;

				break;
			}
		}

		//std::cout << "different = " << different << std::endl;

		unsigned int z2 = (different + 1)%3;
		//std::cout << "z2 = " << z2 << std::endl;
		unsigned int z1 = (different + 2)%3;
		//std::cout << "z1 = " << z1 << std::endl;

		param[0] = proj[z1] + (proj[different] - proj[z1])*dists[z1]/(dists[z1] - dists[different]);
		//std::cout << "param[0] = " << param[0] << std::endl;
		param[1] = proj[z2] + (proj[different] - proj[z2])*dists[z2]/(dists[z2] - dists[different]);
		//std::cout << "param[1] = " << param[1] << std::endl;
	}

	if (param[0] > param[1])
	{
		double tmp = param[0];
		param[0] = param[1];
		param[1] = tmp;
	}

	//std::cout << "param[0] = " << param[0] << std::endl;
	//std::cout << "param[1] = " << param[1] << std::endl;

	//std::cout << "tzero = " << std::boolalpha << tzero << std::endl;
	//for the other triangle:

	//if one or two points hit the other plane
	if (tzero)
	{
		unsigned int z1 = 4, z2 = 4;

		for (unsigned int i = 0; i < 3; i++)
		{
			//if (tdists[i] < 0.0001)
			if (tdists[i] == 0.0)
			{
				if (z1 == 4)
				{
					z1 = i;
				}
				else
				{
					z2 = i;

					break;
				}
			}
		}

		//std::cout << "z1 = " << z1 << std::endl;
		//std::cout << "z2 = " << z2 << std::endl;

		tparam[0] = tproj[z1];
		//std::cout << "tparam[0] = " << tparam[0] << std::endl;

		//if two points hit the other plane
		if (z2 != 4)
		{
			tparam[1] = tproj[z2];
			//std::cout << "tparam[1] = " << tparam[1] << std::endl;
		}
		else
		{
			//if there are two points in the same side
			if (((tdists[(z1 + 1)%3] < 0.0) && (tdists[(z1 + 2)%3] < 0.0)) ||
				((tdists[(z1 + 1)%3] > 0.0) && (tdists[(z1 + 2)%3] > 0.0)))
			{
				tparam[1] = tproj[z1];
				//std::cout << "tparam[1] = " << tparam[1] << std::endl;
			}
			else
			{
				z2 = (z1 + 1)%3;
				//std::cout << "z2 = " << z2 << std::endl;
				z1 = (z1 + 2)%3;
				//std::cout << "z1 = " << z1 << std::endl;

				tparam[1] = tproj[z2] + (tproj[z1] - tproj[z2])*tdists[z2]/(tdists[z2] - tdists[z1]);
				//std::cout << "tparam[1] = " << tparam[1] << std::endl;
			}
		}
	}
	else
	{
		unsigned int different = 4;

		for (unsigned int i = 0; i < 3; i++)
		{
			if (((tdists[i] < 0.0) && (tdists[(i+1)%3] > 0.0) && (tdists[(i+2)%3] > 0.0)) ||
				((tdists[i] > 0.0) && (tdists[(i+1)%3] < 0.0) && (tdists[(i+2)%3] < 0.0)))
			{
				different = i;

				break;
			}
		}

		//std::cout << "different = " << different << std::endl;

		unsigned int z2 = (different + 1)%3;
		//std::cout << "z2 = " << z2 << std::endl;
		unsigned int z1 = (different + 2)%3;
		//std::cout << "z1 = " << z1 << std::endl;

		tparam[0] = tproj[z1] + (tproj[different] - tproj[z1])*tdists[z1]/(tdists[z1] - tdists[different]);
		//std::cout << "tparam[0] = " << tparam[0] << std::endl;
		tparam[1] = tproj[z2] + (tproj[different] - tproj[z2])*tdists[z2]/(tdists[z2] - tdists[different]);
		//std::cout << "tparam[1] = " << tparam[1] << std::endl;
	}

	if (tparam[0] > tparam[1])
	{
		double tmp = tparam[0];
		tparam[0] = tparam[1];
		tparam[1] = tmp;
	}

	//std::cout << "tparam[0] = " << tparam[0] << std::endl;
	//std::cout << "tparam[1] = " << tparam[1] << std::endl;

	if ((shareOne) &&
		((((param[0] == tparam[0]) || (param[1] == tparam[1])) &&
		  ((param[0] == param[1]) || (tparam[0] == tparam[1]))) ||
		 (param[1] == tparam[0]) ||
		 (param[0] == tparam[1])))
		/*(param[0] == param[1]) &&
		(tparam[0] == tparam[1]) &&
		(param[0] == tparam[0]))*/
		/*(std::fabs(param[0] - param[1]) < 0.0001) &&
		(std::fabs(tparam[0] - tparam[1]) < 0.0001) &&
		(std::fabs(param[0] - tparam[0]) < 0.0001))*/
	{
		//std::cout << "return false 1" << std::endl;
		return false;
	}

	if ((param[1] < tparam[0] + 0.0001) ||
		(tparam[1] < param[0] + 0.0001))
	{
		//std::cout << "return false 2" << std::endl;
		return false;
	}

	//std::cout << "return true" << std::endl;
	return true;
}

bool Triangle3D::intercept(const Edge &e) const
{
	return this->intercept(&e);
}

bool Triangle3D::intercept(const Edge *e) const
{
	//Code based on book Geometric Tools for Computer Graphics
	Vector3D d(e->getP1(), e->getP2());
	Vector3D e1(this->getP1(), this->getP2());
	Vector3D e2(this->getP1(), this->getP3());

	double dnorm = d.norm();
	d.multiply(1.0/dnorm);

	Vector3D p = d.cross(e2);

	double m = p.dot(e1);

	if (fabs(m) < 0.0001)
	{
		return false;
	}

	m = 1.0/m;

	Vector3D s(this->getP1(), e->getP1());

	double u = m*s.dot(p);

	if ((u < 0.0001) || (u > (1.0 - 0.0001)))
	//if ((u < 0.0) || (u > 1.0))
	{
		return false;
	}

	Vector3D q = s.cross(e1);

	double v = m*d.dot(q);

	if ((v < 0.0001) || (v > (1.0 - 0.0001)))
	//if ((v < 0.0) || (v > 1.0))
	{
		return false;
	}

	if ((u + v) > (1.0 - 0.0001))
	//if (u + v > 1.0)
	{
		return false;
	}

	double t = m*e2.dot(q);

	if ((t < 0.0001) || (t > dnorm - 0.0001))
	//if ((t < 0.0001) || (t > 1.0 - 0.0001))
	//if ((t < 0.0) || (t > 1.0))
	{
		return false;
	}

	return true;
}

bool Triangle3D::intercept(const Point3D &p1, const Point3D &p2, const Point3D &p3) const
{
	return this->intercept(&p1, &p2, &p3);
}

bool Triangle3D::intercept(const Point3D *p1, const Point3D *p2, const Point3D *p3) const
{
	Triangle3D t(p1, p2, p3);

	bool intercept = this->intercept(t);

	t.setPoints(NULL, NULL, NULL);

	return intercept;
}

double Triangle3D::signedPlaneDistance(const Point3D &p, const Vector3D &n, double d)
{
	return Triangle3D::signedPlaneDistance(&p, &n, d);
}

double Triangle3D::signedPlaneDistance(const Point3D *p, const Vector3D *n, double d)
{
	return n->dot(p) + d;
}

double Triangle3D::signedPlaneDistance(const Point3D &p) const
{
	return this->signedPlaneDistance(&p);
}

double Triangle3D::signedPlaneDistance(const Point3D *p) const
{
	Vector3D n = this->normal();

	n.normalize();

	double d = -n.dot(this->getP1());

	return this->signedPlaneDistance(p, &n, d);
}

double Triangle3D::signedPlaneDistance(double x, double y, double z) const
{
	return this->signedPlaneDistance(Point3D(x, y, z));
}
