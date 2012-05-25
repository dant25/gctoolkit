#include "GeometricShape.h"
#include <algorithm>

GeometricShape::GeometricShape()
#if USE_GUI
	: Colorable()
#endif //#if USE_GUI
{
#if USE_ARRAY
	this->numPts = 0;
	this->points = NULL;
#endif //#if USE_ARRAY
}

GeometricShape::GeometricShape(unsigned int numPoints)
#if USE_GUI
	: Colorable()
#endif //#if USE_GUI
{
#if USE_ARRAY
	this->numPts = static_cast<UShort>(numPoints);
	this->points = new Point*[this->numPts];
#else
	this->points.resize(numPoints, NULL);
#endif //#if USE_ARRAY
}

GeometricShape::~GeometricShape()
{
	/*while (!this->points.empty())
	{
		if (this->points.back())
		{
			delete this->points.back();
		}

		this->points.pop_back();
	}*/

	//this->points.clear();

#if USE_ARRAY
	if (this->points)
	{
		delete [] this->points;
	}
#endif //#if USE_ARRAY
}

void GeometricShape::setPoint(unsigned int i, Point *p)
{
	//debug
	/*if ((p == NULL) && (i == 1) &&
		((this->getId() == 75118) || (this->getId() == 1202)))
	{
		std::cout << "setting NULL point, id = " << this->getId() << ", numpoints = " << this->numPoints() << std::endl;

		std::cout << p->getId() << std::endl;
	}*/
	//endebug

	if (i < this->numPoints())
	{
		this->points[i] = p;
	}
}

Point *GeometricShape::getPoint(unsigned int i) const
{
	return (i < this->numPoints()) ? this->points[i] : NULL;
}

unsigned int GeometricShape::numPoints() const
{
#if USE_ARRAY
	return this->numPts;
#else
	return this->points.size();
#endif //#if USE_ARRAY
}

unsigned int GeometricShape::dimension() const
{
#if USE_ARRAY
	/*if (!this->points)
	{
		return 0;
	}*/

	return (!this->points) ? 0 : this->points[0]->dimension();
#else

	/*unsigned int dim = 0;

	for (unsigned int i = 0; i < this->numPoints(); i++)
	{
		if (this->points[i]->dimension() > dim)
		{
			dim = this->points[i]->dimension();
		}
	}

	return dim;*/

	return this->points[0]->dimension();
#endif //#if USE_ARRAY
}

double GeometricShape::size() const
{
	return fabs(this->orientedSize());
}

Point GeometricShape::mid() const
{
	Vector v;

	for (unsigned int i = 0; i < this->numPoints(); i++)
	{
		v.sum(this->points[i]);
	}

	v.multiply(1.0/static_cast<double>(this->numPoints()));

	return Point(v);
}

bool GeometricShape::have(const Point &p) const
{
	for (unsigned int i = 0; i < this->numPoints(); i++)
	{
		if (p.equal(this->points[i]))
		{
			return true;
		}
	}

	return false;
}

bool GeometricShape::have(const Point *p) const
{
	//return std::find(this->points.begin(), this->points.end(), p) != this->points.end();

	for (unsigned int i = 0; i < this->numPoints(); i++)
	{
		if (this->points[i] == p)
		{
			return true;
		}
	}

	return false;
}

bool GeometricShape::match(const GeometricShape &s) const
{
	if (this->numPoints() != s.numPoints())
	{
		return false;
	}

	for (unsigned int i = 0; i < this->numPoints(); i++)
	{
		if ((this->points[i] != s.points[i]) &&
			(!this->points[i]->match(s.points[i])))
		{
			return false;
		}
	}

	return true;
}

bool GeometricShape::match(const GeometricShape *s) const
{
	return ((this == s) || (this->match(*s)));
}

bool GeometricShape::equal(const GeometricShape &s) const
{
	if (this->numPoints() != s.numPoints())
	{
		return false;
	}

	for (unsigned int i = 0; i < this->numPoints(); i++)
	{
		bool found = false;

		for (unsigned int j = 0; j < s.numPoints(); j++)
		{
			if ((this->points[i] == s.points[j]) ||
				(this->points[i]->equal(s.points[j])))
			{
				found = true;

				break;
			}
		}

		if (!found)
		{
			return false;
		}
	}

	return true;
}

bool GeometricShape::equal(const GeometricShape *s) const
{
	return ((this == s) || (this->equal(*s)));
}

void GeometricShape::add(Point *p)
{
#if USE_ARRAY
	if (!this->points)
	{
		this->points = new Point*[1];

		this->points[0] = p;

		this->numPts = 1;

		return;
	}

	Point **points = this->points;

	this->points = new Point*[this->numPts + 1];

	for (unsigned int i = 0; i < this->numPts; i++)
	{
		this->points[i] = points[i];
	}

	delete [] points;

	this->points[this->numPts++] = p;
#else
	this->points.push_back(p);
#endif //#if USE_ARRAY
}

void GeometricShape::remove(Point *p)
{
	std::vector<Point *>::iterator it = std::find(this->points.begin(), this->points.end(), p);

	if (it != this->points.end())
	{
		this->points.erase(it);
	}
}

#if USE_ARRAY
GeometricShape &GeometricShape::operator=(const GeometricShape &s)
{
	if (this != &s)
	{
		if (this->numPts != s.numPts)
		{
			if (this->points)
			{
				delete [] this->points;
			}

			this->numPts = s.numPts;

			this->points = new Point*[this->numPts];
		}

		/*if (this->points)
		{
			delete [] this->points;
		}

		this->numPts = s.numPts;

		this->points = new Point*[this->numPts];*/

		for (unsigned int i = 0; i < this->numPts; i++)
		{
			this->points[i] = s.points[i];
		}

#if USE_GUI
		this->setColor(s.r, s.g, s.b);
#endif //#if USE_GUI
	}

	return *this;
}
#endif //#if USE_ARRAY

#if USE_GUI
void GeometricShape::highlight() const
{
	Colorable::highlight();

	for (unsigned int i = 0; i < this->numPoints(); i++)
	{
		this->points[i]->highlight();
	}
}

void GeometricShape::unhighlight() const
{
	Colorable::unhighlight();

	for (unsigned int i = 0; i < this->numPoints(); i++)
	{
		this->points[i]->unhighlight();
	}
}

/*void GeometricShape::draw() const
{
	this->draw(true);
}*/

bool GeometricShape::isInVisibleSpace() const
{
	Box box = this->box();

	Point *min = isPlaneInclusive() ? box.getMin() : box.getMax();
	Point *max = isPlaneInclusive() ? box.getMax() : box.getMin();

	for (unsigned int i = 0; i < 3; i++)
	{
		if (((isPlaneEnabled(2*i    )) && (min->getCoord(i) > getPlaneCoord(2*i    ))) ||
			((isPlaneEnabled(2*i + 1)) && (max->getCoord(i) < getPlaneCoord(2*i + 1))))
		{
			return false;
		}
	}

	return true;
}
#endif //#if USE_GUI
