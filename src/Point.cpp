#include "Point.h"


Point::Point(long int id)
{
    this->id = id;
    r = 0;
    g = 0;
    b = 0;
}

Point::Point(std::vector<double> coords, long int id)
{
	this->setCoords(coords);
    r = 0;
    g = 0;
    b = 0;
}

Point::Point(const Point *p)
{
	this->setCoords(p->getCoords());
    r = 0;
    g = 0;
    b = 0;
}

Point::Point(const Vector &v)
{
	this->setCoords(v.getCoords());
    r = 0;
    g = 0;
    b = 0;
}

Point::Point(const Vector *v)
{
	this->setCoords(v->getCoords());
    r = 0;
    g = 0;
    b = 0;
}

Point::~Point()
{
	this->coords.clear();
}

unsigned int Point::dimension() const
{
	return this->coords.size();
}

void Point::setCoords(std::vector<double> coords)
{
	this->coords = coords;

	//this->dimension = this->coords.size();
}

std::vector<double> Point::getCoords() const
{
	return this->coords;
}

void Point::setCoord(unsigned int i, double c)
{
	if (i < this->dimension())
	{
		this->coords[i] = c;
	}
	else
	{
		std::cout << "debug i (" << i << ") >= dimension(" << this->dimension() << ")" << std::endl;
	}
}

double Point::getCoord(unsigned int i) const
{
    if(i < this->dimension())
        return (this->coords[i]);
    else
    {
		std::cout << "debug i (" << i << ") >= dimension(" << this->dimension() << ")" << std::endl;
		return 0.0;
    }
}

double Point::distance(const Point &p) const
{
    double norm = 0.0;

	for (unsigned int i = 0; i < 2; i++)
	{
		norm += pow(this->coords[i] - p.coords[i], 2.0);
	}

    return sqrt(norm);
}

bool Point::equal(const Point &p) const
{
	unsigned int dim = std::max(this->dimension(), p.dimension());

	for (unsigned int i = 0; i < dim; i++)
	{
		if (fabs(this->getCoord(i) - p.getCoord(i)) > 0.0001)
		{
			return false;
		}
	}

	return true;
}

bool Point::match(const Point &p) const
{
	unsigned int dim = std::max(this->dimension(), p.dimension());

	for (unsigned int i = 0; i < dim; i++)
	{
		//both coordinates should be exactly equal, do not use tolerance here
		if (this->getCoord(i) != p.getCoord(i))
		{
			return false;
		}
	}

	return true;
}

bool Point::match(const Point *p) const
{
	return this->match(*p);
}

bool Point::equal(const Point *p) const
{
	return this->equal(*p);
}

void Point::sum(const Vector &v)
{
	this->sum(&v);
}

void Point::sum(const Vector *v)
{
	unsigned int dim = std::max(v->dimension(), this->dimension());

	//this->setDimension(dim);

	for (unsigned int i = 0; i < dim; i++)
	{
		//this->coords[i] += v.getCoord(i);
		this->setCoord(i, this->getCoord(i) + v->getCoord(i));
	}
}


void Point::draw() const
{

}
