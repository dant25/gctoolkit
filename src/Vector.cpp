#include "Vector.h"

Vector::Vector(unsigned int dimension, long int id)
{
    this->id = id;
	this->setDimension(dimension);
}

Vector::Vector(std::vector<double> coords, long int id)
{
    this->id = id;
	this->setCoords(coords);
}

Vector::Vector(const Vector &v)
{
	this->setCoords(v.getCoords());
}

Vector::Vector(const Vector *v)
{
	this->setCoords(v->getCoords());
}

Vector::Vector(const Point &p)
{
	this->setCoords(p.getCoords());
}

Vector::Vector(const Point *p)
{
	this->setCoords(p->getCoords());
}

Vector::Vector(const Point &p1, const Point &p2)
{
	this->setDimension(std::max(p1.dimension(), p2.dimension()));

	unsigned int dim = this->dimension();

	for (unsigned int i = 0; i < dim; i++)
	{
		this->setCoord(i, p2.getCoord(i) - p1.getCoord(i));
	}
}

Vector::Vector(const Point *p1, const Point *p2)
{
	this->setDimension(std::max(p1->dimension(), p2->dimension()));

	unsigned int dim = this->dimension();

	for (unsigned int i = 0; i < dim; i++)
	{
		this->setCoord(i, p2->getCoord(i) - p1->getCoord(i));
	}
}

Vector::~Vector()
{

}

void Vector::setDimension(unsigned int dimension)
{
	//this->dimension = dimension;

	if (dimension != this->dimension())
	{
		this->coords.resize(dimension, 0.0);
	}
}

/*UInt Vector::getDimension() const
{
	return this->dimension();
}*/

unsigned int Vector::dimension() const
{
	return this->coords.size();
}

void Vector::setCoords(std::vector<double> coords)
{
	this->coords = coords;

	//this->dimension = this->coords.size();
}

std::vector<double> Vector::getCoords() const
{
	return this->coords;
}

void Vector::setCoord(unsigned int i, double c)
{
	if (i < this->dimension())
	{
		this->coords[i] = c;
	}
}

double Vector::getCoord(unsigned int i) const
{
	return (i < this->dimension()) ? coords[i] : 0.0;
}

void Vector::sum(const Vector &v)
{
	unsigned int vdim = v.dimension();
	unsigned int tdim = this->dimension();

	if (tdim < vdim)
	{
		//this->dimension = v.getDimension();

		this->coords.resize(vdim, 0.0);

		tdim = vdim;
	}

	for (unsigned int i = 0; i < tdim; i++)
	{
		this->coords[i] += v.getCoord(i);
	}
}

void Vector::sum(const Vector *v)
{
	this->sum(*v);
}

void Vector::multiply(double d)
{
	unsigned int dim = this->dimension();

	for (unsigned int i = 0; i < dim; i++)
	{
		this->coords[i] *= d;
	}
}

void Vector::invert()
{
	this->multiply(-1.0);
}

double Vector::dot(const Vector &v) const
{
	double dot = 0.0;

	unsigned int dim = std::min(this->dimension(), v.dimension());

	for (unsigned int i = 0; i < dim; i++)
	{
		dot += this->coords[i]*v.coords[i];
	}

	return dot;
}

double Vector::dot(const Vector *v) const
{
	return this->dot(*v);
}

double Vector::norm() const
{
	return sqrt(this->dot(this));
}

double Vector::angle(const Vector &v) const
{
	double cos = this->cosAngle(v);

	//some errors might occur due to precision
	if (cos < -1.0)
	{
		cos = -1.0;
	}
	else if (cos > 1.0)
	{
		cos = 1.0;
	}

	return acos(cos);
}

double Vector::angle(const Vector *v) const
{
	return this->angle(*v);
}

double Vector::cosAngle(const Vector &v) const
{
	return this->dot(v)/(this->norm()*v.norm());
}

double Vector::cosAngle(const Vector *v) const
{
	return this->cosAngle(*v);
}

void Vector::normalize()
{
	double n = this->norm();

	//if (std::fabs(n - 1.0) > Shape::getTolerance()) this->multiply(1.0/n);
	if (n > 0.0001) this->multiply(1.0/n);
}

void Vector::transform(double **matrix)
{
	unsigned int dim = this->dimension();

	double values[dim];

	for (unsigned int i = 0; i < dim; i++)
	{
		values[i] = 0.0;

		for (unsigned int j = 0; j < dim; j++)
		{
			values[i] += matrix[i][j] * this->coords[j];
		}

		values[i] += matrix[i][dim];
	}
}

bool Vector::match(const Vector &v) const
{
	unsigned int dim = std::max(this->dimension(), v.dimension());

	for (unsigned int i = 0; i < dim; i++)
	{
		//both coordinates should be exactly equal, do not use tolerance here
		if (this->getCoord(i) != v.getCoord(i))
		{
			return false;
		}
	}

	return true;
}

bool Vector::match(const Vector *v) const
{
	return this->match(*v);
}

bool Vector::equal(const Vector &v) const
{
	unsigned int dim = std::max(this->dimension(), v.dimension());

	for (unsigned int i = 0; i < dim; i++)
	{
		if (fabs(this->getCoord(i) - v.getCoord(i)) < 0.0001)
		{
			return false;
		}
	}

	return true;
}

bool Vector::equal(const Vector *v) const
{
	return this->equal(*v);
}

#if USE_OPENGL
void Vector::draw() const
{

}

std::string Vector::text() const
{
	std::stringstream str;

	str << this->getId();

	for (UInt i = 0; i < this->coords.size(); i++)
	{
		str << " " << this->coords[i];
	}

	str << std::endl;

	return str.str();
}
#endif //#if USE_OPENGL

