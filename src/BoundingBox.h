#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "math/Vector3.h"

class BoundingBox {
public:
    BoundingBox() { };
    BoundingBox(const Vector3& pMin, const Vector3& pMax) {
        this->pMin = pMin;
        this->pMax = pMax;
    }

    Vector3 pMin, pMax;

};

#endif

