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
        MergeHull3D(std::list< std::list<Point*> > list);
        virtual ~MergeHull3D();

        void draw();
        bool save(std::string fileName);

        void setPoint();
        void setFace();
        void setEdge();

        void clear();
        void execute();

        bool existEdge(Edge3D e);
        void addEdge(Edge3D* e);
        void initialFace();
        void nextFaces();

        static bool compareY(Point* first, Point* second);


    protected:

    private:
        bool renderPointList;
        bool renderFacesList;
        bool renderEdgesList;

        std::list< std::list<Point*> > listObj;
        std::list<Point*> pointList;
        std::list<Edge*> edgeList;
        std::list<Edge*> free_edgeList;
        std::list<Polygon*> facesList;
};

#endif // MERGEHULL3D_H
