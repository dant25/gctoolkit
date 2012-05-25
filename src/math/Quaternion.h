#ifndef _QUATERNION_H__
#define _QUATERNION_H__

#include "Vector3.h"

/**
 * This class represents a quaternion in the form  [w, (xi + yj + zk)]. A unitary quaternions can be used to represent
 * rotations. Through quaternions interporlation a smooth rotation can be achieved. Some methods are provided to
 * change the quarternion representation to other common rotation representations like: Euler Angle, Axis Angle and rotation matrixes.
 */

class Quaternion
{
    friend Vector3 operator*(const Vector3& v, const Quaternion &q );
    public:

        /**
        * Defines the multiplication identity quaternion [1.0, (0.0, 0.0, 0.0)].
        */
        static const Quaternion MUL_IDENTITY;

        /**
        * Defines the addiction identity quaternion [0.0, (0.0, 0.0, 0.0)].
        */
        static const Quaternion ZERO;

    public:

        static bool compareReal( double a, double b ) { return (fabs( a - b ) <= 0.001 ); }

        /**
        * Default constructor. Initializes the Quaternion as the multiplication identity.
        * @param w scalar part.
        * @param x The x component of the vector part.
        * @param y The y component of the vector part.
        * @param z The z component of the vector part.
        */
        Quaternion( double w = 1.0, double x = 0.0, double y = 0.0, double z = 0.0);

        /**
        * [1.0, (0.0, 0.0, 0.0)].
        * @param w scalar part.
        * @param v vector part.
        */
        Quaternion( double w, const Vector3& v );

        /**
        * Copy constructor.
        * @param copy The Quaternio to be copied from.
        */
        Quaternion( const Quaternion& copy );

        /**
        * Default destructor.
        */
        ~Quaternion();

        /**
        * Computes the lenght of a Quaternion. |Q| = sqrt( w² + x² + y² + z² ).
        * @return The lenght of this quaternion.
        */
        double length() const;

        /**
        * Normalizes the quaternion, i.e, divides it by its lenght. norm(Q) = Q / |Q|
        * @return The normalized quaternion. This allows to use it in attribuitions.
        * Ex: Q = P.normalize();
        */
        Quaternion& normalize();

        /**
        * Computes the quaterion conjugate.
        * A normalized quaternion has the following property: INV(Q) = K(Q),
        * where INV(Q) is the inversion of Q and K(Q) is the conjugate.
        * Thus, let Q = [ w, (xi, yj, zk) ] then K(Q) = [ w, (-xi, -yj, -zk )].
        * @return The quaternion's conjugate.
        */
        Quaternion conjugate() const;

        /**
        * Converts a quaternion to a row major matrix representation( the one used in OpenGL ).
        * @param m A pointer to a matrix which will represent the quaternion.
        */
        void quatToMatrix( double *m );

        /**
        * Converts from Euler angles representation to quaternion.
        * @param pitch The amount of rotation ( in degrees ) around the x-axis.
        * @param yaw The amount of rotation ( in degrees ) around the y-axis.
        * @param roll The amount of roration ( in degrees ) around the z-axis.
        */
        void eulerToQuat( double pitch, double yaw , double roll );

        /**
        * Converts from Angle-Axis representation to quaternion.
        * @param angle The amount of rotation, in degrees, around an arbitrary axis.
        * @param axis The rotation axis.
        */
        void fromAngleAxis( double angle, const Vector3& axis );

        /**
        * Converts from Axis-Angle representation to quaternion.
        * @param angle The amount of rotation ( in degrees ) around an arbitrary axis.
        * @param x The x component of the rotation axis.
        * @param y The y component of the rotation axis.
        * @param z The z component of the rotarion axis.
        */
        void fromAngleAxis( double angle, double x, double y, double z);

        /**
        * Implements the assignment operator.
        * @param copy The right operand of the assignment.
        * @return The assigned quaternion. This allows chained calls.
        */
        Quaternion operator=( const Quaternion &copy );

        /**
        * Implements the Quaternion-to-Quaternion multiplication operator.
        * @param q The right operand of the multiplication.
        * @return Q = [ this * q ]. A quartenion which is the multiplication of this and the quartenion q.
        */
        Quaternion operator*( const Quaternion &q ) const;

        /**
        * Implements the Quarternion addiction operator.
        * @param q The right operand of the multiplication.
        * @return Q = [ this + q ]. A quaternion which is the addiction of this and the quaternion q.
        */
        Quaternion operator+( const Quaternion &q ) const;

        /**
        * Implements the equality operator.
        * @param q The right operand.
        * @return true if this quaternion is equal to q, false otherwise.
        * @see operator!=
        */
        bool operator==( const Quaternion &q ) const;

        /**
        * Implementets the difference operator.
        * @param q The right operand.
        * @return true if this quaternion is different from q, false otherwise.
        * @see operator==
        */
        bool operator!=( const Quaternion &q ) const;

        /**
         * Implements the negative operator.
         * @return [-w,-x,-y,-z]
         */
        Quaternion operator-() const;

   //private:

        /**
        * The scalar part of the quaternion.
        */
        double w;

        /**
        * The x component of the quaternion vector part.
        */
        double x;

        /**
        * The y component of the quaternion vector part.
        */
        double y;

        /**
        * The z component of the quaternion vector part.
        */
        double z;

};


#endif
