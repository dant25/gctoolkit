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
#include "math/Vector3.h"

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

        bool existEdge(Edge3D e);
        void addEdge(Edge3D* e);
        void initialFace(std::list<Point*> pointList);
        void nextFaces();//(Polygon* face);

        static bool compareY(Point* first, Point* second);


    protected:

    private:
        bool renderPointList;
        bool renderFacesList;

        std::list<Point*> pointList;
        //std::list<Point*> free_pointList;
        std::list<Edge*> edgeList;
        std::list<Edge*> free_edgeList;
        std::list<Polygon*> facesList;
};

#endif // MERGEHULL3D_H
