#ifndef CAMERA_H_
#define CAMERA_H_

#include "math/Quaternion.h"
#include "BoundingBox.h"
struct Frustum {
    double left;
    double right;
    double bottom;
    double top;
    double near;
    double far;
};

class Camera {
  public:
    Camera();

    void render();
    void rotate(double angle, const Vector3& axis);
    void updateRotatation(int mouseX, int mouseY, int windowWidth, int windowHeight);
    void fit(const BoundingBox& bb);
    void zoom(double zoomFactor);
    void mapTrackball(int mouseX, int mouseY, int windowWidth, int windowHeight);
    void setProjection(double fovy, double ar, double near, double ffar);
    void setProjection( double left, double right, double bottom, double top, double near, double ffar);


    void reset() { initialized = false; mouseLastPos = Vector3(0.0, 0.0, 0.0); mouseCurrPos = Vector3(0.0, 0.0, 0.0); };

    Quaternion orientation;
    Vector3 pos;
    Vector3 mouseLastPos;
    Vector3 mouseCurrPos;

    Frustum frustum;

    bool initialized;
};


#endif
