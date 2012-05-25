#include "Quaternion.h"


const Quaternion Quaternion::MUL_IDENTITY = Quaternion( 1.0, 0.0, 0.0, 0.0 );
const Quaternion Quaternion::ZERO = Quaternion( 0.0, 0.0, 0.0, 0.0 );

Quaternion::Quaternion(double w, const Vector3& v)
{
    this->w = w;
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

Quaternion::Quaternion(double w, double x, double y, double z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion::Quaternion( const Quaternion& copy )
{
    this->w = copy.w;
    this->x = copy.x;
    this->y = copy.y;
    this->z = copy.z;
}

Quaternion::~Quaternion()
{
}

double Quaternion::length() const
{
    // lenght(Q) = sqrt( w² + x² + y² + z² )
    return (double)sqrt( w * w + x * x + y * y + z * z );
}


Quaternion& Quaternion::normalize()
{
     // If the quaternion is the zero, in other word, the addiction identity,
     // don't normalize it.
     if ( *this == Quaternion::ZERO )
        return *this;

     double len =  1.0 / length();

     x *= len;
     y *= len;
     z *= len;
     w *= len;

     return *this;
}

Quaternion Quaternion::conjugate() const
{
     // A normalized quaternion has the following property: INV(Q) = K(Q),
     // where INV(Q) is the inversion of Q and K(Q) is the conjugate.
     // Thus, let Q = [ w, (xi, yj, zk) ] then K(Q) = [ w, (-xi, -yj, -zk )].
     return Quaternion(w, -x, -y, -z);
}

void Quaternion::quatToMatrix( double *m )
{
     /***********************************************************
      * Converts the quaternion w + xi + yj + zk to a           *
      * row major( OpenGL ) rotation matrix M =                 *
      *                                                         *
      *  | 1 - 2y² - 2z²     2xy + 2wz     2xz - 2wy     0 |    *
      *  |   2xy - 2wz     1 - 2x² - 2z²   2yz + 2wx     0 |    *
      *  |   2xz + 2wy       2yz - 2wx    1 - 2x² - 2y²  0 |    *
      *  |       0               0             0         1 |    *
      *                                                         *
      ***********************************************************/

     double xx, yy, zz, xy, xz, yz, wx, wy, wz;

     xx = 2 * x * x;
     yy = 2 * y * y;
     zz = 2 * z * z;
     xy = 2 * x * y;
     xz = 2 * x * z;
     yz = 2 * y * z;
     wx = 2 * w * x;
     wy = 2 * w * y;
     wz = 2 * w * z;


     m[0] = 1.0 - yy - zz;
     m[1] = xy - wz;
     m[2] = xz + wy;
     m[3] = 0.0;

     m[4] = xy + wz;
     m[5] = 1.0 - xx - zz;
     m[6] = yz - wx;
     m[7] = 0.0;

     m[8] = xz - wy;
     m[9] = yz + wx;
     m[10]= 1.0 - xx - yy;
     m[11]= 0.0;

     m[12]= 0.0;
     m[13]= 0.0;
     m[14]= 0.0;
     m[15]= 1.0;

}

void Quaternion::eulerToQuat( double roll, double pitch, double yaw )
{
    /************************************************************************************
     * Converts the Euler angle representation to quaternion.                           *
     * Q = Qroll * Qpitch * Qyaw                                                        *
	 *                                                                                  *
	 * ( cos(r/2) - i sin(r/2) ) * ( cos(p/2) - j sin(p/2) ) * ( cos(y/2) - ksin(y/2) ) *
     *                                                                                  *
     * The result is a matrix 4x1 as follows:                                           *
     *                                                                                  *
     * | cos(r/2) * cos( p/2 ) * cos( y/2 ) + sin( r/2 ) * sin( p/2 ) * sin( y/2 ) |    *
     * | sin(r/2) * cos( p/2 ) * cos( y/2 ) - cos( r/2 ) * sin( p/2 ) * sin( y/2 ) |    *
     * | cos(r/2) * sin( p/2 ) * cos( y/2 ) + sin( r/2 ) * cos( p/2 ) * sin( y/2 ) |    *
     * | cos(r/2) * cos( p/2 ) * sin( y/2 ) - sin( r/2 ) * sin( p/2 ) * cos( y/2 ) |    *
     *                                                                                  *
     ************************************************************************************/


    double cr, cp, cy, sr, sp, sy, cpcy, spsy;

    //roll *= 0.5;
    //pitch *= 0.5;
    //yaw *= 0.5;

    // computes trigonometry identities
    cr = cos( roll );
	cp = cos( pitch );
	cy = cos( yaw  );


	sr = sin( roll );
	sp = sin( pitch );
	sy = sin( yaw );

	cpcy = cp * cy;
	spsy = sp * sy;


	this->w = cr * cpcy + sr * spsy;
	this->x = sr * cpcy - cr * spsy;
	this->y = cr * sp * cy + sr * cp * sy;
	this->z = cr * cp * sy - sr * sp * cy;

}

void Quaternion::fromAngleAxis( double angle, const Vector3& v )
{
    w = cos( angle );
    x = v.x * sin( angle );
    y = v.y * sin( angle );
    z = v.z * sin( angle );

    this->normalize();
}

void Quaternion::fromAngleAxis( double angle, double x, double y, double z)
{
    fromAngleAxis( angle, Vector3( x, y, z ) );
}

Quaternion Quaternion::operator=( const Quaternion& copy )
{
    w = copy.w;
    x = copy.x;
    y = copy.y;
    z = copy.z;

    return *this;
}

Quaternion Quaternion::operator*( const Quaternion &q ) const
{
    return Quaternion(w * q.w - x * q.x - y * q.y - z * q.z,
                      w * q.x + x * q.w + y * q.z - z * q.y,
                      w * q.y - x * q.z + y * q.w + z * q.x,
                      w * q.z + x * q.y - y * q.x + z * q.w);
}

Quaternion Quaternion::operator+( const Quaternion &q ) const
{
    // Sum each component of the quaternions
    return Quaternion( w + q.w, x + q.x, y + q.y, z + q.z );
}

bool Quaternion::operator==( const Quaternion &q ) const
{
    // Return true if each member of the this quaternion is equal to each
    // member of q
    return ( compareReal( w, q.w ) && compareReal( x, q.x ) &&
             compareReal( y, q.y ) && compareReal( z, q.z ) );
}

bool Quaternion::operator!=( const Quaternion &q ) const
{
    return !(*this == q );
}

Vector3 operator*( const Vector3& v, const Quaternion& q )
{
    Quaternion temp(0, v );
    Quaternion newVector = q * temp * q.conjugate();
    return Vector3( newVector.x, newVector.y, newVector.z );
}

Quaternion Quaternion::operator-() const
{
    return Quaternion( -w, -x, -y, -z );
}

