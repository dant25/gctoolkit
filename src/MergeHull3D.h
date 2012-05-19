#ifndef MERGEHULL3D_H
#define MERGEHULL3D_H

#include<list>
#include <map>
#include <stack>
#include <cmath>
#include <iostream>

#include "Point3D.h"
#include "Edge3D.h"
#include "Polygon.h"

class MergeHull3D
{
    public:
        MergeHull3D(std::list<Point*> pointList);
        virtual ~MergeHull3D();

        void draw();
        bool save(std::string fileName);

        void setPoint();
        void setFace();

        void clear();
        void execute();


    protected:

    private:
        bool renderPointList;
        bool renderFacesList;

        std::list<Point*> pointList;
        std::list<Edge*> edgeList;
        std::list<Polygon*> facesList;
};

#endif // MERGEHULL3D_H
