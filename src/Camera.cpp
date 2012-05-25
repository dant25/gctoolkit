#include <GL/gl.h>
#include <GL/glu.h>
#include "Camera.h"
#include <cmath>
#include <iostream>


BoundingBox bb = BoundingBox(Vector3(-100, -100, -100), Vector3(100, 100, 100));


Camera::Camera() : pos(0.0, 0.0, 0.0), orientation(1.0, 0.0, 0.0, 1.0),
                    mouseCurrPos(0.0, 0.0, 0.0), mouseLastPos(0.0, 0.0, 0.0)
{
    initialized = false;
    frustum.left = frustum.bottom = - 1.0;
    frustum.right = frustum.top = 1.0;
    frustum.near = 0.001;
    frustum.far = 10000.0;
}

void Camera::rotate(double angle, const Vector3& axis) {
    angle *= 0.2;
    Quaternion q;
    q.fromAngleAxis( angle, axis );
    orientation = orientation * q;
}

void Camera::mapTrackball(int mouseX, int mouseY, int windowWidth, int windowHeight) {
   // ( PI / 2 )
    static const double PI_2 = 1.570796327;

    // map from viewport to a window with corners (-1,-1) and (1,1).
    // This window has width and height = 2.0.
    // Note the need to subtract windowWidth and windowHeight, that is because
    // ( 2 * mouse ) / window would map to a window with corners (0,0) and (1,1).
    // What we do is subtract 1 from the expression above giving the expression
    mouseCurrPos.x = ( 2.0 * mouseX - windowWidth ) / windowWidth;
    mouseCurrPos.y = ( windowHeight - 2.0 * mouseY ) / windowHeight;
    mouseCurrPos.z = 0.0;

    double d = mouseCurrPos.length();
    glBegin(GL_LINES);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMax.z);
        glVertex3f(bb.pMax.x, bb.pMin.y, bb.pMax.z);
        glVertex3f(bb.pMax.x, bb.pMax.y, bb.pMax.z);
        glVertex3f(bb.pMin.x, bb.pMax.y, bb.pMax.z);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMax.z);
        //Bottom face
        //glColor3f(0.0, 1.0, 0.0);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMin.z);
        glVertex3f(bb.pMax.x, bb.pMin.y, bb.pMin.z);
        glVertex3f(bb.pMax.x, bb.pMin.y, bb.pMax.z);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMax.z);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMin.z);
        //Top face
        //glColor3f(0.0, 0.0, 1.0);
        glVertex3f(bb.pMin.x, bb.pMax.y, bb.pMax.z);
        glVertex3f(bb.pMax.x, bb.pMax.y, bb.pMax.z);
        glVertex3f(bb.pMax.x, bb.pMax.y, bb.pMin.z);
        glVertex3f(bb.pMin.x, bb.pMax.y, bb.pMin.z);
        glVertex3f(bb.pMin.x, bb.pMax.y, bb.pMax.z);
        //Left face
        //glColor3f(1.0, 1.0, 1.0);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMin.z);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMax.z);
        glVertex3f(bb.pMin.x, bb.pMax.y, bb.pMax.z);
        glVertex3f(bb.pMin.x, bb.pMax.y, bb.pMin.z);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMin.z);
        //Right face
        //glColor3f(0.0, 0.0, 0.0);
        glVertex3f(bb.pMax.x, bb.pMin.y, bb.pMax.z);
        glVertex3f(bb.pMax.x, bb.pMin.y, bb.pMin.z);
        glVertex3f(bb.pMax.x, bb.pMax.y, bb.pMin.z);
        glVertex3f(bb.pMax.x, bb.pMax.y, bb.pMax.z);
        glVertex3f(bb.pMax.x, bb.pMin.y, bb.pMax.z);
        //Back face
        //glColor3f(1.0, 1.0, 0.0);
        glVertex3f(bb.pMax.x, bb.pMin.y, bb.pMin.z);
        glVertex3f(bb.pMin.x, bb.pMin.y, bb.pMin.z);
        glVertex3f(bb.pMin.x, bb.pMax.y, bb.pMin.z);
        glVertex3f(bb.pMax.x, bb.pMax.y, bb.pMin.z);
        glVertex3f(bb.pMax.x, bb.pMin.y, bb.pMin.z);
    glEnd();

    // the point lies outside the sphere z = 0.
    if ( d > 1.0 )
        //return;
        d = 1.0;
    mouseCurrPos.z = cos( PI_2 * d );
    mouseCurrPos.normalize();
    /*const double k = 0.70710678118654752440;
    if (d  < k)
        currPos.z = (1 - d);
    else
        currPos.z = k*k/d;*/

}

void Camera::updateRotatation(int mouseX, int mouseY, int windowWidth, int windowHeight) {
    if (!initialized)
    {
        mapTrackball( mouseX, mouseY, windowWidth, windowHeight );
        mouseLastPos = mouseCurrPos;
        initialized = true;
    }
    else
    {
        mapTrackball( mouseX, mouseY, windowWidth, windowHeight );
        double angle = mouseCurrPos.angle(mouseLastPos);
        Vector3 axis = (mouseCurrPos^mouseLastPos).normalize();
        rotate(angle, axis);
        mouseLastPos = mouseCurrPos;
    }
}

void Camera::render() {
    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode( GL_MODELVIEW );
    double m[16];
    orientation.quatToMatrix(m);

    //Translate the camera to pos
    m[12] = -pos.x;
    m[13] = -pos.y;
    m[14] = -pos.z;
    glTranslatef(-pos.x, -pos.y, -pos.z);
    glLoadMatrixd((double*)m);
    //glTranslatef( -pos.x, -pos.y, -pos.z );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //TODO: modificar frustum fora daqui.
    glFrustum( frustum.left, frustum.right, frustum.bottom, frustum.top, frustum.near, frustum.far);

    glPopAttrib();
}


void Camera::setProjection( double fovy, double ar, double near, double ffar )
{
    double height2 = near * tan( fovy );
    double width2 = ar * height2;

    frustum.left = pos.x - width2;
    frustum.right = pos.x + width2;
    frustum.bottom = pos.y - height2;
    frustum.top = pos.y + height2;
    frustum.near = near;
    frustum.far = ffar;
}

void Camera::setProjection( double left, double right, double bottom, double top, double near, double ffar )
{
    frustum.left = left;
    frustum.right = right;
    frustum.bottom = bottom;
    frustum.top = top;
    frustum.near = near;
    frustum.far = ffar;
}

void Camera::fit( const BoundingBox& bb )
{
    //reset();
    double width2 = (bb.pMax.x - bb.pMin.x) * 3.0;
    double height2= (bb.pMax.y - bb.pMin.y) * 3.0;
    double near, ffar;

    Vector3 bbCenter = (bb.pMax-bb.pMin)*0.5;

    // define aspect ratio to be 4:3. Case width is bigger than height adjust height size, otherwise adjust width
    ( width2 >= height2 ) ? height2 = width2 * 0.75 : width2 = height2 * 1.333;

    // fovy of 45º
    near = height2 / 2.0;
    ffar = 2.3 * ( bb.pMax.z - bb.pMin.z );
    if ( ffar < 1000 )
        ffar = 10000.0;

    //setPosition( 0.0, 0.0, bb.pMin.z + 2 * width2 );
    pos = Vector3(0.0, 0.0, bb.pMax.z + 2 * width2);

    setProjection( -width2, width2, -height2, height2, near, ffar );
}

void Camera::zoom(double zoomFactor) {
    frustum.left *= zoomFactor;
    frustum.right *= zoomFactor;
    frustum.bottom *= zoomFactor;
    frustum.top *= zoomFactor;
}
