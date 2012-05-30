#include "Vector3.h"

const Vector3 Vector3::UNIT_X( 1.0, 0.0, 0.0 );
const Vector3 Vector3::UNIT_Y( 0.0, 1.0 , 0.0 );
const Vector3 Vector3::UNIT_Z( 0.0, 0.0, 1.0 );
const Vector3 Vector3::NEGATIVE_UNIT_X( -1.0, 0.0, 0.0 );
const Vector3 Vector3::NEGATIVE_UNIT_Y(  0.0,-1.0, 0.0 );
const Vector3 Vector3::NEGATIVE_UNIT_Z(  0.0, 0.0,-1.0 );
const Vector3 Vector3::ZERO( 0.0, 0.0, 0.0 );

Vector3::Vector3( double x, double y, double z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3( const Vector3 &copy )
{
    *this = copy;
}

Vector3::~Vector3()
{
}

Vector3& Vector3::normalize()
{
    // Check if it's already normalized
    //if ( Math::comparedouble( x*x + y*y + z*z, 1.0f ) )
    //    return *this;

    double m = magnitude();

    if ( compareReal ( m, 0.0 ) )
        return *this;
        //throw exception();

    // optimization: multiplication faster than division
    m = 1.0 / m;
    x *= m;
    y *= m;
    z *= m;

    return *this;

}

double Vector3::angle( const Vector3 &v ) const
{
    return acos( (*this * v)  / (magnitude() * v.magnitude() ) );
}

bool Vector3::operator==(const Vector3 &v) const
{
    if( compareReal ( x, v.x ) &&
        compareReal ( y, v.y ) &&
        compareReal ( z, v.z ) )
        return true;

    return false;
}

Vector3 Vector3::operator/( const Vector3 &v ) const
{
    if ( compareReal ( v.x, 0.0 ) || compareReal ( v.y, 0 ) )
       return *this;
       //throw exception();

    return Vector3(x / v.x, y / v.y, z / v.z );
}

Vector3 Vector3::operator/( double s ) const
{
    if ( compareReal ( s, 0.0 ) )
       return *this;
       //throw exception();

    return Vector3(x / s, y / s, z / s);
}

///////////////////////////////////////////////////////////////
//                 Friend Funtions                            /
///////////////////////////////////////////////////////////////
ostream &operator<<( ostream& output, const Vector3 &operand)
{
    output << "[" << operand.x << ", " << operand.y <<  ", " << operand.z << "] ";
    return output;
}

Vector3 operator*( double s, const Vector3 &v)
{
    return Vector3(v.x * s, v.y * s, v.z * s);
}
