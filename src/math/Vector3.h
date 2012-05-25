#ifndef _Vector3_H__
#define _Vector3_H__

#include <ostream>
#include <math.h>


using std::ostream;

/**
 * This class represents a tridimensional vector
 */
class Vector3
{
    friend ostream &operator<<( ostream& output, const Vector3 &operand );
    friend Vector3 operator*(double s, const Vector3 &v );

    public:

        static bool compareReal( double a, double b ) { return (fabs( a - b ) <= 0.001 ); }

        /**
         * Null vector.
         */
        static const Vector3 ZERO;

        /**
         * Unit x vector ( 1.0, 0.0, 0.0 ).
         */
        static const Vector3 UNIT_X;

        /**
         * Unit y vector ( 0.0, 1.0, 0.0 ).
         */
        static const Vector3 UNIT_Y;

        /**
         * Unit z vector ( 0.0, 0.0, 1.0 ).
         */
        static const Vector3 UNIT_Z;

        /**
         * Negative unit x vector ( -1.0, 0.0, 0.0 ).
         */
        static const Vector3 NEGATIVE_UNIT_X;

        /**
         * Negative unit y vector ( 0.0, -1.0, 0.0 ).
         */
        static const Vector3 NEGATIVE_UNIT_Y;

        /**
         * Negative unit z vector ( 0.0, 0.0, -1.0 ).
         */
        static const Vector3 NEGATIVE_UNIT_Z;

    public:

        /**
         * Default constructor
         * Initializes the Vector with the ZERO vector.
         * @param x The x vector's component
         * @param y The y vector's component
         * @param z The z vector's component
         */
        Vector3( double x = 0.0, double y = 0.0, double z = 0.0 );

        /**
         * Copy constructor
         * @param copy The vector to be copied from
         */
        Vector3( const Vector3 &copy );

        /**
         * Default Destructor.
         */
        ~Vector3();

        /**
         * Divides the vector by its magnitude.
         * @return The normalized vector so it can be used in assigning operations.
         */
        Vector3& normalize();

        /**
         * Compute the vector's lenght
         */
        double length() const { return sqrt ( x * x + y * y + z * z ); }

        /**
         * Alias for lenght().
         * @see lenght.
         */
        double magnitude() const { return sqrt ( x * x + y * y + z * z ); }

        /**
         * Computes the distance between this and the v vector.
         * Distance between u and v is given by | u - v |², where | u | is lenght of u.
         * @param v The vector which the distance will be measured from
         * @return The distance between two vectors
         * @see distance2
         */
        double distance( const Vector3 &v) const
        {
            return sqrt( pow( this->x - v.x, 2 ) + pow( this->y - v.y, 2 ) + pow( this->z - v.z, 2 ) );
        }

        /**
         * Computes the power of two distance between this and a vector v
         * @see distance.
         */
        double distance2( const Vector3 &v) const
        {
            return pow( x - v.x, 2) + pow( y - v.y, 2 ) + pow( z - v.z, 2 );
        }

        /** Computes the angle between this and a vector v.
         * @param v The vector to be measured the angle from.
         * @return The angle between this and v.
         */
        double angle(const Vector3 &v) const;

        /**
          * Implements the dot product.
          * @return The dot product of this and v.
          * @see operator*
          */
         double dot( const Vector3 &v ) const { return ( x * v.x + y * v.y + z * v.z ); }

        /**
          * Implements the cross product
          * The cross product of two vectors u and v is given by
          * w = u x v = ( u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x )
          * @return The cross product of this vector and v.
          * @see operator^
          */
         Vector3 cross( const Vector3 &v ) const
         {
            return Vector3( this->y * v.z - this->z * v.y,
                            this->z * v.x - this->x * v.z,
                            this->x * v.y - this->y * v.x );
         }

        /**
         * Implements the assign operator for this class.
         * @param copy The right operand of the assignment.
         * @return The vetor after the assignment. This allows
         * chained calls.
         * @see operator+=
         * @see operator-=
         */
        Vector3& operator=( const Vector3& copy )
        {
            x = copy.x;
            y = copy.y;
            z = copy.z;
            return *this;
        }

        /**
         * Implements the addiction operator.
         * @return this + v
         */
        Vector3 operator+( const Vector3 &v ) const { return Vector3(x + v.x, y + v.y, z + v.z ); }

        /**
         * Implements the '+=' operator where a += b equals to a = a + b.
         * @param v The right operand of the assignment.
         * @return The resulting vector after the assignment. This allows
         * chained calls.
         * @see operator=.
         */
        Vector3& operator+=( const Vector3& v )
        {
            *this = *this + v;
            return *this;
        }

        /**
         * Implements the equal opertator for this class.
         * @param v The vector which will be compared to this.
         * @return True if they are equal, false otherwise.
         * @see operator!=
         */
        bool operator==( const Vector3 &v ) const;

        /**
         * Implements the difference operator for this class.
         * @param v The vector which will be compared to this.
         * @return True if they are different, false otherwise.
         * @see operator==
         */
        bool operator!=( const Vector3 &v ) const { return ( !( *this == v ) ); }

         /**
          * Implements the subtraction operator.
          * @return this - v
          */
        Vector3 operator-( const Vector3 &v ) const { return Vector3(x - v.x, y - v.y, z - v.z ); }

        /**
         * Implements the '-=' operator where a -= b equals to a = a - b.
         * @param v The right operand of the assignment.
         * @return The resulting vector after the assignment. This allows
         * chained calls.
         * @see operator=.
         */
        Vector3 operator-=( const Vector3 &v )
        {
            *this = *this - v;
            return *this;
        }

         /**
          * Implements the 'sign' operator.
          * Invert the sign of the vector.
          * @return A negative vector if this is positive, a positive otherwise.
          */
        Vector3 operator-() const { return Vector3( -x, -y, -z ); }

         /**
          * Implements the dot product operator.
          * @return The dot product of this and v.
          * @see dot
          */
         double operator*( const Vector3 &v ) const { return ( x * v.x + y * v.y + z * v.z ); }

         /**
          * Multiplies a vector by a scalar
          * @param s A scalar to multiply each of vector's component
          * @return The vector multiplied by scalar s
          */
         //Vector3 operator*( const double& s ) const { return ( x * s, y * s, z * s ); }

         /**
          * Implements the cross product operator
          * The cross product of two vectors u and v is given by
          * w = u x v = ( u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x )
          * @return The cross product of this and v.
          * @see cross
          */
         Vector3 operator^( const Vector3 &v ) const
         {
            return Vector3( this->y * v.z - this->z * v.y,
                            this->z * v.x - this->x * v.z,
                            this->x * v.y - this->y * v.x );
         }

         /**
          * Implements the Vector-to-Vector division.
          * @param v The vector which this will be divided from.
          * @return A vector which is this divided by v.
          */
         Vector3 operator/( const Vector3 &v) const;

         /**
          * Implents the Vector-to-Scalar division.
          * Note: The scalar must be a right operand!
          * @param s The number which this will be divided from.
          * @return A vector which is this divided by s.
          */
         Vector3 operator/( double s ) const;

         Vector3 operator/=( double s ) {
            this->x /= s;
            this->y /= s;
            this->z /= s;
            return *this;
         }


    public:

        /**
         * The vector's x component
         */
        double x;

        /**
         * The vector's y component
         */
        double y;

        /**
         * The vector's z component
         */
        double z;
};

/*******************************************************
 *              Friend Operators Section               *
 *******************************************************/

/// Stream extraction operator
ostream &operator<<( ostream& output, const Vector3 &operand);

/// Scalar multiplication operator
Vector3 operator*( double s, const Vector3 &v );

#endif
