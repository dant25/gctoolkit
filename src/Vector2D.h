#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include "Vector.h"
#include "Point2D.h"

class Point2D;

class Vector2D : public Vector
{
public:

	Vector2D(double x = 0.0, double y = 0.0, long int id = 0);
	Vector2D(const Point2D &p1, const Point2D &p2);
	Vector2D(const Vector &v);
	Vector2D(const Vector *v);
	virtual ~Vector2D();

	virtual void setPosition(double x, double y);

	virtual void setX(double x);
	virtual double getX() const;

	virtual void setY(double y);
	virtual double getY() const;

	virtual unsigned int dimension() const;

	virtual double cross(const Vector2D &v) const;
	virtual double cross(const Vector2D *v) const;

	virtual double scaledCross(const Vector2D &v) const;
	virtual double scaledCross(const Vector2D *v) const;

	virtual double orientedAngle() const;
	virtual double orientedAngle(const Vector2D &v) const;
	virtual double orientedAngle(const Vector2D *v) const;

	virtual bool left(const Vector2D &v) const;
	virtual bool left(const Vector2D *v) const;

	virtual bool left(const Point2D &p) const;
	virtual bool left(const Point2D *p) const;

	virtual bool right(const Vector2D &v) const;
	virtual bool right(const Vector2D *v) const;

	virtual bool right(const Point2D &p) const;
	virtual bool right(const Point2D *p) const;

#if USE_OPENGL
	virtual void draw() const;
#endif //#if USE_OPENGL
};


#endif //#ifndef _VECTOR2D_H_
